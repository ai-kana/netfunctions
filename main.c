#include "net/net.h"
#include <stdio.h>
#include <stdlib.h>

#include "functions/freader.h"
#include "functions/frunner.h"

int test() {
    return 69;
}

int main() {
    printf("1: Read and execute function\n2: Send function\n> ");

    int input;
    scanf("%d", &input);

    struct fbuffer buffer;
    if (input == 1) {
        buffer = get_function(&test);
        send_buffer(buffer.instructions, buffer.length);
    } 

    if (input == 2) {
        buffer = read_buffer();
        run_function(buffer);
    }

    free(buffer.instructions);
    return 0;
}
