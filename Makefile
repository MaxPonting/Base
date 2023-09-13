# Compiler
CC = g++

# Compiler Flags
FLAGS = -Wall
DFLAGS = -g3 -ggdb -Wextra -Wno-cast-function-type
RFLAGS = -O3

# Source File
SRC = src/main.cpp

# Include Directory
INC = -I include/

# Linker Files
LINK = -lopengl32 -lgdi32

debug: 
	$(CC) $(FLAGS) $(DFLAGS) $(SRC) $(INC) $(LINK) -o bin/debug/debug.exe & cd bin/debug & debug.exe

release:
	$(CC) $(FLAGS) $(RFLAGS) $(SRC) $(INC) $(LINK) -o bin/release/release.exe & cd bin/release & release.exe



	
