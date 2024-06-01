CC=g++
CFLAGS=-Wall
LDFLAGS=-lglfw -lGL -lX11 -lpthread -lXrandr -lXi

SOURCES=main.cpp
EXECUTABLE=opengl_window

all: $(EXECUTABLE)

$(EXECUTABLE): $(SOURCES)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

clean:
	rm -f $(EXECUTABLE)
