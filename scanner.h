#include "token.h"

struct Token {
    int tokenId;            //Value assigned to a token
	char *lexicalCategory;	//Token type, such as LBACE, etc.
	char *lexeme;			//The expression correpsonding to certain token
	char *CTokenFamily;      //According to 6 kinds of tokens that C has https://msdn.microsoft.com/en-us/library/c6sb2c6b.aspx
	int	  lineNo;			//Number of the line where the token is located
} Token;

char *names[] = {NULL, "AUTO" ,"BREAK" ,"CASE" ,"CHARACTER" ,"CONST" ,"CONTINUE" ,"DEFAULT" ,"DO" ,"DOUBLE" ,"ELSE" ,"ENUM" ,"EXTERN" ,"FLOAT" ,"FOR" ,"FORTRAN" ,"GOTO" ,"IF" ,"INLINE" ,"INT" ,"LONG" ,"REGISTER" ,"RESTRICT" ,"RETURN" ,"SHORT" ,"SIGNED" ,"STATIC" ,"STRUCT" ,"SWITCH" ,"TYPEDEF" ,"UNION" ,"UNSIGNED" ,"VOID" ,"VOLATILE" ,"WHILE" ,"EQUALS" ,"PLUS" ,"MINUS" ,"STAR" ,"SLASHX" ,"MODULO" ,"PLUSX" ,"MINUSX" ,"EQUALX" ,"EXCALAMATION_EQUALS" ,"GREATER_THAN" ,"LESS_THAN" ,"GREATER_THAN_EQUALS" ,"LESSER_THAN_EQUALS" ,"EXCALAMATION" ,"AMEPSANDX" ,"PIPEX" ,"TILDE" ,"AMPERSAND" ,"PIPE" ,"CARET" ,"SHL" ,"SHR" ,"DOT" ,"QUESTION_MARK" ,"SIZEOF" ,"COLON" ,"ALIGNOF" ,"QUOTE" ,"APOS" ,"LBRACE" ,"RBRACE" ,"LBRACKET" ,"RBRACKET" ,"COMMA" ,"SEMICOLON" ,"ELIPSIS" ,"ID" ,"STRING" ,"CHAR" ,"ERROR" ,"CONSTANT" ,"LPARENTHESIS" ,"RPARENTHESIS", "INCLUDE", "DEFINE", "SPACE", "TAB","NEWLINE"};
struct Token getToken();

char *getTokenFamily(int tokenId);

