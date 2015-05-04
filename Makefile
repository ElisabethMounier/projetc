LIBS=$(shell sdl2-config --libs)
CFLAGS=$(shell sdl2-config --cflags)

all: 
	gcc -o main main.c $(LIBS)

#main:
#	gcc -o main.o -c main.c $(CFLAGS)

clean:
	rm *.o
	rm main
