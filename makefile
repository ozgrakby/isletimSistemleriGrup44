all: compile run

compile:
	gcc -I ./include/ -o ./lib/prompt.o -c ./src/prompt.c
	gcc -I ./include/ -o ./lib/girisyonlendirme.o -c ./src/girisyonlendirme.c
	gcc -I ./include/ -o ./lib/cikisyonlendirme.o -c ./src/cikisyonlendirme.c
	gcc -I ./include/ -o ./lib/arkaplancalisma.o -c ./src/arkaplancalisma.c
	gcc -I ./include/ -o ./bin/shell.out ./lib/prompt.o ./lib/girisyonlendirme.o ./lib/cikisyonlendirme.o ./lib/arkaplancalisma.o ./src/shell.c

run:
	./bin/shell.out