#include "arduino_compat.h"

int64_t micros() {
    struct timeval tv;
    gettimeofday(&tv,NULL);
    return tv.tv_sec*(uint64_t)1000000+tv.tv_usec;
}

void delay(size_t c) {
    usleep(c * 1000);
}

const char* F(const char* c) { return c; }

