CXX = g++
TARGET = flowfree.exe
OBJECTS = bin/main.o bin/grid.o bin/solvedgrid.o bin/unsolvedgrid.o bin/node.o bin/square.o bin/tree.o bin/movegen.o bin/activenodeslist.o  bin/hashutils.o bin/transpositiontable.o

%.o: ../src/%.cpp
	$(CXX) -g -c $^ -o $@

all: $(OBJECTS)
	$(CXX) -o $(TARGET) -DDEBUG -g $(OBJECTS)
	
clear:
	del bin\*.o