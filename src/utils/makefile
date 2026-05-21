all:
	gcc -fPIC -c singly.c -o singly.o
	gcc -fPIC -c utils.c -o utils.o
	gcc -shared -o utils.dll singly.o utils.o
	cmd /c move *.dll ../../
	cmd /c move *.o ../objs
	cd ../..