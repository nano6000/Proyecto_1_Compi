void clearLine(char line[]);
void newFrame();
void _newCodeFrame();
void endCurrentFrame();
void beginFrame();
void clearLine(char line[]);
void escapeLatexSpecialChars(char lexeme[]);
void append(char subject[], char insert[], int pos);
void addBackslash(char lexeme[], int index);
char* integer_to_string(int x);