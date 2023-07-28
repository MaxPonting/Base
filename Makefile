# Compiler
CC = gcc

# Compiler Flags
FLAGS = -Wall
TFLAGS = -g -ggdb
DFLAGS = -g -ggdb -Wextra
RFLAGS = -O3

# Source Files
SRC = src/allocator/*.c src/array/*.c src/string/*.c src/graphics/*.c
TSRC = $(SRC) src/test.c src/main.c

# Include Directories
INC = -I include/ -I dep/glfw/include -I dep/glad/include

# Library Directories
LIB = -L dep/glfw/lib -L dep/glad/lib 

# Linker
LINK = -lglfw3 -lgdi32 -lopengl32 -lglad

# Builds

test:
	$(CC) $(FLAGS) $(TFLAGS) $(TSRC) $(INC) $(LIB) $(LINK) -o bin/test/base.exe & cd bin/test & base.exe

performance:
	$(CC) $(FLAGS) $(RFLAGS) $(TSRC) $(INC) $(LIB) $(LINK) -o bin/performance/base.exe & cd bin/performance & base.exe

debug:
	$(CC) $(FLAGS) $(DFLAGS) -c $(SRC) $(INC) $(LIB) $(LINK)
	ar -rcs bin/debug/libBase.a *.o
	make clean

release:
	$(CC) $(FLAGS) $(RFLAGS) $(SRC) -c $(INC) $(LIB) $(LINK)
	ar -rcs bin/release/libBase.a *.o
	make clean

clean:
	del *.o 

	
