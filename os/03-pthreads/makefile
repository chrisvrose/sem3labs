all: multiply.c cross.c
	mkdir -p builds/
	gcc multiply.c -o multiply.out -pthread
	gcc cross.c -o cross.out -pthread
clean:
	rm -vrf builds/
