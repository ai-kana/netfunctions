#include "frunner.h"
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>

void run_function(struct fbuffer function) {
    void* exe_buffer = mmap(
        NULL, 
        function.length, 
        PROT_READ | PROT_WRITE | PROT_EXEC,
        MAP_PRIVATE | MAP_ANONYMOUS,
        -1,
        0
    );
    if (exe_buffer == MAP_FAILED) {
        printf("Failed to map memory");
        return;
    }

    memcpy(exe_buffer, function.instructions, function.length);
    int (*func)() = (int (*)())exe_buffer;
    int out = func();

    printf("Return: %d\n", out);

    if (munmap(exe_buffer, function.length) == -1) {
        printf("Failed to unmap memory");
        return;
    }
}
