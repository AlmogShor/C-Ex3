#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "string_functions.h"

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
    printf("Anagram Sequences: ");
    textAnagram();
    printf("\n");
    return 0;
}

/* read input */

// get input word from command line
int readWord() { // todo: how to check if scan was successful
    char inp_word[WORD];
    char c;
    fgets(inp_word, WORD, stdin);
    for (int i = 0; i < WORD; ++i) {
        c = inp_word[i];
        if (isspace(c)) {
            return 0;
        }
        word[i] = c;
    }
    return 1;
}

// get input text from command line
int readText() {
    char c;
    for (int i = 0; i < TXT; ++i) {
        scanf("%c", &c);
        if (c == TILDA) { // tilda (~) marks the end of the text
            return 0;
        }
        text[i] = c;
    }
    return 1;
}

/* part a */

// calculate the sum of ascii values of the word
int wordVal() {
    int sum = 0;
    char c;
    for (int i = 0; i < strlen(word); ++i) {
        c = word[i];
        sum += calcCharVal(c);
    }
    return sum;
}

// function finds the minimal sequence with the same ascii value of the word
int textVal() {
    int start = 0, end = 0;
    int curr_sum = 0, flag = 0;
    while (start < strlen(text) && !(end == strlen(text) && curr_sum < word_val)) {
        if (curr_sum == word_val) { // sum is equal to the word value
            for (int i = start; i < end; ++i) {
                if (!isalpha(text[i])) { // ignores characters that are not alphabetical
                    start++;
                } else {
                    break;
                }
            }
            if (flag) { // add tilda if not the first word printed
                putchar(TILDA);
            }
            for (int i = start; i < end; ++i) { // prints sequence
                putchar(text[i]);
            }
            flag++;
            curr_sum = curr_sum - calcCharVal(text[start++]); // subtract ascii value of first character in the sequence
            if (end != strlen(text)) {
                curr_sum += calcCharVal(text[end++]);
            }
        }
        if (curr_sum > word_val) { // sum is greater than the word value
            curr_sum = curr_sum - calcCharVal(text[start++]); // subtract ascii value of first character in the sequence
        }
        if (curr_sum < word_val && end != strlen(text)) { // sum is less than the word value
            curr_sum += calcCharVal(text[end++]); // add value of next character
        }
    }
    return 0;
}

// returns the ascii value of an alphabetical character
int calcCharVal(char c) {
    int val = 0;
    if (c >= 'a' && c <= 'z') {
        val += c - 'a' + 1;
    } else if (c >= 'A' && c <= 'Z') {
        val += c - 'A' + 1;
    }
    return val;
}

/* part b */

// saves an array of the word with reversed alphabet (a = z, b = y, etc)
// also saves an array with the reverse of the reversed alphabet word
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

// function prints sequences that match the arrays from idagomla function (above)
int textAtbash() {
    int curr_idx = 0, spaceCnt;
    char tmp_str[TXT] = {0};
    for (int i = 0; i < strlen(text); i++) { // i == current start index
        // check the atbash sequence
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
            if (j == strlen(idaGomla) - 1) {
                tmp_str[curr_idx++] = TILDA;
                break;
            }
        }
        // check the reverse atbash
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
            if (j == strlen(reverse) - 1) {
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
        tmp_str[k] = 0;
    }
    puts(tmp_str); // write the string to the output stream (prints)
    return 0;
}

/* part c */

// function prints minimal sequences in the text that contain all the letters in the word
int textAnagram() {
    char check[WORD];
    char tmp[WORD];
    strcpy(tmp, word);
    sort(tmp);
    int start = 0, end = 0, idx, flag, mowgli = 0;

    // if i = strlen(text) - strlen(tmp) + 1 -> there are fewer letters than the word itself
    for (int i = 0; i < (strlen(text) - strlen(tmp) + 1); i++) {
        start = end = i;
        idx = 0;
        while (1) {
            if (isspace(text[end])) { // add and ignore spaces
                if (start == end) { // break loop if first character is a space
                    break;
                }
                end++;
            } else {
                check[idx++] = text[end++];
            }
            if (idx == strlen(word)) {
                break;
            }
        }
        sort(check);
        flag = isAnagram(check, tmp);
        if (flag) {
            if (mowgli) {
                putchar(TILDA);
            }
            for (int j = start; j < end; j++) {
                putchar(text[j]);
            }
            mowgli++;
        }
    }
    return 0;
}

// sorts the char array by ascii value
void sort(char *arr) {
    int i, j, temp;
    for (i = 0; i < strlen(arr) - 1; i++) {
        for (j = i + 1; j < strlen(arr); j++) {
            if (arr[i] > arr[j]) {
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

// given two sorted arrays, checks if they are identical
int isAnagram(char *check, char *tmp) {
    for (int i = 0; i < strlen(check) && i < strlen(tmp); i++) {
        if (check[i] != tmp[i]) {
            return 0;
        }
    }
    return 1;
}