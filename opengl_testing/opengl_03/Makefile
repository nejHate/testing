CC=g++
CFLAGS=-Wall
LDFLAGS=-lGL -lGLEW -lglfw

SOURCES=main.cpp
EXECUTABLE=opengl_cube

all: $(EXECUTABLE)

$(EXECUTABLE): $(SOURCES)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

clean:
	rm -f $(EXECUTABLE)
