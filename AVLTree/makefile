hepsi: derle calistir

derle:
	g++ -I ./include/ -o ./lib/Node.o -c ./src/Node.cpp
	g++ -I ./include/ -o ./lib/List.o -c ./src/List.cpp
	g++ -I ./include/ -o ./lib/Control.o -c ./src/Control.cpp
	g++ -I ./include/ -o ./bin/program ./lib/Control.o ./lib/List.o ./lib/Node.o ./src/Program.cpp
	
calistir:	
	./bin/program