#include "serial.h"

#include <errno.h>      // Error number definitions
#include <stdint.h>     // C99 fixed data types
#include <stdlib.h>     // C standard library
#include <string.h>     // String function definitions
#include <unistd.h>     // UNIX standard function definitions
#include <fcntl.h>      // File control definitions

// Open usb-serial port for reading & writing
FILE* open_serial(const char* path, int baudrate) {
    FILE* f = fopen(path, "r+");
    if (f == NULL) {
        /*
        fprintf(stderr, "open_serial: Unable to open %s: %s\n", path, strerror(errno));
        exit(1);
        */
        return NULL;
    }

    int fd = fileno(f);
    if (fd == -1) {
        /*
        fprintf(stderr, "open_serial: Unable to open %s: %s\n", path, strerror(errno));
        exit(1);
        */
        return NULL;
    }

    // Terminal options
    struct termios options;
    // Return value
    int rc;

    // Get the current options for the port
    if((rc = tcgetattr(fd, &options)) < 0) {
        /*
        fprintf(stderr, "failed to get attr: %d, %s\n", fd, strerror(errno));
        exit(1);
        */
        return NULL;
    }

    // Set the baud rates
    cfsetispeed(&options, baudrate);
    cfsetospeed(&options, baudrate);

    cfmakeraw(&options);
    options.c_cflag |= (CLOCAL | CREAD);   // Enable the receiver and set local mode
    options.c_cflag &= ~CSTOPB;            // 1 stop bit
    options.c_cflag &= ~CRTSCTS;           // Disable hardware flow control
    options.c_cc[VMIN]  = 1;
    options.c_cc[VTIME] = 2;

    // Set the new attributes
    if((rc = tcsetattr(fd, TCSANOW, &options)) < 0) {
        /*
        fprintf(stderr, "failed to set attr: %d, %s\n", fd, strerror(errno));
        exit(1);
        */
        return NULL;
    }

    return f;
}

