#ifndef serial_h
#define serial_h

#include <stdio.h>
#include <termios.h>

FILE* open_serial(const char* path, int baudrate);

#endif

