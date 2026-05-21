MV = $(if $(OS), cmd /c move,mv)

all:
	gcc -fPIC -c singly.c -o singly.o
	gcc -fPIC -c utils.c -o utils.o
	gcc -shared -o utils.dll singly.o utils.o
	$(MV) *.dll ../../
	$(MV) *.o ../objs
	cd ../..