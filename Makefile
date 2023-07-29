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

# Include Directory
INC = -I include/

test:
	make debug
	$(CC) $(FLAGS) $(TFLAGS) $(TSRC) $(INC) -L bin/debug/ -lbase -o bin/test/test.exe & cd bin/test & test.exe

performance:
	make release
	$(CC) $(FLAGS) $(RFLAGS) $(PSRC) $(INC) -L bin/debug/ -lbase -o bin/performance/performance.exe & cd bin/performance & performance.exe

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

	
