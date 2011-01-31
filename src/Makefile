CC=g++
CCFLAGS=-I.
LDFLAGS=-lGL -lGLU -lglut
TARGET=a.out
OBJECTS=main.o display.o vec.o world.o mass.o update.o spring.o character.o input.o view.o level.o overworld.o mode.o menu.o

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) -o $(TARGET) $(LDFLAGS) $(OBJECTS)

clean:
	rm -f $(TARGET) $(OBJECTS)

%.o: %.cc
	$(CC) -c $(CCFLAGS) $<
