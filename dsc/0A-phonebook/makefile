SRC := src
OBJ := builds/buildObjects

SOURCES := $(wildcard $(SRC)/*.c)
OBJS := $(pathsubst $(SRC)/%.c $(OBJ)/%.o

test:
	echo $SOURCES

all:main.o
	cc -I includes/  main.c::

main.o: main.c
	cc -c -I includes/ main.c -o main.o
