#include "./myclib/vector/vector.h"
#include "./myclib/string/mystring.h"

#include <stdio.h>
#include <limits.h>

void print_binary(unsigned int num) {
    int bits = sizeof(num) * 8;

    for (int i = bits - 1; i >= 0; i--) {
        printf("%d", (num >> i) & 1);
    }
    putchar('\n');
}

vector zip(char* r) {
    vector vec = vector_new(3,sizeof(int));

    unsigned int i;

    while(1) {
        i = 0;
        for(size_t q = 0; q < (sizeof(int)*4);q++) {
            i = i << 2;
            switch(*r) {
                case 'a':
                    i = i | 1;
                    break;
                case 'b':
                    i = i | 2;
                    break;
                case 'c':
                    i = i | 3;
                    break;
                case '\0':
                    vector_push_back(&vec, &i);
                    return vec;
                default:
                    abort();
            }
            r++;
        }
        vector_push_back(&vec, &i);
    }
}

string unzip(vector* vec) {
    string str = string_new_empty(10);

    int num_to_shift = sizeof(int)*8 - 2;

    for (size_t i = 0; i<vec->length; i++){
        unsigned int el = *(unsigned int*)vector_pos(vec,i);
        if (i==vec->length-1) {
            while(el>>num_to_shift == 0 && num_to_shift != 0) {
                num_to_shift -= 2;
            }
        }

        while (num_to_shift >= 0) {
            switch(el>>num_to_shift) {
                case 1:
                    string_push_back(&str,'a');
                    break;
                case 2:
                    string_push_back(&str,'b');
                    break;
                case 3:
                    string_push_back(&str,'c');
                    break;
                case 0:
                    return str;
                default:
                    abort();
            }
            el = el&(UINT_MAX>>(32-num_to_shift));
            num_to_shift-=2;
        }

        num_to_shift=sizeof(int)*8 - 2;
    }
}

int main() {
    char* a = "ccccccccccccccccccccccccccccccccc";
    vector vec = zip(a);
    string str = unzip(&vec);
    puts(str.str);

    for (size_t i = 0; i < vec.length; i++) {
        unsigned int num = *(unsigned int*)vector_pos(&vec, i);
        print_binary(num);
    }

    string_destroy(&str);
    vector_destroy(&vec);
}
