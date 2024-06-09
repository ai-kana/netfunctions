#include "freader.h"

#include <string.h>
#include <stdlib.h>

struct fbuffer get_function(void* function) {
    unsigned char* ptr = function;
    unsigned int size = 0;
    while (1) {
        size++;
        if (*ptr == 0xC3 || *ptr == 0xCB) {
            break;
        }

        if (*ptr == 0xC2 || *ptr == 0xCA) {
            size += 2;
            break;
        }

        ptr++;
    }

    unsigned char* instructions = (unsigned char*)malloc(size);
    memcpy(instructions, function, size);

    struct fbuffer ret;
    ret.instructions = instructions;
    ret.length = size;

    return ret;
}
