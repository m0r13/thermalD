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

int64_t micros();
void delay(size_t);
const char* F(const char* c);

class Stream {
public:
    Stream(FILE* tx = stdout, FILE* rx = stdin) : tx(tx), rx(rx) {}
    ~Stream() {}

    virtual void write(uint8_t c) { fputc(c, tx); /*fflush(tx);*/ }
    virtual bool available() const { return !feof(rx); }
    virtual uint8_t read() { return fgetc(rx); }

protected:
    FILE *tx, *rx;
};

class SerialStream : public Stream {
public:
    SerialStream() : Stream(NULL, NULL) {}

    bool open(const char* path, int baudrate) {
        FILE* s = open_serial(path, baudrate);
        if (s == NULL) {
            return false;
        }
        tx = rx = s;
        return true;
    }
};

class Print {
public:
    virtual size_t write(uint8_t c) {}

    void pprintf(const char* fmt, va_list args) {
        char* str;
        int ret = vasprintf(&str, fmt, args);
        if (ret < 0) {
            fprintf(stderr, "Error in asprintf.\n");
            return;
        }
        print(str);
        free(str);
    }

    void printf(const char *fmt, ...) {
        va_list args;
        va_start(args, fmt);
        pprintf(fmt, args);
        va_end(args);
    }
    
    void print(const char* str) {
        const char* c = str - 1;
        while(*(++c) != '\0') {
            write(*c);
        }
    }

    void println(const char* str) {
        print(str);
        write('\n');
    }
};

#endif
