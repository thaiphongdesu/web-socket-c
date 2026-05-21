all:
	gcc -fPIC -c log.c -o log.o
	gcc -shared -o log.dll log.o
	cmd /c move *.dll ../../
	cmd /c move *.o ../objs
	cd ../..