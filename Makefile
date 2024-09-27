CC = gcc
TARGET = cfman
CFLAGS = -I./include -Wall -g $(shell sdl2-config --cflags)
LDFLAGS = $(shell sdl2-config --libs)
OBJS = main.o fops.o window.o

all: $(TARGET)

$(TARGET): $(OBJS)

	$(CC) $(CFLAGS) $(OBJS) -o $(TARGET) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@


run: 
	./$(TARGET)

clean:
	rm -rf *.o $(TARGET)