# Compiler
CC = g++
# Compiler flags
CFLAGS = -g -Wall -std=c++11

# The build target executable
TARGET = final

# Source files
SRC = coach.cpp officer.cpp member.cpp reservation.cpp user.cpp court.cpp final.cpp

# Object files
OBJ = $(SRC:.cpp=.o)

# Default target
all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ)

# To obtain object files
%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

# To remove generated files
clean:
	rm -f $(OBJ) $(TARGET)
