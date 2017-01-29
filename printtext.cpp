#include "Adafruit_Thermal.h"
#include "arduino_compat.h"
#include "serial.h"

#include <iostream>

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " [serial-port]" << std::endl;
        return 1;
    }

    SerialStream s;
    if (!s.open(argv[1], B9600)) {
        std::cerr << "Unable to open " << argv[1] << ": " << strerror(errno) << std::endl;
        return 1;
    }
    Adafruit_Thermal printer(&s);
    printer.begin();
    printer.setDefault();

    for (std::string line; std::getline(std::cin, line); ) {
        printer.printParagraph(line.c_str());
    }
    return 0;
}
