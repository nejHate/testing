# Define the compiler
CXX = g++

# Define the compiler flags
CXXFLAGS = -std=c++11 -Wall

# Define the SFML library flags
SFML_LIBS = -lsfml-graphics -lsfml-window -lsfml-system

# Define the source files
SRC = main.cpp

# Define the output executable
OUT = subchunk_renderer

# Define the make rules
all: $(OUT)

$(OUT): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(OUT) $(SRC) $(SFML_LIBS)

clean:
	rm -f $(OUT)
