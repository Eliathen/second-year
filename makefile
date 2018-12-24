CC=g++
CFLAGS=-c -Wall -std=c++11 
LIBFLAGS=-lsfml-graphics -lsfml-window -lsfml-system
SOURCES=main.cpp game.cpp map.cpp player.cpp ship.cpp enemy.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=battleshipGame
BINDIR=/usr/bin

all: $(SOURCES) $(EXECUTABLE)
        
$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@ $(LIBFLAGS)

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@ $(LIBFLAGS)

clean:
	rm *.o $(EXECUTABLE)