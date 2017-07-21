CXX = g++
TARGET = flowfree.exe
OBJECTS = bin/main.o bin/grid.o bin/solvedgrid.o bin/unsolvedgrid.o bin/square.o

%.o: ../src/%.cpp
	$(CXX) -c $^ -o $@

all: $(OBJECTS)
	$(CXX) -o $(TARGET) $(OBJECTS)