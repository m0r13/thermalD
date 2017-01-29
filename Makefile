LIB_OBJ=serial.o arduino_compat.o image.o Adafruit_Thermal.o
APP_OBJ=printtext.o printimage.o test.o A_printertest.o
OBJ=$(LIB_OBJ) $(APP_OBJ)

CXXARGS=-g

all: printtext printimage test A_printertest
clean:
	rm -rf test $(OBJ)

printtext: printtext.o $(LIB_OBJ)
	g++ -o printtext printtext.o $(LIB_OBJ)
printimage: printimage.o $(LIB_OBJ)
	g++ -o printimage printimage.o $(LIB_OBJ)

test: test.o $(LIB_OBJ)
	g++ -o test test.o $(LIB_OBJ)

A_printertest: A_printertest.o $(LIB_OBJ)
	g++ -o A_printertest A_printertest.o $(LIB_OBJ)

serial.o: serial.h
arduino_compat.o: arduino_compat.h
image.o: image.h
Adafruit_Thermal.o: Adafruit_Thermal.h
printtext.o:  Adafruit_Thermal.h
printimage.o:  Adafruit_Thermal.h image_data.h
test.o: Adafruit_Thermal.h
A_printertest.o: Adafruit_Thermal.h
