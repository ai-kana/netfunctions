#include "freader.h"

#include <string.h>
#include <stdlib.h>

// All are ret instruction op codes
#define RET_1 0xC3
#define RET_2 0xCB

// These pop extra values off the stack of word size so '+2' to the size
#define RET_3 0xC2
#define RET_4 0xCA

struct fbuffer get_function(void* function) {
    unsigned char* ptr = function;
    unsigned int size = 0;
    while (1) {
        size++;
        if (*ptr == RET_1 || *ptr == RET_2) {
            break;
        }

        if (*ptr == RET_3 || *ptr == RET_4) {
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
