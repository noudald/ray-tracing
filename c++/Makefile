SOURCES := src/main.cpp
OBJS := $(SOURCES:.cpp=.o)
CFLAGS := -Wall -Wextra -Werror
CC := g++

all: main

main: $(OBJS)
	$(CC) $(CFLAGS) -o main $(OBJS) $(LFLAGS) $(LIBS)

run:
	./main > image.ppm && ristretto image.ppm

clean:
	rm main image.ppm
