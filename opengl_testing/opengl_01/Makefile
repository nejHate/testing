# Compiler and linker
CXX = g++
CXXFLAGS = -Wall -std=c++11

# Directories
INCLUDE_DIRS = -I/usr/include -I/usr/local/include
LIB_DIRS = -L/usr/lib -L/usr/local/lib

# Libraries
LIBS = -lglfw -lGLEW -lGL -lm

# Source files
SRCS = main.cpp

# Output executable
TARGET = cube

# Build target
all: $(TARGET) run

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) $(INCLUDE_DIRS) $(SRCS) $(LIB_DIRS) $(LIBS) -o $(TARGET)

# Run target
run: $(TARGET)
	./$(TARGET)

# Clean target
clean:
	rm -f $(TARGET)
	rm -f *.o
