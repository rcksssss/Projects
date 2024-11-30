CC = g++
CCFLAGS = --std=c++20 -Wall -Werror -pedantic -g
LIB = -lsfml-system -lboost_unit_test_framework

# Source files and header files
SRC = main.cpp EDistance.cpp
TEST_SRC = test.cpp EDistance.cpp
HEADERS = EDistance.hpp

# Output program when made
PROGRAM = EDistance
TEST_PROGRAM = test
STATIC_LIB = EDistance.a

# Default target
all: $(PROGRAM) $(TEST_PROGRAM) $(STATIC_LIB)

# Object Files
OBJ = $(SRC:.cpp=.o)
TEST_OBJ = $(TEST_SRC:.cpp=.o)

# Building the Executable
$(PROGRAM): $(OBJ)
	$(CC) $(CCFLAGS) -o $@ $^ $(LIB)

# Building the Test Executable
$(TEST_PROGRAM): $(TEST_OBJ)
	$(CC) $(CCFLAGS) -o $@ $^ $(LIB)

# Build the static Library
$(STATIC_LIB): EDistance.o
	ar rcs $@ $^

# Compile the source files
%.o: %.cpp $(HEADERS)
	$(CC) $(CCFLAGS) -c $< -o $@

# Clean
clean:
	rm -f *.o $(PROGRAM) $(TEST_PROGRAM) $(STATIC_LIB)

# Lint executable
lint:
	cpplint *.cpp *.hpp

# Phony targets
.PHONY: all clean lint
