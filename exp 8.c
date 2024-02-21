#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Function to generate the cipher sequence from a keyword
void generateCipherSequence(char keyword[], char cipherSeq[]) {
    int i, j;
    int keywordLen = strlen(keyword);
    int index = 0;

    // Copy the keyword to the cipher sequence
    for (i = 0; i < keywordLen; i++) {
        cipherSeq[index++] = toupper(keyword[i]);
    }

    // Mark used letters in the keyword
    int used[26] = {0};
    for (i = 0; i < keywordLen; i++) {
        used[toupper(keyword[i]) - 'A'] = 1;
    }

    // Append unused letters to the cipher sequence in normal order
    for (i = 0; i < 26; i++) {
        if (!used[i] && ('A' + i) != 'J') { // Exclude 'J' as it's usually combined with 'I'
            cipherSeq[index++] = 'A' + i;
        }
    }
    cipherSeq[index] = '\0';
}

// Function to encrypt plaintext using monoalphabetic cipher
void encryptMonoalphabetic(char plaintext[], char cipherSeq[]) {
    int i;
    int len = strlen(plaintext);

    for (i = 0; i < len; i++) {
        if (isalpha(plaintext[i])) {
            int index = toupper(plaintext[i]) - 'A';
            plaintext[i] = isupper(plaintext[i]) ? cipherSeq[index] : tolower(cipherSeq[index]);
        }
    }
}

int main() {
    char keyword[] = "CIPHER";
    char plaintext[] = "Hello, World!";
    char cipherSeq[26];

    // Generate the cipher sequence from the keyword
    generateCipherSequence(keyword, cipherSeq);

    // Encrypt the plaintext using the generated cipher sequence
    encryptMonoalphabetic(plaintext, cipherSeq);

    printf("Encrypted message: %s\n", plaintext);

    return 0;
}
