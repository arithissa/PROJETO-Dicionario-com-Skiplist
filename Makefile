objects =   dicionario.o main.o

all :   $(objects)
	gcc -o  alg $(objects)

run :   alg
	./alg

dicionario.o :   dicionario.h
main.o  :   dicionario.h

clean   :
	rm *.o alg
