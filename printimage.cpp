#include "Adafruit_Thermal.h"
#include "arduino_compat.h"
#include "serial.h"
#include "image_data.h"

#include <iostream>
#include <string>

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " [serial-port]" << std::endl;
        return 1;
    }

    SerialStream s;
    s.open(argv[1], B9600);
    if (!s.open(argv[1], B9600)) {
        std::cerr << "Unable to open " << argv[1] << ": " << strerror(errno) << std::endl;
        return 1;
    }
    Adafruit_Thermal printer(&s);
    printer.begin();
    printer.setDefaults();
    printer.feed(1);

    printer.setDotPrintTime(printer.getDotPrintTime() * 0.1);
    printer.printBitmap(image_width, image_height, image_data);
    
    printer.println("");
    for (std::string str; std::getline(std::cin, str); ) {
        printer.printParagraph(str.c_str());
    }
    return 0;
}
