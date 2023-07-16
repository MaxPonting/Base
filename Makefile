test:
	gcc -g -Wall -Wextra src/*.c -o bin/test/base.exe & cd bin/test & base.exe

performance:
	gcc -O3 src/*.c -o bin/performance/base.exe & cd bin/performance & base.exe

debug:
	gcc -g -c -Wall -Wextra src/*.c
	ar -rcs bin/debug/libBase.a *.o
	mv *.o bin/debug

release:
	gcc -c -O3 src/*.c
	ar -rcs bin/release/libBase.a *.o
	mv *.o bin/release

rm:
	rm *o