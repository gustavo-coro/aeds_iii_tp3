all: main

main: main.o ler_arquivo.o lista.o processamento_texto.o calcula_casamento.o gerenciaTempo.o
	gcc -o tp3 main.o ler_arquivo.o lista.o processamento_texto.o calcula_casamento.o gerenciaTempo.o

main.o: src/main.c src/ler_arquivo.c src/lista.c src/processamento_texto.c src/calcula_casamento.c src/gerenciaTempo.c include/main.h
	gcc -o main.o src/main.c -c -W -Wall -ansi -pedantic -std=c99

ler_arquivo.o: src/ler_arquivo.c include/ler_arquivo.h
	gcc -o ler_arquivo.o src/ler_arquivo.c -c -W -Wall -ansi -pedantic -std=c99

lista.o: src/lista.c include/lista.h
	gcc -o lista.o src/lista.c -c -W -Wall -ansi -pedantic -std=c99

processamento_texto.o: src/processamento_texto.c include/processamento_texto.h
	gcc -o processamento_texto.o src/processamento_texto.c -c -W -Wall -ansi -pedantic -std=c99

calcula_casamento.o: src/calcula_casamento.c include/calcula_casamento.h
	gcc -o calcula_casamento.o src/calcula_casamento.c -c -W -Wall -ansi -pedantic -std=c99

gerenciaTempo.o: src/gerenciaTempo.c include/gerenciaTempo.h
	gcc -o gerenciaTempo.o src/gerenciaTempo.c -c -W -Wall -ansi -pedantic -std=c99

clean:
	rm -rf *.o *~ tp3