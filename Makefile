all: test
clean:
	rm -rf test test.o Adafruit_Thermal.o

test: test.o Adafruit_Thermal.o
	g++ -o test test.o Adafruit_Thermal.o

Adafruit_Thermal.o: Adafruit_Thermal.h
