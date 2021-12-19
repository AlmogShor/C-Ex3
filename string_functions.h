#ifndef C_EX3_STRING_FUNCTIONS_H
#define C_EX3_STRING_FUNCTIONS_H

#define TXT 1024
#define WORD 30
#define TILDA '~'

char word[WORD];
char text[TXT];
char idaGomla[WORD];
char reverse[WORD];
int word_val;

int readWord();

int readText();

int wordVal();

int textVal();

int calcCharVal(char c);

int idagomla();

int textAnagram();

int isAnagram(char *check, char  *tmp);

void sort(char *arr);

int textAtbash();

int findMatches();

#endif //C_EX3_STRING_FUNCTIONS_H
