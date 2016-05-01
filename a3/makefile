
all: a3

TARGET = -mmacosx-version-min=10.8
LIBS = -F/System/Library/Frameworks -framework OpenGL -framework GLUT

a3: a3.c imageData.c a3.h draw.c
	clang -lm -g a3.c imageData.c draw.c -o a3 $(LIBS) $(TARGET)


testRun: a3 run

run:
	./a3

testParse:
	clang -lm -g test.c imageData.c -o test $(TARGET)
	./test