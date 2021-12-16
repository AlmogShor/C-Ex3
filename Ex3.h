#ifndef C_EX3_EX3_H
#define C_EX3_EX3_H

#define TXT 1024
#define WORD 30
#define TILDA '~'

char word[WORD];
char text[TXT];
char idaGomla[WORD];
int word_val;

int readWord();

int readText();

int wordVal();

int textVal();

int calcCharVal(char c);

int idagomla();

void initAdded();

int findMatches();

int textAtbash();

int findMatches();

#endif //C_EX3_EX3_H
