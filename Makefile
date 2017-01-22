LIB_OBJ=arduino_compat.o Adafruit_Thermal.o
OBJ=$(LIB_OBJ)

all: test
clean:
	rm -rf test $(OBJ)

test: test.o $(LIB_OBJ)
	g++ -o test test.o $(LIB_OBJ)

Adafruit_Thermal.o: Adafruit_Thermal.h
arduino_compat.o: arduino_compat.h
