#Para escrever comentários ##
############################# Makefile ##########################
all: lib.h.gch llrbt.h.gch indexer

lib.h.gch: lib.h
	gcc -c -I"pwd" lib.h
llrbt.h.gch: llrbt.h
	gcc -c -I"pwd" llrbt.h
indexer: indexer.c
	gcc -o indexer indexer.c -lpthread -lm
clean:
	rm -rf *.gch
mrproper: clean
	rm -rf indexer