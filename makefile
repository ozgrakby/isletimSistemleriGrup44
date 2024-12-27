all: compile run

compile:
	gcc -I ./include/ -o ./lib/prompt.o -c ./src/prompt.c
	gcc -I ./include/ -o ./lib/girisyonlendirme.o -c ./src/girisyonlendirme.c
	gcc -I ./include/ -o ./bin/shell.out ./lib/prompt.o ./lib/girisyonlendirme.o ./src/shell.c

run:
	./bin/shell.out
