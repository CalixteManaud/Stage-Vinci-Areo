all: ManualTester.run

ManualTester.run: ManualTester.o
	g++ -o ManualTester.run ManualTester.o -lusb-1.0

MCDU.o: ManualTester.cpp
	g++ -c ManualTester.cpp

clean:
	rm -f *.o *.run

