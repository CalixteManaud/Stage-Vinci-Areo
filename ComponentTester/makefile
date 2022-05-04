all: ComponentTester.run

ComponentTester.run: Folders main.o ComponentTester.o Component.o Button.o USB.o
	g++ -o bin/ComponentTester.run obj/main.o obj/ComponentTester.o obj/Component.o obj/Button.o obj/USB.o -lsfml-system -lsfml-window -lsfml-graphics -lusb-1.0 -pthread

main.o: src/main.cpp
	g++ -o obj/main.o -c src/main.cpp

ComponentTester.o: src/ComponentTester.cpp
	g++ -o obj/ComponentTester.o -c src/ComponentTester.cpp

Component.o: src/Component.cpp
	g++ -o obj/Component.o -c src/Component.cpp

Button.o: src/Button.cpp
	g++ -o obj/Button.o -c src/Button.cpp

USB.o: src/USB.cpp
	g++ -o obj/USB.o -c src/USB.cpp

Folders:
	mkdir -p bin obj

clean:
	rm -rf bin obj
