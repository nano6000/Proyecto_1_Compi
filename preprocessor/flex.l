%{
#include <stdio.h>
#include "../token.h"
int reprocess = 0;
%}

CONSTANT        (-)?[0-9]+|"0x"[A-F0-9]{1,4}
AUTO            "auto"
BREAK           "break"
CASE            "case"
CHARACTER       "char"
CONST           "const"
CONTINUE        "continue"
DEFAULT         "default"
DO              "do"
DOUBLE          "double"
ELSE            "else"
ENUM            "enum"
EXTERN          "extern"
FLOAT           "float"
FOR             "for"
FORTRAN         "fortran"
GOTO            "goto"
IF              "if"
INLINE          "inline"
INT             "int"
LONG            "long"
REGISTER        "register"
RESTRICT        "restrict"
RETURN          "return"
SHORT           "short"
SIGNED          "signed"
STATIC          "static"
STRUCT          "struct"
SWITCH          "switch"
TYPEDEF         "typedef"
UNION           "union"
UNSIGNED        "unsigned"
VOID            "void"
VOLATILE        "volatile"
WHILE           "while"


EQUALS					\=
PLUS				    \+
MINUS		        	\-
STAR		        	\*
SLASHX2     			\/\/
MODULO					\%
PLUSX2  				\+\+
MINUSX2 				\-\-
EQUALX2      			\=\=
EXCALAMATION_EQUALS		\!\=
GREATER_THAN			\>
LESS_THAN				\<
GREATER_THAN_EQUALS 	\>\=
LESSER_THAN_EQUALS		\<\=
EXCALAMATION    		\!
AMEPSANDX2				\&\&
PIPEX2					\|\|
TILDE   				\~
AMPERSAND				\&
PIPE    				\|
CARET   				\^
SHL						\<\<
SHR						\>\>
DOT						\.
QUESTION_MARK   		\?
SIZEOF					"sizeof"
COLON           		\:
ALIGNOF					"alignof"

QUOTE           \"
APOS            \'
LBRACE          \{
RBRACE          \}
LBRACKET        \[
RBRACKET        \]
LPARENTHESIS    \(
RPARENTHESIS    \)
COMMA           \,
SEMICOLON       \;
ELIPSIS         \.\.\.


ID		    	[_a-zA-Z][_a-zA-Z0-9]*
STRING		    \"(\\.|[^\\"])*\"
CHAR 	    	\'[^\n|\n]\'
ERROR	    	{APOS}ID{APOS}
COMMENT		    ("/*"[^*]*[*]+([^/*][^*]*[*]+)*[/])|"//".*



INCLUDE         "#include"
DEF             "#define"
FILE            [a-zA-Z0-9]+[.][a-zA-Z0-9]+

%%

{CONSTANT}		return CONSTANT;

{AUTO}		    return AUTO;
{BREAK}		    return BREAK;
{CASE}		    return CASE;
{CHAR}	    	return CHAR;
{CONST}	    	return CONST;
{CONTINUE}		return CONTINUE;
{DEFAULT}		return DEFAULT;
{DO}	    	return DO;
{DOUBLE}		return DOUBLE;
{ELSE}	    	return ELSE;
{ENUM}	    	return ENUM;
{EXTERN}		return EXTERN;
{FLOAT}	    	return FLOAT;
{FOR}	    	return FOR;
{FORTRAN}		return FORTRAN;
{GOTO}	    	return GOTO;
{IF}	    	return IF;
{INLINE}		return INLINE;
{INT}	    	return INT;
{LONG}	    	return LONG;
{REGISTER}		return REGISTER;
{RESTRICT}		return RESTRICT;
{RETURN}		return RETURN;
{SHORT}	    	return SHORT;
{SIGNED}		return SIGNED;
{STATIC}		return STATIC;
{STRUCT}		return STRUCT;
{SWITCH}		return SWITCH;
{TYPEDEF}		return TYPEDEF;
{UNION}	    	return UNION;
{UNSIGNED}		return UNSIGNED;
{VOID}		    return VOID;
{VOLATILE}		return VOLATILE;
{WHILE}		    return WHILE;


{EQUALS}	    	    return EQUALS;
{PLUS}		            return PLUS;
{MINUS}		            return MINUS;
{STAR}		            return STAR;
{MODULO}		        return MODULO;
{EXCALAMATION_EQUALS}	return EXCALAMATION_EQUALS;
{GREATER_THAN}		    return GREATER_THAN;
{LESS_THAN}             return LESS_THAN;
{GREATER_THAN_EQUALS}   return GREATER_THAN_EQUALS;
{LESSER_THAN_EQUALS}	return LESSER_THAN_EQUALS;
{EXCALAMATION}		    return EXCALAMATION;
{AMEPSANDX2}		    return AMEPSANDX2;
{PIPEX2}		        return PIPEX2;
{TILDE}	        	    return TILDE;
{AMPERSAND}		        return AMPERSAND;
{PIPE}		            return PIPE;
{CARET}		            return CARET;
{SHL}		            return SHL;
{SHR}		            return SHR;
{DOT}		            return DOT;
{QUESTION_MARK}		    return QUESTION_MARK;
{SIZEOF}		        return SIZEOF;
{COLON}		            return COLON;
{ALIGNOF}		        return ALIGNOF;
{QUOTE}                 return QUOTE;
{APOS}                  return APOS;
{LBRACE}                return LBRACE;
{RBRACE}                return RBRACE;
{LPARENTHESIS}          return LPARENTHESIS;
{RPARENTHESIS}          return RPARENTHESIS;
{COMMA}                 return COMMA;
{SEMICOLON}             return SEMICOLON;
{ELIPSIS}               return ELIPSIS;
{LBRACKET}              return LBRACKET;
{RBRACKET}              return RBRACKET;


{INCLUDE}               return INCLUDE;




{FILE}      return FILENAME;
{ID}			return ID;
[ \t\n]			return SEPARATOR;
<<EOF>>         return 0;
{COMMENT}		;
.				{printf("TOKEN: %s irreconocible en la linea: %d\n", yytext, yylineno);}




%%

int yywrap(void)
{
	return 1;
}
