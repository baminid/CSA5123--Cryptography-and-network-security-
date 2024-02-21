#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Function to decrypt a message using the Playfair cipher
void decryptPlayfair(char *ciphertext, char matrix[5][5]) {
    int i, j, k, l;
    int len = strlen(ciphertext);

    // Decrypt message pair by pair
    for (i = 0; i < len; i += 2) {
        // Find positions of characters in the matrix
        for (j = 0; j < 5; j++) {
            for (k = 0; k < 5; k++) {
                if (matrix[j][k] == ciphertext[i]) {
                    break;
                }
            }
            if (k < 5) {
                break;
            }
        }
        for (l = 0; l < 5; l++) {
            for (k = 0; k < 5; k++) {
                if (matrix[l][k] == ciphertext[i + 1]) {
                    break;
                }
            }
            if (k < 5) {
                break;
            }
        }

        // If the letters are in the same row
        if (j == l) {
            printf("%c%c", matrix[j][(k - 1 + 5) % 5], matrix[l][(k - 1 + 5) % 5]);
        }
        // If the letters are in the same column
        else if (k == l) {
            printf("%c%c", matrix[(j - 1 + 5) % 5][k], matrix[(l - 1 + 5) % 5][k]);
        }
        // If the letters form a rectangle
        else {
            printf("%c%c", matrix[j][k], matrix[l][l]);
        }
    }
}

int main() {
    char matrix[5][5] = {
        {'K', 'X', 'J', 'E', 'Y'},
        {'U', 'R', 'E', 'B', 'Z'},
        {'W', 'H', 'Y', 'T', 'U'},
        {'H', 'E', 'Y', 'F', 'S'},
        {'K', 'R', 'E', 'G', 'O'}
    };
    char ciphertext[] = "KXJEYUREBEZWEHEWRYTUHEYFSKREHEGOYFIWTTTUOLKSYCAJPOBOTEIZONTXBYBNTGONEYCUZWRGDSONSXBOUYWRHEBAAHYUSEDQ";

    printf("Decrypted message: ");
    decryptPlayfair(ciphertext, matrix);

    return 0;
}
