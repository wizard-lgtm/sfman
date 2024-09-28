CC = gcc
TARGET = cfman
CFLAGS = -I./include -Wall -g -I/opt/homebrew/include/SDL2
LDFLAGS = $(shell sdl2-config --libs)
OBJS = main.o fops.o window.o color.o
ARCH = arm64

all: $(TARGET)

$(TARGET): $(OBJS)

	$(CC) -arch $(ARCH) $(CFLAGS) $(OBJS) -o $(TARGET) $(LDFLAGS)

%.o: %.c
	$(CC) -arch $(ARCH) $(CFLAGS) -c $< -o $@


run: 
	./$(TARGET)

clean:
	rm -rf *.o $(TARGET)