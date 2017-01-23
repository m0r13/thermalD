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
    s.open(argv[1], B9600);
    Adafruit_Thermal printer(&s);

    for (std::string line; std::getline(std::cin, line); ) {
        printer.println(line.c_str());
    }
    return 0;
}
