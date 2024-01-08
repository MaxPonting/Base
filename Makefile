# Operating System
ifeq ($(OS), Windows_NT)
	DOS := Windows
else
	DOS := $(shell uname)
endif

# Compiler
CC = g++

# Compiler Flags
FLAGS = -Wall -Wextra -Wno-cast-function-type -Wno-missing-field-initializers
DFLAGS = -g3 -ggdb 
RFLAGS = -O2
ifeq ($(DOS), Windows)
DIFLAGS = -O2 -static -static-libgcc -static-libstdc++
endif
ifeq ($(DOS), Linux)
DIFLAGS = -O2 -static-libgcc -static-libstdc++
endif

# Source File
SRC = src/physics.cpp

# Include Directory
INC = -I include/

# Linker Files
ifeq ($(DOS), Windows)
LINK = -lopengl32 -lgdi32 -lWinmm
endif
ifeq ($(DOS), Linux)
LINK = -lGL -lX11
endif

# Windows
ifeq ($(DOS), Windows)
clean:
	del /S bin\debug\*
	del /S bin\release\*
	del /S bin\distribution\*

debug: 
	$(CC) $(FLAGS) $(DFLAGS) $(SRC) $(INC) $(LINK) -o bin/debug/windows.exe 
	bin/debug/windows.exe

release:
	$(CC) $(FLAGS) $(RFLAGS) $(SRC) $(INC) $(LINK) -o bin/release/windows.exe
	bin/release/windows.exe

distribution:
	$(CC) $(FLAGS) $(DIFLAGS) $(SRC) $(INC) $(LINK) -o bin/distribution/windows.exe 
	bin/distribution/windows.exe

endif

# Linux
ifeq ($(DOS), Linux)
clean:
	rm -r bin/debug/*
	rm -r bin/release/*
	rm -r bin/distribution/*

debug:
	$(CC) $(FLAGS) $(DFLAGS) $(SRC) $(INC) $(LINK) -o bin/debug/linux.exe 
	bin/debug/linux.exe

release:
	$(CC) $(FLAGS) $(RFLAGS) $(SRC) $(INC) $(LINK) -o bin/release/linux.exe
	bin/release/linux.exe

distribution:
	$(CC) $(FLAGS) $(DIFLAGS) $(SRC) $(INC) $(LINK) -o bin/distribution/linux.exe 
	bin/distribution/linux.exe
endif




	
