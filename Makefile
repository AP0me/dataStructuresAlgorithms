all:
	gcc sym.c -o ./bin/sym.exe
	gcc InitImg.c -o ./bin/InitImg.exe
	./bin/InitImg.exe 100
	./bin/sym.exe -s 200 output 1000