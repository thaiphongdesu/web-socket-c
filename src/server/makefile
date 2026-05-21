OBJS_PATH = ../objs/
MV = $(if $(OS), cmd /c move,mv)

all:
	gcc -fPIC -c server.c -lws2_32 -o server.o
	$(MV) *.o ../objs
	cd ../..