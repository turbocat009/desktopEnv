all: main background

main: src/main.c
	gcc -O2 -Wall -o bin/main src/main.c -I/opt/X11/include -L/opt/X11/lib -lX11

background: src/background.c
	gcc -o bin/background src/background.c -I/opt/X11/include -L/opt/X11/lib -lX11 -lpng

clean:
	rm -f main background
