#include <stdio.h>
#include "scanner.h"
#include "beamerWrite.c"
#include "lex.yy.c"
#define BETWEEN(value, min, max) (value <= max && value >= min)

#define MAX_INCLUDE_DEPTH 10
#define ROWS 512
#define	COLUMNS 2
YY_BUFFER_STATE include_stack[MAX_INCLUDE_DEPTH];
int include_stack_ptr = 0;

extern int yylex();
extern int yylineno;
extern char* yytext;


int currentLine;
struct Token token;


char *defineTable[ROWS][COLUMNS];
int cant_define;
char* replacement;
char* outputName;

void rmQuote(char *d , char *s)
{
	if (*s=='"')
		s++;
	while (*d++=*s++)
		if (*s=='"')
			s++;
} 

void strgcpy(char *d , char *s)
{
	while (*d++);
	for (--d;*d++=*s++;);
} 

int strgcmp(char *d, char *s)
{
	int i =0;
	int state = 0;
	for (i = 0; d[i]!='\0'; i++)
		if (d[i]!=s[i])
			return 0;
	return 1;
}

void reset(char *d)
{
	while (*d++='\0');
} 

void read_includes()
{
	while(token.tokenId == SEPARATOR)
	{
		getToken();
	}
	//printf("%s\n", token.lexeme);
	if (token.tokenId == STRING)
	{
		if ( include_stack_ptr >= MAX_INCLUDE_DEPTH )
        {
            fprintf( stderr, "Includes nested too deeply" );
            exit( 1 );
        }
        
        rmQuote(outputName, token.lexeme);
		//printf("FILE: %s\n", outputName);

        include_stack[include_stack_ptr++] = YY_CURRENT_BUFFER;
        

        yyin = fopen( outputName, "r" );

        if ( ! yyin )
            printf("No yyin\n");

        yy_switch_to_buffer( yy_create_buffer( yyin, YY_BUF_SIZE ) );
	}
	
	reset(outputName);
}

void read_define()
{
	int backslash = 0;
	while(token.tokenId == SEPARATOR)
	{
		getToken();
	}
	
	strgcpy(defineTable[cant_define][0], yytext);
	//printf("Lexema %s\n", defineTable[cant_define][0]);
	getToken();
	getToken();
	
	while(token.tokenId == SEPARATOR)
	{
		getToken();
	}
	while(*yytext != '\n' | backslash)
	{
		if (token.tokenId == BACKSLASH)
			backslash = 1;
		else if (*yytext == '\n')
			backslash = 0;
		else if (*yytext == '\t')
		{
			getToken();
			continue;
		}
		else
		{
			strgcpy(defineTable[cant_define][1], yytext);
		}	
		getToken();
	}
	cant_define++;
}

void replace_define()
{
	int i;
	for(i = 0; i<cant_define; i++)
	{
		
		if (strgcmp(yytext, defineTable[i][0]) != 0)
		{
			//printf("Lexema 1%s\n", defineTable[i][0]);
			//printf("Lexema 2%s\n", yytext);
			strgcpy(replacement, defineTable[i][1]);
			//printf("Lexema %s\n", replacement);
			break;
		}
	}
}



int preprocessor(void) 
{
	getToken();
	
	outputName = malloc(20 * sizeof(char));
	replacement = malloc(1000 * sizeof(char)); 
	reset(replacement);
	int i, j;
	for(i=0; i<ROWS; i++)
	{
		defineTable[i][0] = malloc(20 * sizeof(char));
		defineTable[i][1] = malloc(1000 * sizeof(char));
	}
	
	
	FILE* out_file;
	out_file = fopen("output.c", "w");
    yyout = out_file;
	
	while(token.tokenId) 
	{
		//printf("%s\n", token.tokenId);
		if (token.tokenId == INCLUDE) //include found
		{
			getToken();                               
			read_includes();
	        
	    }
	    if (token.tokenId == DEFINE) //define found
		{
			getToken();                               
			read_define();
	        
	    }
	    if (token.tokenId == ID) //posible macro found
		{
			replace_define();
	        
	        
		    
	    }
	    if(*replacement!='\0')
	    {
	    	fprintf(yyout, "%s", replacement);
	        reset(replacement);
	    }
	    else
	    	fprintf(yyout, "%s", yytext);
		getToken();
	    //printf("Token: %s\n", yytext);
		
		if (token.tokenId == 0)
		{
			if ( --include_stack_ptr < 0 )
		    {
		        break;
		    }
		
		    else
		    {
		    	//printf("Deberia pasar por aqui");
		        yy_delete_buffer( YY_CURRENT_BUFFER );
		        yy_switch_to_buffer(include_stack[include_stack_ptr] );
		        //printf("Token: %s\n", yytext);
		        getToken();
		    }
		}
	}
	
	fclose(out_file);
	free(outputName);
	return 0;
}


void compileLatex(){
	//system("pdflatex latex/result.tex && evince result.pdf -f" );
}

int main(void) 
{
	cant_define = 0;
	preprocessor();
	
	yyin = fopen( "output.c", "r" );

    if ( ! yyin )
        printf("No yyin\n");

    yy_switch_to_buffer( yy_create_buffer( yyin, YY_BUF_SIZE ) );

    FILE* out_file;
	out_file = fopen("scannedFile.txt", "w");
    yyout = out_file;
	
	getToken();
	currentLine = token.lineNo;
	//system("rm latex/result.tex");
	//copy(TEMPLATE_HEAD, BEAMER_FILE);
	while(token.tokenId) 
	{
		
		//while (currentLine == token.lineNo && token.tokenId){
			
			fprintf(yyout, "%s ", getTokenFamily(token.tokenId));
			/*if (token.tokenId==100){
				writeSeparator(token.lexeme);
				getToken();
				continue;
			}
			//printf("%s has id %d, is a lexeme from %s in line %d and is of family %s\n", token.lexeme, token.tokenId ,token.lexicalCategory, token.lineNo, token.CTokenFamily);
			addToken(token); */
			getToken();
		//}
		//currentLine = token.lineNo;
	}
	//beamerEndCCode();
	//writeStatistics();
	//appendToFile(BEAMER_FILE, "\n\n\\end{document}");
	//compileLatex();
	yyterminate();
	fclose(out_file);
	free(outputName);
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
	else if (token.tokenId == 100){
		return yytext;
	}
	return "\n";
}