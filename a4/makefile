
all: a4

TARGET = -mmacosx-version-min=10.8
LIBS = -F/System/Library/Frameworks -framework OpenGL -framework GLUT
FILE = inputs/test1

a4: a4.c a4.h fileData.c ray.c
	clang a4.c fileData.c ray.c -o a4 $(LIBS) $(TARGET)


run: all
	./a4 $(FILE)

test: testMain.c fileData.c
	clang -lm testMain.c fileData.c ray.c -g -o a4test $(LIBS) $(TARGET)
	./a4test $(FILE)