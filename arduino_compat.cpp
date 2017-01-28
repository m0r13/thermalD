#include "arduino_compat.h"

unsigned long micros() {
    struct timeval tv;
    gettimeofday(&tv,NULL);
    return tv.tv_sec * (unsigned long) 1000000 + tv.tv_usec;
}

void delay(size_t c) {
    usleep(c * 1000);
}

const char* F(const char* c) { return c; }

Stream::Stream(FILE* tx, FILE* rx)
    : tx(tx), rx(rx) {
}

Stream::~Stream() {
}

void Stream::write(uint8_t c) {
    fputc(c, tx);
}

bool Stream::available() const {
    return !feof(rx);
}

uint8_t Stream::read() {
    return fgetc(rx);
}

SerialStream::SerialStream()
    : Stream(NULL, NULL) {
}

bool SerialStream::open(const char* path, int baudrate) {
    FILE* s = open_serial(path, baudrate);
    if (s == NULL) {
        return false;
    }
    tx = rx = s;
    return true;
}

void Print::pprintf(const char* fmt, va_list args) {
    char* str;
    int ret = vasprintf(&str, fmt, args);
    if (ret < 0) {
        fprintf(stderr, "Error in asprintf.\n");
        return;
    }
    print(str);
    free(str);
}

void Print::printf(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    pprintf(fmt, args);
    va_end(args);
}

void Print::print(const char* str) {
    const char* c = str - 1;
    while(*(++c) != '\0') {
        write(*c);
    }
}

void Print::println(const char* str) {
    print(str);
    write('\n');
}

void Print::printParagraph(std::string str, size_t lineLength) {
    int pos = 0;
    while (!str.empty()) {
        std::string word;
        size_t nextWhitespace = str.find(' ');
        if (nextWhitespace == std::string::npos) {
            word = str;
            str = "";
        } else {
            word = str.substr(0, nextWhitespace);
            str = str.substr(nextWhitespace+1);
            size_t nextCharacter = str.find_first_not_of(" ");
            if (nextCharacter != std::string::npos) {
                str = str.substr(nextCharacter);
            } else {
                str = "";
            }
        }

        if (pos + word.size() < lineLength) {
            print(word.c_str());
            pos += word.size();

            if (pos + 1 < lineLength) {
                write(' ');
                pos++;
            } else {
                write('\n');
                pos = 0;
            }
        } else {
            write('\n');
            print(word.c_str());
            pos = word.size();
        }
    }

    if (pos != 0) {
        write('\n');
    }
    write('\n');
}

