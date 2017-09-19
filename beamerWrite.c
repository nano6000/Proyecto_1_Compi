#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "beamerWrite.h"
#include "AppendFileAtoB.c"


static char TEMPLATE_HEAD[] = "latex/templateHead.tex";
static char BEAMER_FILE[] = "latex/result.tex";
static char charactersToEscape[] = {'&', '%', '$', '#', '_', '{', '}', '~', '^', '\\'};

int familyCount[7] = {0,0,0,0,0,0,0};


char line[1300] = "";
int lineCounter = 0;

void appendToFile(char file[], char string[]){
    FILE *fp1;
    fp1 = fopen(file, "a");
    if(fp1 == NULL)
    {
        printf("\nError reading file\n");
        exit(0);
    }
    fprintf(fp1, "%s", string);
    fclose(fp1);
}


void addToken(struct Token token){
    
    char lexemeWithColor[128] = "";
    strcat(lexemeWithColor, "@\\colorbox{");
    strcat(lexemeWithColor, token.CTokenFamily);
    strcat(lexemeWithColor, "}{");
    /* & % $ # _ { } ~ ^ \ */
    char lexeme[128];
    strcpy(lexeme, token.lexeme);
    escapeLatexSpecialChars(lexeme);
    strcat(lexemeWithColor, lexeme);
    strcat(lexemeWithColor, "}@");
    strcat(line,lexemeWithColor);
    clearLine(lexemeWithColor);
    
    if (token.CTokenFamily == "CONSTANT"){
        familyCount[0]++;
    }else if (token.CTokenFamily == "INCLUDE"){
        familyCount[1]++;
    }else if (token.CTokenFamily == "STRING"){
        familyCount[2]++;
    }else if (token.CTokenFamily == "ID"){
        familyCount[3]++;
    }else if (token.CTokenFamily == "KEYWORD"){
        familyCount[4]++;
    }else if (token.CTokenFamily == "OPERATOR"){
        familyCount[5]++;
    }else if (token.CTokenFamily == "PUNCTUATOR"){
        familyCount[6]++;
    }
}

//Writes a tab or space if it has come, if its a new line, write it to beamer
void writeSeparator (char separator[]){
    
    if (lineCounter == 8){
        newFrame();
        lineCounter = 0;
    }
    int len = strlen(line);
    line[len] = separator[0];
    line[len+1] = '\0';
    

    if (separator[0] == '\n'){
        lineCounter++;
        appendToFile(BEAMER_FILE, line);
        clearLine(line);
    }
}

//Erases line to start another one
void clearLine (char line[]){
    line[0] = '\0';

}

void newFrame(){
    endCurrentFrame();
    _newCodeFrame();
}

void endCurrentFrame(){
    char endFrame[] = "\t\t\\end{lstlisting}\n\t\\end{flushleft}\n\\end{frame}\n\n";
    appendToFile(BEAMER_FILE,endFrame);
}

void _newCodeFrame(){
    char beginFrame[] = "\n\\begin{frame}[fragile]{C Code analyzed}\n\t\\begin{flushleft}\n\t\t\\begin{lstlisting}[breaklines]\n";
    appendToFile(BEAMER_FILE, beginFrame);
}

void beamerEndCCode(){
    endCurrentFrame();
    //appendToFile(BEAMER_FILE, "\n\n\\end{document}");
}


void escapeLatexSpecialChars(char lexeme[]){

    int lenListOfChars = strlen(charactersToEscape);
    int lenLexeme = strlen(lexeme);
    //printf ("hola");
    //printf("lexeme is %s of len %d\n", lexeme, lenLexeme);
    int i;
    int j;
    for (j=0; j < lenLexeme;j++){
        printf ("Current lexeme being compared: %s\nJ is %d\n", lexeme, j);
        for (i=0;i< lenListOfChars; i++){
            printf ("--Comparing %c with %c--\n", lexeme[j], charactersToEscape[i]);
            if (lexeme[j] == charactersToEscape[i]){
                printf("got occurence in j = %d\n", j);
                if (charactersToEscape[i] == '\\'){
                    break;
                }
                addBackslash(lexeme, j);
                j+=2;
                i = -1;
                lenLexeme++;
                printf("lexeme is now %s j is now %d\n", lexeme,j);
                continue;
                
            }
        }
    }
}

void addBackslash(char lexeme[], int index){
    append(lexeme, "\\", index);
}


void writeStatistics (){
    clearLine(line);
    

    
    strcpy(line, "\\begin{frame}{Statistics}\n");
    strcat(line, "The amount of constants is ");
    strcat(line, integer_to_string(familyCount[0]));
    strcat(line, "\\\\\n");
    
   // strcat(line, "The amount of includes is ");
    //strcat(line, integer_to_string(familyCount[1]));
   // strcat(line, "\\\\\n");
    
    strcat(line, "The amount of strings is ");
    strcat(line, integer_to_string(familyCount[2]));
    strcat(line, "\\\\\n");
    
    strcat(line, "The amount of IDs is ");
    strcat(line, integer_to_string(familyCount[3]));
    strcat(line, "\\\\\n");
    
    strcat(line, "The amount of keywords is ");
    strcat(line, integer_to_string(familyCount[4]));
    strcat(line, "\\\\\n");
    
    strcat(line, "The amount of operators is ");
    strcat(line, integer_to_string(familyCount[5]));
    strcat(line, "\\\\\n");
    
    strcat(line, "The amount of punctuators is ");
    strcat(line, integer_to_string(familyCount[6]));
    strcat(line, "\\\\\n");
    
    strcat(line, "\\end{frame}");
    appendToFile(BEAMER_FILE, line);
    
}


void append(char subject[], char insert[], int pos) {
    char buf[256] = ""; // 100 so that it's big enough. fill with zeros
    strncpy(buf, subject, pos); // copy at most first pos characters
    int len = strlen(buf);
    strcpy(buf+len, insert); // copy all of insert[] at the end
    len += strlen(insert);  // increase the length by length of insert[]
    strcpy(buf+len, subject+pos); // copy the rest

    strcpy(subject, buf);   // copy it back to subject

}

char* integer_to_string(int x){
    char* buffer = malloc(sizeof(char) * sizeof(int) * 4 + 1);
    if (buffer)
    {
         sprintf(buffer, "%d", x);
    }
    return buffer; // caller is expected to invoke free() on this buffer to release memory
}