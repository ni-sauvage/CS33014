all: csu33014-annual-q2-code.c  csu33014-annual-q2-main.c csu33014-annual-q2-code.h
	gcc -O2 -o finddups csu33014-annual-q2-code.c -fopenmp csu33014-annual-q2-main.c

debug: csu33014-annual-q2-code.c  csu33014-annual-q2-main.c csu33014-annual-q2-code.h
	gcc -g -o finddups csu33014-annual-q2-code.c  csu33014-annual-q2-main.c

sanitize: csu33014-annual-q2-code.c  csu33014-annual-q2-main.c csu33014-annual-q2-code.h
	gcc -g  -fsanitize=address -o finddups csu33014-annual-q2-code.c  csu33014-annual-q2-main.c 

test: all
	./finddups 2000

time: all
	./finddups 20000
