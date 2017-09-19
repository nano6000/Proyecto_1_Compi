//#include "preprocessor.h"

#include <stdlib.h>
#include <string.h>
//#include <stdio.h>
//#include "lex.yy.c"


#define MAX_INCLUDE_DEPTH 10
YY_BUFFER_STATE include_stack[MAX_INCLUDE_DEPTH];
int include_stack_ptr = 0;

/*extern int yylex();
extern int yylineno;
extern char* yytext;
*/
char* outputName;

void rmQuote(char *d , char *s)
{
	if (*s=='"')
		s++;
	while (*d++=*s++)
		if (*s=='"')
			s++;
} 

void reset(char *d)
{
	while (*d++='\0');
} 

void read_includes(int token)
{
	while(token == SEPARATOR)
	{
		token = yylex();
	}
	//printf("%s\n", yytext);
	if (token == STRING)
	{
		if ( include_stack_ptr >= MAX_INCLUDE_DEPTH )
        {
            fprintf( stderr, "Includes nested too deeply" );
            exit( 1 );
        }
        
        rmQuote(outputName, yytext);
		//printf("FILE: %s\n", outputName);

        include_stack[include_stack_ptr++] = YY_CURRENT_BUFFER;
        

        yyin = fopen( outputName, "r" );

        if ( ! yyin )
            printf("No yyin\n");

        yy_switch_to_buffer( yy_create_buffer( yyin, YY_BUF_SIZE ) );
	}
	
	reset(outputName);
}

int preprocessor(void) 
{
	int token = yylex();
	
	outputName = malloc(100 * sizeof(char));
	
	FILE* out_file;
	out_file = fopen("output.c", "w");
    yyout = out_file;
	
	while(token!=0) 
	{
		//printf("%d\n", token);
		if (token == INCLUDE) //include found
		{
			token = yylex();                               
			read_includes(token);
	        
	    }
	    //printf("Token: %s\n", yytext);
	    fprintf(yyout, "%s", yytext);
		token = yylex();
	    //printf("Token: %s\n", yytext);
		
		if (token == 0)
		{
			if ( --include_stack_ptr < 0 )
		    {
		        yyterminate();
		    }
		
		    else
		    {
		    	//printf("Deberia pasar por aqui");
		        yy_delete_buffer( YY_CURRENT_BUFFER );
		        yy_switch_to_buffer(include_stack[include_stack_ptr] );
		        //printf("Token: %s\n", yytext);
		        token = yylex();
		    }
		}
	}
	
	fclose(out_file);
	free(outputName);
	return 0;
}