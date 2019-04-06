all: gtushell cat pwd wc bunedu lsf 

gtushell:
	gcc -c  -std=gnu99 gtushell.c -Wall
	gcc -o gtushell gtushell.o

cat:
	gcc -c  -std=gnu99 cat.c -Wall
	gcc -o cat cat.o

pwd:
	gcc -c  -std=gnu99 pwd.c -Wall
	gcc -o pwd pwd.o

wc:
	gcc -c  -std=gnu99 wc.c -Wall
	gcc -o wc wc.o

bunedu:
	gcc -c  -std=gnu99 bunedu.c -Wall
	gcc -o bunedu bunedu.o

lsf:
	gcc -c  -std=gnu99 lsf.c -Wall
	gcc -o lsf lsf.o

clean:
	rm -f *.o gtushell cat pwd wc bunedu lsf
