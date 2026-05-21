MV = $(if $(OS), cmd /c move,mv)

all:
	gcc -fPIC -c log.c -o log.o
	gcc -shared -o log.dll log.o
	$(MV) *.dll ../../
	$(MV) *.o ../objs
	cd ../..