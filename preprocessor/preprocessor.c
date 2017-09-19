//#include "preprocessor.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "lex.yy.c"


#define MAX_INCLUDE_DEPTH 10
YY_BUFFER_STATE include_stack[MAX_INCLUDE_DEPTH];
int include_stack_ptr = 0;

extern int yylex();
extern int yylineno;
extern char* yytext;

int symbol;


void read_includes(int token)
{
	while(token == SEPARATOR)
	{
		token = yylex();
	}
	if (token == QUOTE || token == LESS_THAN)
	{
		token = yylex();
		if (token == FILENAME)
		{
			if ( include_stack_ptr >= MAX_INCLUDE_DEPTH )
            {
	            fprintf( stderr, "Includes nested too deeply" );
	            exit( 1 );
            }
            
    		printf("FILE: %s\n", yytext);

	        include_stack[include_stack_ptr++] = YY_CURRENT_BUFFER;
	        
	
	        yyin = fopen( yytext, "r" );
	
	        if ( ! yyin )
	            printf("No yyin\n");
	
	        yy_switch_to_buffer( yy_create_buffer( yyin, YY_BUF_SIZE ) );
		}
		
	}
}

int main(void) 
{
	int token = yylex();
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
		        token = yylex();
		        //printf("Token: %s\n", yytext);
		        token = yylex();
		    }
		}
	}
	
	fclose(out_file);
	return 0;
}