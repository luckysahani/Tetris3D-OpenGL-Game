INC = -I./src
LDFLAGS = $(INC) -L/usr/lib	-L/usr/X11R6/lib -lX11 -lGL -lGLU -lglut -ljpeg  -lm -lalut `pkg-config --libs freealut` 
CC = gcc
main: clean
	$(CC)  $(IFLAGS)  src/main.c src/glm.h src/glm.c src/block.h src/block.c src/base.h src/base.c src/viewer.h src/viewer.c   $(LDFLAGS) -o base

clean:
	rm -rf base
