CC=clang
OUTPUT=game
CFLAGS=-Wall $(shell sdl2-config --cflags)
LDFLAGS=$(shell sdl2-config --libs) -lSDL2_image
SRC=main.c display.c events.c grid.c
OBJ=$(SRC:.c=.o)

all: $(OUTPUT)

$(OUTPUT): $(OBJ)
	@echo "linking $@.."
	@$(CC) -o $@ $^ $(LDFLAGS)

main.c : display.h events.h grid.h
%.o: %.c
	@echo "$(CC) $@.."
	@$(CC) $(CFLAGS) -o $@ -c $<

clean:
	rm *.o
	rm $(OUTPUT)
