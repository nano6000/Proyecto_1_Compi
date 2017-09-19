#include <stdio.h>
#include "scanner.h"
#include "beamerWrite.c"
#define BETWEEN(value, min, max) (value <= max && value >= min)

extern int yylex();
extern int yylineno;
extern char* yytext;



int currentLine;
struct Token token;

void compileLatex(){
	system("pdflatex latex/result.tex" );
}

int main(void) 
{
	getToken();
	currentLine = token.lineNo;
	system("rm latex/result.tex");
	copy(TEMPLATE_HEAD, BEAMER_FILE);
	while(token.tokenId) 
	{
		
		while (currentLine == token.lineNo && token.tokenId){
			
			if (token.tokenId==100){
				writeSeparator(token.lexeme);
				getToken();
				continue;
			}
			//printf("%s has id %d, is a lexeme from %s in line %d and is of family %s\n", token.lexeme, token.tokenId ,token.lexicalCategory, token.lineNo, token.CTokenFamily);
			addToken(token); 
			getToken();
		}
		currentLine = token.lineNo;
	}
	beamerEndCCode();
	writeStatistics();
	appendToFile(BEAMER_FILE, "\n\n\\end{document}");
	compileLatex();
	return 0;
}

struct Token getToken(){
	token.tokenId = yylex();
	token.lexicalCategory = names[token.tokenId];
	token.CTokenFamily = getTokenFamily(token.tokenId);
	token.lexeme = yytext;
	token.lineNo = yylineno;
}

char *getTokenFamily(int tokenId){
	if (tokenId == CONSTANT){
		return "CONSTANT";
	}else if(tokenId == INCLUDE){
		return "INCLUDE";
	}
	else if (tokenId == STRING){
		return "STRING";
	}
	else if (tokenId == ID){
		return "ID";
	}
	else if (tokenId <= 34){
		return "KEYWORD";
	}
	else if (BETWEEN(tokenId, 35, 62)){
		return "OPERATOR";
	}
	else if (BETWEEN(tokenId, 63, 78)){
		return "PUNCTUATOR";
	}
	return 0;
}