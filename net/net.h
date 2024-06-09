#pragma once

#include "../functions/freader.h"

#define source_ip "127.0.0.1"
#define source_port 10001
#define buffer_size 512

void send_buffer(unsigned char* buffer, unsigned int size);
struct fbuffer read_buffer();
