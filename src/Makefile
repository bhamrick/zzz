CC=g++
CCFLAGS=-I. -g
LDFLAGS=-lGL -lGLU -lglut -g
TARGET=a.out
OBJECTS=main.o display.o vec.o world.o mass.o update.o spring.o character.o input.o view.o level.o overworld.o mode.o menu.o main_screen.o options.o message.o

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) -o $(TARGET) $(LDFLAGS) $(OBJECTS)

clean:
	rm -f $(TARGET) $(OBJECTS)

%.o: %.cc
	$(CC) -c $(CCFLAGS) $<
