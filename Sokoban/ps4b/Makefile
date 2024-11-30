CC = g++
CCFLAGS = --std=c++20 -Wall -Werror -pedantic -g
LIB = -lsfml-graphics -lsfml-audio -lsfml-window -lsfml-system -lboost_unit_test_framework

# Source files and header files
SRC = main.cpp Sokoban.cpp
HEADERS = Sokoban.hpp

# Output program when made
PROGRAM = Sokoban
STATIC_LIB = Sokoban.a

# Default target
all: $(PROGRAM) $(STATIC_LIB)

# Object Files
OBJ = $(SRC:.cpp=.o)

# Building the Executable
$(PROGRAM): $(OBJ)
	$(CC) $(CCFLAGS) -o $@ $^ $(LIB)

# Build the static Library
$(STATIC_LIB): Sokoban.o
	ar rcs $@ $^

# Compile the source files
%.o: %.cpp $(HEADERS)
	$(CC) $(CCFLAGS) -c $< -o $@

# Clean
clean:
	rm -f *.o $(PROGRAM) $(STATIC_LIB)

# Lint executable
lint:
	cpplint *.cpp *.hpp

# Phony targets
.PHONY: all clean lint
