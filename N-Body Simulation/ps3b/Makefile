CC = g++
CCFLAGS = --std=c++20 -Wall -Werror -pedantic -g
LIB = -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system -lboost_unit_test_framework

# Source files and header files
SRC = main.cpp Universe.cpp CelestialBody.cpp
TEST_SRC = test.cpp Universe.cpp CelestialBody.cpp
HEADERS = Universe.hpp CelestialBody.hpp

# Output program when made
PROGRAM = NBody
TEST_PROGRAM = test
STATIC_LIB = NBody.a

# Default target
all: $(PROGRAM) $(TEST_PROGRAM) $(STATIC_LIB)

# Object Files
OBJ = $(SRC:.cpp=.o)
TEST_OBJ = $(TEST_SRC:.cpp=.o)

# Building the Executables

$(PROGRAM): $(OBJ)
	$(CC) $(CCFLAGS) -o $@ $^ $(LIB)

$(TEST_PROGRAM): $(TEST_OBJ)
	$(CC) $(CCFLAGS) -o $@ $^ $(LIB)

# Build the static Library

$(STATIC_LIB): Universe.o CelestialBody.o
	ar rcs $@ $^

# Compile the source files
%.o: %.cpp $(HEADERS) 
	$(CC) $(CCFLAGS) -c $< -o $@

test: $(TEST_PROGRAM)

# Clean
clean:
	rm -f *.o $(PROGRAM) $(TEST_PROGRAM) $(STATIC_LIB)

# Lint executable
lint:
	cpplint *.cpp *.hpp

# Phony targets
.PHONY: all clean lint test