LIB_OBJ=arduino_compat.o Adafruit_Thermal.o
APP_OBJ=test.o A_printertest.o
OBJ=$(LIB_OBJ) $(APP_OBJ)

all: test A_printertest
clean:
	rm -rf test $(OBJ)

test: test.o $(LIB_OBJ)
	g++ -o test test.o $(LIB_OBJ)

A_printertest: A_printertest.o $(LIB_OBJ)
	g++ -o A_printertest A_printertest.o $(LIB_OBJ)

Adafruit_Thermal.o: Adafruit_Thermal.h
arduino_compat.o: arduino_compat.h
