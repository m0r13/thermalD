#include "Adafruit_Thermal.h"
#include "arduino_compat.h"
#include "serial.h"
#include "image.h"

#include <iostream>
#include <string>

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " [serial-port]" << std::endl;
        return 1;
    }

    SerialStream s;
    s.open(argv[1], B9600);
    Adafruit_Thermal printer(&s);
    printer.begin();
    printer.feed(1);
    printer.printBitmap(image_width, image_height, image_data);
    printer.println("");
    printer.justify('C');
    for (std::string str; std::getline(std::cin, str); ) {
        printer.println(str.c_str());
    }
    return 0;
}
