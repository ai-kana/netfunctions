#include "net/net.h"
#include <stdio.h>
#include <stdlib.h>

#include "functions/freader.h"
#include "functions/frunner.h"

int test() {
    int x = 5;
    x++;
    x++;
    x <<= 1;
    return x;
}

int main() {
    printf("1: Wait for function\n2: Send function\n> ");

    int input;
    scanf("%d", &input);

    struct fbuffer buffer;
    if (input == 1) {
        buffer = read_buffer();
        run_function(buffer);
    }

    if (input == 2) {
        buffer = get_function(&test);
        send_buffer(buffer.instructions, buffer.length);
    } 


    free(buffer.instructions);
    return 0;
}
