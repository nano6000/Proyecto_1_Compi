%{
#include "token.h"
%}

CONSTANT	[0-9]+
KEYWORD		auto|break|case|char|const|continue|default|do|double|else|enum|extern|float|for|fortran|goto|if|inline|int|long|register|restrict|return|short|signed|sizeof|static|struct|switch|typedef|union|unsigned|void|volatile|while
ID			[_a-zA-Z][_a-zA-Z0-9]*
QUOTE		\"
APOS		\'
STRING		\"(\\.|[^\\"])*\"
CHAR 		{APOS}.?{APOS}
OPERATOR	\=|\+|\-|\*|\/|\/\/|\%|\+\+|\-\-|\=\=|\!\=|\>|\<|\>\=|\<\=|\!|\&\&|\|\||\~|\&|\||\^|\<\<|\>\>|\.|\?|sizeof|\:|alignof
PUNCTUATOR	\(|\)|\{|\}|\;|\[|\]
COMMENT		("/*"[^*]*[*]+([^/*][^*]*[*]+)*[/])|"//".*

%%

{CONSTANT}		return CONSTANT;
{KEYWORD}		return KEYWORD;
{STRING}		return STRING;
{OPERATOR}		return OPERATOR;
{PUNCTUATOR}	return PUNCTUATOR;
{ID}			return ID;
[ \t\n]			;
{COMMENT}		;
.				{printf("ERROR EN LINEA %d : -- Token %s\n", yylineno,yytext);}

%%

int yywrap(void)
{
	return 1;
}
