OBJS_PATH = src\objs
OBJS = /src/objs/*.o
DYN_PATH = .

log:
	cd src/log && make all
	
util:
	cd src/utils && make all

server:
	cd src/server && make all
	
exe:
	gcc $(OBJS_PATH)\singly.o $(OBJS_PATH)\utils.o $(OBJS_PATH)\server.o test.c -L$(DYN_PATH) -lutils -L$(DYN_PATH) -llog -lws2_32 -o server

run: exe
	./server.exe

all: util server exe

clean:
	del *.exe
	del src\objs\*.o
	del *.dll

