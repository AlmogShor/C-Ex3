#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "Ex3.h"

char word[WORD];
char text[TXT];
char idaGomla[];
int word_val;

int main() {
//    readWord();
//    readText();
//    word_val = wordVal(word);

    return 0;

}

int readWord() { // todo: how to check if scan was successful
    char inp_word[WORD];
    char c;
    scanf("Enter word: %s", inp_word);
    for (int i = 0; i < WORD; ++i) {
        c = inp_word[i];
        word[i] = c;
        if (isspace(c)) {
            return 0;
        }
    }
    return 1;
}

int readText() {
    char inp_txt[TXT];
    char c;
    scanf("Enter text: %s", inp_txt);
    for (int i = 0; i < TXT; ++i) {
        c = inp_txt[i];
        text[i] = c;
        if (c == TILDA) {
            return 0;
        }
    }
    return 1;
}

int wordVal() {
    int sum = 0;
    char c;
    for (int i = 0; i < strlen(word); ++i) {
        c = word[i];
        sum += calcCharVal(c);
    }
    return sum;
}

int textVal() {
    int start = 0, end = 0;
    int curr_sum = 0;
    while (start < strlen(text) && !(end == strlen(text) && curr_sum < word_val)) {
        if (curr_sum == word_val) {
            for (int i = start; i < end; ++i) {
                putchar(text[i]);
            }
            putchar(TILDA);
            curr_sum = curr_sum - calcCharVal(text[start++]);
            if (end != strlen(text)) {
                curr_sum += calcCharVal(text[end++]);
            }
        }
        if (curr_sum > word_val) {
            curr_sum = curr_sum - calcCharVal(text[start++]);
        }
        if (curr_sum < word_val && end != strlen(text)) {
            curr_sum += calcCharVal(text[end++]);
        }
    }
    return 0;
}

int calcCharVal(char c) { // todo: toupper/tolower functions?
    int val = 0;
    if (c >= 'a' && c <= 'z') {
        val += c - 'a' + 1;
    } else if (c >= 'A' && c <= 'Z') {
        val += c - 'A' + 1;
    }
    return val;
}

int idagomla(){

    for (int i = 0; i < strlen(word); ++i) {
        if(islower(word[i])){
            idaGomla[i] = 'z' - word[i] + 'a';
        }
        else if(isupper(word[i])){
            idaGomla[i] = 'Z' - word[i] + 'A';
        }
    }
return 0;
}

