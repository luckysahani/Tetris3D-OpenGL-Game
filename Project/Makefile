INC = -I./src
LDFLAGS = $(INC) -L/usr/X11R6/lib -lGL -lGLU -lglut -lSOIL -lm -lalut `pkg-config --libs freealut`
CC = gcc
main: clean
	$(CC)    src/SOIL.h src/main.c src/glm.h src/glm.c src/block.h src/block.c src/base.h src/base.c src/viewer.h src/viewer.c   $(LDFLAGS) -o base

clean:
	rm -rf base
