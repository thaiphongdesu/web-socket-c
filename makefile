lib:
	gcc -fPIC -c singly.c -o singly.o
	gcc -fPIC -c utils.c -o utils.o
	gcc -shared -o utils.dll singly.o utils.o
	
exe: utils.dll
	gcc singly.c utils.c server.c test.c -L. -lutils -lws2_32 -o server

run: exe
	./server.exe

all: lib exe

clean:
	del *.exe
	del *.o
	del *.dll