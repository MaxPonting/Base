CC = gcc
FLAGS = -Wall -Wextra
DFLAGS = -g -ggdb -Og
RFLAGS = -O3
SRC = src/allocator/*.c src/array/*.c src/string/*.c
TSRC = $(SRC) src/main.c

test:
	$(CC) $(FLAGS) $(DFLAGS) $(TSRC) -o bin/test/base.exe & cd bin/test & base.exe

performance:
	$(CC) $(FLAGS) $(RFLAGS) $(TSRC) -o bin/performance/base.exe & cd bin/performance & base.exe

debug:
	$(CC) $(FLAGS) $(DFLAGS) $(SRC) -c $(SRC)
	ar -rcs bin/debug/libBase.a *.o
	make clean

release:
	$(CC) $(FLAGS) $(RFLAGS) $(SRC) -c $(SRC)
	ar -rcs bin/release/libBase.a *.o
	make clean

clean:
	del *.o 

	
