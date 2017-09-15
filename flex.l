%{
#include "token.h"
%}

CONSTANT	[0-9]+
KEYWORD		auto|break|case|char|const|continue|default|do|double|else|enum|extern|float|for|fortran|goto|if|inline|int|long|register|restrict|return|short|signed|sizeof|static|struct|switch|typedef|union|unsigned|void|volatile|while
ID			[a-zA-z][_a-zA-Z0-9]*
QUOTE		\"
APOS		\'
STRING		{QUOTE}[.\n]*{QUOTE}
CHAR 		{APOS}.?{APOS}
ERROR		{APOS}ID{APOS}

%%

{CONSTANT}		return CONSTANT;
{KEYWORD}		return KEYWORD;
{ID}			return ID;
{STRING}		return STRING;
";"				return SEMICOLON;
"{"				return L_BRACKET;
"}"				return R_BRACKET;
"("				return L_PARENT;
")"				return R_PARENT;
"\""			return QUOTE;
"\'"			return APOS;
[ \t\n]			;
{CHAR}			return CHAR;

%%

int yywrap(void)
{
	return 1;
}
