compiler = clang
all: cp.o mv.o ls.o rm.o
	${compiler} cp.o -o cp.out
	${compiler} mv.o -o mv.out
	${compiler} ls.o -o ls.out
	${compiler} rm.o -o rm.out
cp.o: cp.c
	${compiler} -c cp.c 
mv.o: mv.c
	${compiler} -c mv.c
ls.o: ls.c
	${compiler} -c ls.c
rm.o: rm.c
	${compiler} -c rm.c
redo:clean all
clean:
	rm -f cp.o ls.o mv.o rm.o
	rm -f cp.out mv.out ls.out rm.out