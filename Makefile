lineNum: lineNum.c
	gcc -o lineNum lineNum.c



run: lineNum
	./lineNum

clean:
	rm lineNum