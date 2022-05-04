all: MCDU.run FCU.run Pedestal.run

MCDU.run: MCDU.o
	g++ -o MCDU.run MCDU.o -lusb-1.0

FCU.run: FCU.o
	g++ -o FCU.run FCU.o -lusb-1.0

Pedestal.run: Pedestal.o
	g++ -o Pedestal.run Pedestal.o -lusb-1.0

MCDU.o: MCDU.cpp
	g++ -c MCDU.cpp

FCU.o: FCU.cpp
	g++ -c FCU.cpp

Pedestal.o: Pedestal.cpp
	g++ -c Pedestal.cpp

clean:
	rm -f *.o *.run

