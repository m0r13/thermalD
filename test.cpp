
#include "Adafruit_Thermal.h"
#include "adalogo.h"
#include "adaqrcode.h"

#include <stdlib.h>
#include <iostream>
#include <fstream>

char randchar() {
    char c = 0;
    while (1) {
        if (isprint(c = rand() % 255) && !isspace(c))
            return c;
    }
}

int main() {
    Stream s(stdout, stdin);
    Adafruit_Thermal t(&s);
    t.begin();
    t.println("Hello World!");
    t.feed(2);

    //t.printf("Hello World!\n");
    //t.printf("%d %f\n", 42, 0.2049504);

    //t.feed(2);
    //return 0;

    /*
    for(int i = 0; i < 10; i++)
        putchar(randchar());
    printf("\n");
    */
   
    std::ifstream f("/home/moritz/100000.txt");
    //f.open();

    while (1) {

    int i = 0;
    while(i < 28) {
        t.write(randchar());
        char c;
        f >> c;
        if (c == '4' || c == '2') {
            t.boldOn();
        } else {
            t.boldOff();
        }
        //t.write(c);
        //t.write('a' + i);
        //t.write('4');
        //t.write('2');
        //putchar(randchar());
        //printf("\n");
        delay(25);
        i++;
    }
    t.feed(1);
    }
    

  // The following calls are in setup(), but don't *need* to be.  Use them
  // anywhere!  They're just here so they run one time and are not printed
  // over and over (which would happen if they were in loop() instead).
  // Some functions will feed a line when called, this is normal.

    /*
  // Test inverse on & off
  t.inverseOn();
  t.println(F("Inverse ON"));
  t.inverseOff();

  // Test character double-height on & off
  t.doubleHeightOn();
  t.println(F("Double Height ON"));
  t.doubleHeightOff();

  // Set text justification (right, center, left) -- accepts 'L', 'C', 'R'
  t.justify('R');
  t.println(F("Right justified"));
  t.justify('C');
  t.println(F("Center justified"));
  t.justify('L');
  t.println(F("Left justified"));

  // Test more styles
  t.boldOn();
  t.println(F("Bold text"));
  t.boldOff();

  t.underlineOn();
  t.println(F("Underlined text"));
  t.underlineOff();

  t.setSize('L');        // Set type size, accepts 'S', 'M', 'L'
  t.println(F("Large"));
  t.setSize('M');
  t.println(F("Medium"));
  t.setSize('S');
  t.println(F("Small"));

  t.justify('C');
  t.println(F("normal\nline\nspacing"));
  t.setLineHeight(50);
  t.println(F("Taller\nline\nspacing"));
  t.setLineHeight(); // Reset to default
  t.justify('L');

  // Barcode examples:
  // CODE39 is the most common alphanumeric barcode:
  t.printBarcode("ADAFRUT", CODE39);
  t.setBarcodeHeight(100);
  // Print UPC line on product barcodes:
  t.printBarcode("123456789123", UPC_A);
  */

    /*
  // Print the 75x75 pixel logo in adalogo.h:
  t.printBitmap(adalogo_width, adalogo_height, adalogo_data);

  // Print the 135x135 pixel QR code in adaqrcode.h:
  t.printBitmap(adaqrcode_width, adaqrcode_height, adaqrcode_data);
  t.println(F("Adafruit!"));
  t.feed(2);
  */



   return 0;
}
