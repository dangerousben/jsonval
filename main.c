/*
    jsonval - validates JSON files for well-formedness
    Copyright (C) 2007 Ben Spencer

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include "json_parser.tab.h"
#include "json_scanner.yy.h"

extern int yyparse(yyscan_t scanner);
unsigned char parse_and_report(const char *);

int xml_output = 0;

int main(int argc, char *argv[])
{
	unsigned char err = 0;
	int c;

	while((c = getopt(argc, argv, "x")) != -1) {
		switch(c) {
		case 'x':
			xml_output = 1;
			break;
		}
	}

	if(xml_output) printf("<?xml version=\"1.0\" encoding=\"utf-8\"?>\n<jslint>\n");

	if((argc - optind) == 0) err = parse_and_report(NULL);
	else {
		unsigned int i;
		for(i = optind; i < argc; i++) {
			if(parse_and_report(argv[i])) err = 1;
		}
	}
	
	if(xml_output == 1)
	{
		printf("</jslint>\n");
	}

	if(xml_output) printf("</jslint>\n");

	return err;
}

unsigned char parse_and_report(const char *filename)
{
	yyscan_t scanner;
	FILE *f;
	unsigned char err = 0;

	if(filename == NULL || strcmp(filename, "-") == 0) {
		f = stdin;
		filename = "stdin";
	} else {
		f = fopen(filename, "r");
		if(!f) {
			perror(filename);
			return 1;
		}
	}
	
	yylex_init(&scanner);
	yyset_in(f, scanner);
	yyset_extra((void *) filename, scanner);
#ifdef DEBUG
	yyset_debug(1, scanner);
#endif

	if(xml_output) printf("\t<file name=\"%s\">\n", filename);

	switch(yyparse(scanner)) {
	case 0:
		if(!xml_output) printf("%s: valid JSON\n", filename);
		break;
	case 1:
		if(!xml_output) printf("%s: parsing failed\n", filename);
		err = 1;
		break;
	case 2:
		fprintf(stderr, "Out of memory\n");
		exit(1);
		break;
	}
	
	if(xml_output == 1)
	{
		printf("\t</file>\n");
	}

	if(xml_output) printf("\t</file>\n");

	yylex_destroy(scanner);
	if(f != stdin) fclose(f);

	return err;
}

void yyerror(yyscan_t scanner, const char *error)
{
	if(xml_output) {
		printf("\t\t<issue line=\"%d\" char=\"\" issue=\"%s\" evidence=\"\"/>\n",
		       yyget_lineno(scanner), error);
	} else {
		fprintf(stderr, "%s: %s at line %d\n",
			(char *) yyget_extra(scanner),
			error, yyget_lineno(scanner));
	}
}
