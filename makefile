all: hexadoku01 hexadoku03 hexadoku18 hexadoku48

hexadoku01: hexadoku01.c
	gcc -o hexadoku01 hexadoku01.c
hexadoku03: sudoku03.c
	gcc -o hexadoku03 hexadoku03.c
hexadoku18: sudoku18.c
	gcc -o hexadoku18 hexadoku18.c
hexadoku48: sudoku48.c
	gcc -o hexadoku48 hexadoku48.c