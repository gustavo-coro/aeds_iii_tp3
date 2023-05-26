all: main

main: main.o ler_arquivo.o lista.o processamento_texto.o
	gcc -o tp3 main.o ler_arquivo.o lista.o processamento_texto.o

main.o: main.c ler_arquivo.c lista.c processamento_texto.c
	gcc -o main.o main.c -c -W -Wall -ansi -pedantic -std=c99

ler_arquivo.o: ler_arquivo.c ler_arquivo.h
	gcc -o ler_arquivo.o ler_arquivo.c -c -W -Wall -ansi -pedantic -std=c99

lista.o: lista.c lista.h
	gcc -o lista.o lista.c -c -W -Wall -ansi -pedantic -std=c99

processamento_texto.o: processamento_texto.c processamento_texto.h
	gcc -o processamento_texto.o processamento_texto.c -c -W -Wall -ansi -pedantic -std=c99

clean:
	rm -rf *.o *~ tp3