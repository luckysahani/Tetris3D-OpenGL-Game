INC = -I./src
LDFLAGS = $(INC) -L/usr/X11R6/lib -lGL -lGLU -lglut -lm
CC = gcc

main: clean
	$(CC) src/placer.h src/placer.c src/table.h src/table.c src/main.c src/glm.h src/glm.c src/block.h src/block.c src/base.h src/base.c src/viewer.h src/viewer.c $(LDFLAGS) -o base

clean:
	rm -rf base
