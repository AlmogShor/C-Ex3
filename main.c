#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "Ex3.h"

void reverseString(char *reverse);

int main() {
    readWord();
    printf("\n");
    readText();
    printf("\n");
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
    fgets(inp_word, WORD, stdin);
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
    fgets(inp_txt, TXT, stdin);
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
    int curr_sum = 0, flag = 0;
    while (start < strlen(text) && !(end == strlen(text) && curr_sum < word_val)) {
        if (curr_sum == word_val) {
            for (int i = start; i < end; ++i) {
                if (!isalpha(text[i])) {
                    start++;
                } else {
                    break;
                }
            }
            if (flag) {
                putchar(TILDA);
            }
            for (int i = start; i < end; ++i) {
                putchar(text[i]);
            }
            flag++;
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
    for (int i = 0; i < strlen(idaGomla); ++i) {
        reverse[i] = idaGomla[strlen(idaGomla) - 1 - i];
    }
    return 0;
}

int textAtbash() {
    int curr_idx = 0, spaceCnt;
//    char reverse[WORD];
    char tmp_str[TXT] = {0};
    for (int i = 0; i < strlen(text); i++) { // i == current start index
        //Checking the Atbash sequence
        spaceCnt = 0;
        for (int j = 0; j < strlen(idaGomla); j++) {
            if (isspace(text[i + j + spaceCnt])) { // add and ignore spaces
                if (j == 0) {
                    break;
                }
                tmp_str[curr_idx++] = text[i + j + spaceCnt++];
                j--; // check word[j] in next iteration
                continue;
            }
            if (text[i + j + spaceCnt] == idaGomla[j]) {
                tmp_str[curr_idx++] = idaGomla[j];
            } else {
                curr_idx -= (j + spaceCnt);
                break;
            }
            if ((j) == strlen(idaGomla) - 1) {
                tmp_str[curr_idx++] = TILDA;
                break;
            }
        }
        //Check the reverse Atbash
        spaceCnt = 0;
        for (int j = 0; j < strlen(reverse); j++) {
            if (isspace(text[i + j + spaceCnt])) { // add and ignore spaces
                if (j == 0) {
                    break;
                }
                tmp_str[curr_idx++] = text[i + j + spaceCnt++];
                j--; // check word[j] in next iteration
                continue;
            }
            if (text[i + j + spaceCnt] == reverse[j]) {
                tmp_str[curr_idx++] = reverse[j];
            } else {
                curr_idx -= (j + spaceCnt);
                break;
            }
            if ((j) == strlen(reverse) - 1) {
                tmp_str[curr_idx++] = TILDA;
                break;
            }
        }
    }
    for (int k = curr_idx; k >= 0; k--) {
        if (tmp_str[k] == TILDA) {
            tmp_str[k] = 0;
            break;
        }
//        tmp_str[k] = 0;
    }
    puts(tmp_str);
    return 0;
}

//void reverseString() {
//    for (int i = 0; i < strlen(idaGomla); ++i) {
//        reverse[i] = idaGomla[strlen(idaGomla) - 1 - i];
//    }
//}

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