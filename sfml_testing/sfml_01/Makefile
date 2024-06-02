CXX = g++
CXXFLAGS = -std=c++11 -Wall
SFML_LIBS = -lsfml-graphics -lsfml-window -lsfml-system

SRC = main.cpp
OUT = subchunk_renderer

all:
	$(CXX) $(CXXFLAGS) -o $(OUT) $(SRC) $(SFML_LIBS)

clean:
	rm -f $(OUT)
