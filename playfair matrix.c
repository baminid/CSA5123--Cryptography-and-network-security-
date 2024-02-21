#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Function to remove spaces and punctuation from a string
void removeSpacesAndPunctuation(char *plaintext) {
    int i, j = 0;
    for (i = 0; plaintext[i] != '\0'; i++) {
        if (isalpha(plaintext[i])) {
            plaintext[j++] = toupper(plaintext[i]);
        }
    }
    plaintext[j] = '\0';
}

// Function to encrypt a message using the Playfair cipher
void encryptPlayfair(char *plaintext, char matrix[5][5]) {
    int i, j, k, l;
    int len = strlen(plaintext);

    // Replace 'J' with 'I' in the plaintext
    for (i = 0; plaintext[i] != '\0'; i++) {
        if (plaintext[i] == 'J') {
            plaintext[i] = 'I';
        }
    }

    // Adjust message length for double letters
    for (i = 0; i < len; i += 2) {
        if (plaintext[i] == plaintext[i + 1]) {
            len++;
            for (j = len - 1; j > i + 1; j--) {
                plaintext[j] = plaintext[j - 1];
            }
            plaintext[i + 1] = 'X';
        }
    }

    // Encrypt message pair by pair
    for (i = 0; i < len; i += 2) {
        // Find positions of characters in the matrix
        for (j = 0; j < 5; j++) {
            for (k = 0; k < 5; k++) {
                if (matrix[j][k] == plaintext[i]) {
                    break;
                }
            }
            if (k < 5) {
                break;
            }
        }
        for (l = 0; l < 5; l++) {
            for (k = 0; k < 5; k++) {
                if (matrix[l][k] == plaintext[i + 1]) {
                    break;
                }
            }
            if (k < 5) {
                break;
            }
        }

        // If the letters are in the same row
        if (j == l) {
            printf("%c%c", matrix[j][(k + 1) % 5], matrix[l][(k + 1) % 5]);
        }
        // If the letters are in the same column
        else if (k == l) {
            printf("%c%c", matrix[(j + 1) % 5][k], matrix[(l + 1) % 5][k]);
        }
        // If the letters form a rectangle
        else {
            printf("%c%c", matrix[j][k], matrix[l][l]);
        }
    }
}

int main() {
    char matrix[5][5] = {
        {'M', 'F', 'H', 'I', 'K'},
        {'U', 'N', 'O', 'P', 'Q'},
        {'Z', 'V', 'W', 'X', 'Y'},
        {'E', 'L', 'A', 'R', 'G'},
        {'D', 'S', 'T', 'B', 'C'}
    };
    char plaintext[] = "Must see you over Cadogan West. Coming at once.";

    // Remove spaces and punctuation from the plaintext
    removeSpacesAndPunctuation(plaintext);

    printf("Encrypted message: ");
    encryptPlayfair(plaintext, matrix);

    return 0;
}
