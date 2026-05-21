OBJS_PATH = ../objs/

all:
	gcc -fPIC -c server.c -lws2_32 -o server.o
	cmd /c move *.o ../objs
	cd ../..