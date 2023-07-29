# Compiler
CC = gcc

# Compiler Flags
FLAGS = -Wall
TFLAGS = -g3 -ggdb
DFLAGS = -g3 -ggdb -Wextra
RFLAGS = -O3

# Source Files
SRC = src/allocator/*.c src/array/*.c src/string/*.c src/graphics/*.c 
TSRC = src/test.c 
PSRC = src/performance.c

# Build Include Directory
BINC = -I include/ -I dep/glfw/include -I dep/glad/include 

# Test Include Directory
TINC = -I include/

# Library Directories
LIB = -L dep/glfw/lib -L dep/gdi32/lib -L dep/opengl32/lib -L dep/glad/lib 

# Linker
LINK = -lglfw3 -lgdi32 -lopengl32 -lglad

# Builds

test:
	make debug
	$(CC) $(FLAGS) $(TFLAGS) $(TSRC) $(TINC) -L bin/debug/ -lbase -o bin/test/test.exe & cd bin/test & test.exe

performance:
	make release
	$(CC) $(FLAGS) $(RFLAGS) $(PSRC) $(TINC) -L bin/debug/ -lbase -o bin/performance/performance.exe & cd bin/performance & performance.exe

all:
	make debug
	make release

debug:
	$(CC) $(FLAGS) $(DFLAGS) -c $(SRC) $(BINC)
	ar -x dep/glfw/lib/libglfw3.a
	ar -x dep/gdi32/lib/libgdi32.a
	ar -x dep/opengl32/lib/libopengl32.a
	ar -rcs bin/debug/libbase.a *.o *.c.obj
	make clean

release:
	$(CC) $(FLAGS) $(RFLAGS) -c $(SRC) $(BINC)
	ar -x dep/glfw/lib/libglfw3.a
	ar -x dep/gdi32/lib/libgdi32.a
	ar -x dep/opengl32/lib/libopengl32.a
	ar -rcs bin/release/libbase.a *.o *.c.obj
	make clean

clean:
	del *.o *.c.obj

	
