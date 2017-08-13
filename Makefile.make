edit:main.o md5.o
	cc -o edit main.o md5.o

main.o:main.c
	cc -c main.c
md5.o:md5.c
	cc -c md5.c
clean:
	rm edit main.o md5.o	