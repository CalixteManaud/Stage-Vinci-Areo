all: ComponentTester.run

ComponentTester.run: main.o ComponentTester.o Component.o Button.o USB.o
	g++ -o ComponentTester.run main.o ComponentTester.o Component.o Button.o USB.o -lsfml-system -lsfml-window -lsfml-graphics -lusb-1.0 -pthread

main.o: src/main.cpp
	g++ -c src/main.cpp

ComponentTester.o: src/ComponentTester.cpp
	g++ -c src/ComponentTester.cpp

Component.o: src/Component.cpp
	g++ -c src/Component.cpp

Button.o: src/Button.cpp
	g++ -c src/Button.cpp

USB.o: src/USB.cpp
	g++ -c src/USB.cpp

clean:
	rm -f *.o *.run
