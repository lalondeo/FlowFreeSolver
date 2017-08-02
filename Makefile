CXX = g++
TARGET = flowfree.exe
OBJECTS = bin/main.o bin/grid.o bin/solvedgrid.o bin/unsolvedgrid.o bin/node.o bin/square.o bin/tree.o bin/movegen.o bin/nodeslist.o  bin/hashutils.o bin/transpositiontable.o bin/eval.o bin/treeanalysis.o

%.o: ../src/%.cpp
	$(CXX) -g -O3 -c $^ -o $@

all: $(OBJECTS)
	$(CXX) -o $(TARGET) -DDEBUG -g $(OBJECTS)
	
clear:
	del bin\*.o