CC=g++
CFLAGS=-Wall
LDFLAGS=-lGL -lGLEW -lglfw -lglut

SOURCES=main.cpp
EXECUTABLE=opengl_cube

all: $(EXECUTABLE)

$(EXECUTABLE): $(SOURCES)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

clean:
	rm -f $(EXECUTABLE)
