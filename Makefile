# Yes, I know this isn't a proper Makefile

all:
	bison json_parser.y
	flex json_scanner.l
	gcc -Wall main.c json_parser.tab.c json_scanner.yy.c -o jsonval

clean:
	rm -f jsonval json_parser.tab.c json_parser.tab.h json_scanner.yy.c json_scanner.yy.h
