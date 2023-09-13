# Compiler
CC = g++

# Compiler Flags
FLAGS = -Wall
DFLAGS = -g3 -ggdb -Wextra
RFLAGS = -O3

# Source File
SRC = src/main.cpp 

# Include Directory
INC = -I include/

debug: 
	$(CC) $(FLAGS) $(DFLAGS) $(SRC) $(INC) -L bin/debug/ -o bin/debug/debug.exe & cd bin/debug & debug.exe

release:
	$(CC) $(FLAGS) $(RFLAGS) $(SRC) $(INC) -L bin/release/ -o bin/release/release.exe & cd bin/release & release.exe



	
