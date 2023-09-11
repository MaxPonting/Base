# Compiler
CC = g++

# Compiler Flags
FLAGS = -Wall
TFLAGS = -g3 -ggdb 
PFLAGS = -O3
DFLAGS = -g3 -ggdb -Wextra
RFLAGS = -O3 -mwindows

# Source Files
SRC = src/log/*.cpp src/allocator/*.cpp src/file/*.cpp src/math/*.cpp
TSRC = src/main.cpp 

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
	ar -rcs bin/debug/libbase.a *.o
	make clean

release:
	$(CC) $(FLAGS) $(RFLAGS) -c $(SRC) $(INC)
	ar -rcs bin/release/libbase.a *.o
	make clean

clean:
	del *.o *.c.obj

	
