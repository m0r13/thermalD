#ifndef ARDUINO_COMPAT_H
#define ARDUINO_COMPAT_H

#include <cstdint>
#include <cstring>
#include <cctype>
#include <cstdio>
#include <ctime>
#include <sys/time.h>
#include <unistd.h>

int64_t micros();
void delay(size_t);
const char* F(const char* c);

class Stream {
public:
    void write(uint8_t c) { putchar(c); fflush(stdout); }
    bool available() { return false; }
    uint8_t read() { return 0; }
};

class Print {
public:
    virtual size_t write(uint8_t c) {}

    void println(const char* str) {
        const char* c = str - 1;
        while(*(++c) != '\0') {
            write(*c);
        }
    }
};

#endif
