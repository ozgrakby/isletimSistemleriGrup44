all: compile run

compile:
	gcc -I ./include/ -o ./lib/prompt.o -c ./src/prompt.c
	gcc -I ./include/ -o ./bin/shell.out ./lib/prompt.o ./src/shell.c

run:
	./bin/shell.out