%{
#include "token.h"
%}

CONSTANT	[0-9]+
KEYWORD		int|main|return
ID			[a-zA-z][_a-zA-Z0-9]*
STRING		\"[.\n]*\"

%%

{CONSTANT}		return CONSTANT;
{KEYWORD}		return KEYWORD;
{ID}			return ID;
;				return SEMICOLON;
"{"				return L_BRACKET;
"}"				return R_BRACKET;
"("				return L_PARENT;
")"				return R_PARENT;
[ \t\n]			;

%%

int yywrap(void)
{
	return 1;
}
