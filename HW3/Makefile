#MAKE SURE YOUR CODE COMPILES WITH THESE FLAGS!
#WARNINGS = NO COMPILE = ZERO!
#also can add to the list of flags if you so desire. At your own risk. 



#from https://gcc.gnu.org/onlinedocs/gcc/

#-g : 
#   Produce debugging information in the operating system's native format
#   enables use of extra debugging information that only GDB can use; this extra information makes debugging work better in GDB

#-Wall :
#   This enables all the warnings about constructions
#   Basically just more warnings to prevent mistakes that cs2050 students are prone to making

#-Werror :
#   Make all warnings into errors. 
CFLAGS = -g -Wall -Werror



# Compile the entire program, but not build anything
# Running just "make" should do the same as "make all"
# 
all: Gauntlet


# compile game, shop, heroes, and io. I added parse, boss, and fight to HW2's makefile
Gauntlet: game.o shop.o heroes.o io.o parse.o boss.o fight.o
	gcc $^ -g -o Gauntlet
# -o : places output of make into an executible file (replace a.out with Gauntlet)




# this tells make how to build .o files from .c files
#notice that it compiles with the flags that i described earlier
# $@ specifies that it is the target
%.o: %.c game.h
	gcc $< -c $(CFLAGS) -o $@

# tells makefile how to delete all the object files and executable
# -f is the world's greatest flag because it makes the computer shut up
# and remove the files you tell it to
clean:
	rm -f *.o Gauntlet
