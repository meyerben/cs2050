CFLAGS = -g -Wall -Werror

all: Gauntlet

Gauntlet: game.o shop.o heroes.o io.o
	gcc $^ -g -o Gauntlet

%.o: %.c game.h
	gcc $< -c $(CFLAGS) -o $@

clean:
	rm -f *.o Gauntlet
