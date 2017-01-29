
#include "Adafruit_Thermal.h"
#include "image.h"

#include <iostream>

int main() {
    SerialStream s;
    s.open("/dev/ttyUSB0", B9600);
    Adafruit_Thermal t(&s);
    t.begin();
    t.setDefault();

    TestImageStream image;
    t.printImage(image);

    return 0;
}
