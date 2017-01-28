#ifndef ARDUINO_COMPAT_H
#define ARDUINO_COMPAT_H

#include "serial.h"

#include <cstdint>
#include <cstring>
#include <cctype>
#include <cstdio>
#include <ctime>
#include <cstdarg>
#include <cstdlib>
#include <sys/time.h>
#include <unistd.h>

#include <iostream>
#include <string>

int64_t micros();
void delay(size_t);
const char* F(const char* c);

class Stream {
public:
    Stream(FILE* tx = stdout, FILE* rx = stdin);
    virtual ~Stream();

    virtual void write(uint8_t c);
    virtual bool available() const;
    virtual uint8_t read();

protected:
    FILE *tx, *rx;
};

class SerialStream : public Stream {
public:
    SerialStream();

    bool open(const char* path, int baudrate);
};

class Print {
public:
    virtual size_t write(uint8_t c) {}

    void pprintf(const char* fmt, va_list args);

    void printf(const char *fmt, ...);

    void print(const char* str);

    void println(const char* str);

    void printParagraph(std::string str, size_t lineLength = 32);
};

#endif
