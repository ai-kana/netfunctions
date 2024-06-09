#pragma once

struct fbuffer {
    unsigned char* instructions;
    unsigned int length;
};

struct fbuffer get_function(void* function);
