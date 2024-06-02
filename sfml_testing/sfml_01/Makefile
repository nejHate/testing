# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall

# Source file
SRC = main.cpp

# Output executable
OUT = subchunk_renderer

# SFML libraries
SFML_LIBS = -lsfml-graphics -lsfml-window -lsfml-system

# Build rule
all: $(OUT)

$(OUT): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(OUT) $(SRC) $(SFML_LIBS)

# Clean rule
clean:
	rm -f $(OUT)
