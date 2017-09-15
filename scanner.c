#include <stdio.h>
#include "token.h"

extern int yylex();
extern int yylineno;
extern char* yytext;

char *names[] = {NULL, "CONSTANT", "ID", "SEMICOLON", "KEYWORD", "L_BRACKET", 
					"R_BRACKET", "L_PARENT", "R_PARENT", "CHAR", "STRING", "QUOTE", "APOS"};

int main(void) 
{
	int token;

	token = yylex();
	while(token) 
	{
		printf("%s is set to %s\n", names[token], yytext);
		token = yylex();
	}
	return 0;
}