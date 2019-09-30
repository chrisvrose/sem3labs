all:main.o
	cc -I includes/  main.o -o main.out

main.o: main.c
	cc -c -I includes/ main.c -o main.o

run: all
	./main.out
