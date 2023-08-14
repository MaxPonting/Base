# Compiler
CC = gcc

# Compiler Flags
FLAGS = -Wall
TFLAGS = -g3 -ggdb 
PFLAGS = -O3
DFLAGS = -g3 -ggdb -Wextra
RFLAGS = -O3 -mwindows

# Source Files
SRC = src/log/*.c src/allocator/*.c src/array/*.c src/string/*.c src/window/*.c src/opengl/*.c src/file/*.c src/math/*.c src/nuklear/*.c
TSRC = src/test.c 

# Include Directory
INC = -I include/

test: 
	$(CC) $(FLAGS) $(TFLAGS) $(TSRC) $(INC) -L bin/debug/ -lbase -o bin/test/test.exe & cd bin/test & test.exe

performance:
	$(CC) $(FLAGS) $(PFLAGS) $(TSRC) $(INC) -L bin/release/ -lbase -o bin/performance/performance.exe & cd bin/performance & performance.exe

all:
	make debug
	make release

debug:
	$(CC) $(FLAGS) $(DFLAGS) -c $(SRC) $(INC)
	ar -x dep/libglfw3.a
	ar -x dep/libgdi32.a
	ar -x dep/libopengl32.a
	ar -x dep/libglad.a
	ar -rcs bin/debug/libbase.a *.o *.c.obj
	make clean

release:
	$(CC) $(FLAGS) $(RFLAGS) -c $(SRC) $(INC)
	ar -x dep/libglfw3.a
	ar -x dep/libgdi32.a
	ar -x dep/libopengl32.a
	ar -x dep/libglad.a
	ar -rcs bin/release/libbase.a *.o *.c.obj
	make clean

clean:
	del *.o *.c.obj

	
