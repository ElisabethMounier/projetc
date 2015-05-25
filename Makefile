CC=gcc
OUTPUT=game
CFLAGS=-Wall $(shell sdl2-config --cflags)
LDFLAGS=$(shell sdl2-config --libs) -lSDL2_image -lSDL2_ttf
SRC=display.c events.c grid.c level.c game.c main.c
OBJ=$(SRC:.c=.o)

all: $(OUTPUT)

$(OUTPUT): $(OBJ)
	@echo "linking $@.."
	@$(CC) -o $@ $^ $(LDFLAGS)

main.c : display.h events.h grid.h game.h
%.o: %.c
	@echo "$(CC) $@.."
	@$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm *.o
	rm $(OUTPUT)
