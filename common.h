#ifndef JSONVAL_COMMON_H
#define JSONVAL_COMMON_H

/*
 * Reference yylex() and yytext from flex
 */
typedef void* yyscan_t;
typedef int YYSTYPE;
extern int yylex (YYSTYPE* yylval_param, yyscan_t scanner);

extern void yyerror(yyscan_t, const char *);

#endif
