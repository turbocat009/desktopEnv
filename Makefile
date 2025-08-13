all: main background

main: src/main.c
	gcc -O2 -Wall -o bin/main src/main.c -I/opt/X11/include -L/opt/X11/lib -lX11

background: src/background.c
	gcc -o bin/background src/background.c -I/opt/homebrew/include/SDL2 -L/opt/homebrew/lib -lSDL2 -lSDL2_image -lSDL2_ttf

clean:
	rm -f main background
