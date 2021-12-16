#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "Ex3.h"

int main() {
    readWord();
    readText();
    word_val = wordVal(word);
    idagomla();
    printf("Gematria Sequences: ");
    textVal();
    printf("\n");
    printf("Atbash Sequences: ");
    textAtbash();
    printf("\n");
    printf("Anagram Sequences: ");
    findMatches();

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

int idagomla() {
    for (int i = 0; i < strlen(word); ++i) {
        if (islower(word[i])) {
            idaGomla[i] = 'z' - word[i] + 'a';
        } else if (isupper(word[i])) {
            idaGomla[i] = 'Z' - word[i] + 'A';
        } else {
            idaGomla[i] = word[i];
        }
    }
    return 0;
}

int textAtbash() {
    int curr_idx = 0;
    char reverse[strlen(idaGomla)];
    char tmp_str[TXT] = {0};
    for (int i = 0; i < strlen(idaGomla); ++i) {
        reverse[i] = idaGomla[strlen(idaGomla) - 1 - i];
    }
    for (int i = 0; i < strlen(text); i++) { // i == current start index
        for (int j = 0; j < strlen(idaGomla); j++) {
            if (isspace(text[i + j])) { // add and ignore spaces
                tmp_str[curr_idx++] = text[i + j];
                j--; // check word[j] in next iteration
            } else if (text[i + j] == idaGomla[j]) {
                tmp_str[curr_idx++] = idaGomla[j];
            }
            if (j == strlen(idaGomla) - 1) {
                tmp_str[curr_idx++] = TILDA;
            }
            if (text[i + j] != idaGomla[j]) {
                curr_idx -= j;
                break;
            }
        }
        for (int j = 0; j < strlen(reverse); j++) {
            if (isspace(text[i + j])) { // add and ignore spaces
                tmp_str[curr_idx++] = text[i + j];
                j--; // check word[j] in next iteration
            } else if (text[i + j] == reverse[j]) {
                tmp_str[curr_idx++] = reverse[j];
            }
            if (j == strlen(reverse) - 1) {
                tmp_str[curr_idx++] = TILDA;
            }
            if (text[i + j] != reverse[j]) {
                curr_idx -= j;
                break;
            }
        }
    }
    for (int k = strlen(tmp_str); k >= 0; k--) {
        if (tmp_str[k] == TILDA) {
            break;
        }
        tmp_str[k] = 0;
    }
    puts(tmp_str);
    return 0;
}

//int
// array of int -> 0 = not added, 1 = added (index = char at index)

int findMatches() {
    int tmp = strlen(word) * sizeof(int);
    int is_added[tmp];
    char ans[strlen(word)];
    int cnt, flag;
    initAdded(tmp, is_added);
    for (int i = 0; i < strlen(text); i++) {
        flag = cnt = 0;
        for (int j = 0; j < strlen(word); j++) {
            if (is_added[j] == 0 && is_added[j] == word[i]) {
                is_added[j] = 1;
                flag = 1;
                ans[i] = word[i];
                break;
            }
        }
        for (int j = 0; j < strlen(word); ++j) {
            if (is_added[j] == 1) {
                cnt++;
            }
        }
        if (cnt == strlen(word) || flag == 0) {
            initAdded(tmp, is_added);
            puts(ans);
            putchar(TILDA);
        }
    }

    return 0;
}

void initAdded(int tmp, int *is_added) {
    for (int k = 0; k < tmp; k++) {
        is_added[k] = 0;
    }
}
