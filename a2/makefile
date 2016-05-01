
all: a2

TARGET = -mmacosx-version-min=10.8
LIBS = -F/System/Library/Frameworks -framework OpenGL -framework GLUT

a2: a2.c imageData.c a2.h camera.c draw.c
	clang -lm -g a2.c imageData.c camera.c draw.c -o a2 $(LIBS) $(TARGET)


testRun: a2 run

run:
	./a2 textures/texture2.pgm


test: test.c imageData.c
	clang -lm -g test.c imageData.c -o a2test
	./a2test textures/feep.pgm