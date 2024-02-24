#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

#define MATRIX_SIZE 2

// Function to encrypt the message using Hill cipher
void hill_encrypt(char *message, int key[MATRIX_SIZE][MATRIX_SIZE]) {
    int len = strlen(message);
    int i, j, k, sum;
    int plaintext[MATRIX_SIZE], ciphertext[MATRIX_SIZE];

    // Remove spaces and convert to uppercase
    for (i = 0, j = 0; i < len; i++) {
        if (isalpha(message[i])) {
            message[j++] = toupper(message[i]);
        }
    }
    message[j] = '\0';

    // Pad the message if necessary
    while (strlen(message) % MATRIX_SIZE != 0) {
        strcat(message, "X");
    }

    // Encrypt the message
    for (i = 0; i < strlen(message); i += MATRIX_SIZE) {
        for (j = 0; j < MATRIX_SIZE; j++) {
            plaintext[j] = message[i + j] - 'A';
        }
        for (j = 0; j < MATRIX_SIZE; j++) {
            sum = 0;
            for (k = 0; k < MATRIX_SIZE; k++) {
                sum += key[j][k] * plaintext[k];
            }
            ciphertext[j] = sum % 26;
        }
        for (j = 0; j < MATRIX_SIZE; j++) {
            message[i + j] = ciphertext[j] + 'A';
        }
    }
}

// Function to decrypt the message using Hill cipher
void hill_decrypt(char *message, int key[MATRIX_SIZE][MATRIX_SIZE]) {
    int len = strlen(message);
    int i, j, k, sum;
    int ciphertext[MATRIX_SIZE], decrypted[MATRIX_SIZE];
    int inverse[MATRIX_SIZE][MATRIX_SIZE];

    // Calculate the inverse of the key matrix
    int det = key[0][0] * key[1][1] - key[0][1] * key[1][0];
    int inv_det = 0;
    for (int x = 1; x < 26; x++) {
        if ((det * x) % 26 == 1) {
            inv_det = x;
            break;
        }
    }
    inverse[0][0] = key[1][1];
    inverse[1][1] = key[0][0];
    inverse[0][1] = -key[0][1];
    inverse[1][0] = -key[1][0];
    for (i = 0; i < MATRIX_SIZE; i++) {
        for (j = 0; j < MATRIX_SIZE; j++) {
            inverse[i][j] *= inv_det;
            inverse[i][j] = (inverse[i][j] % 26 + 26) % 26;
        }
    }

    // Decrypt the message
    for (i = 0; i < len; i += MATRIX_SIZE) {
        for (j = 0; j < MATRIX_SIZE; j++) {
            ciphertext[j] = message[i + j] - 'A';
        }
        for (j = 0; j < MATRIX_SIZE; j++) {
            sum = 0;
            for (k = 0; k < MATRIX_SIZE; k++) {
                sum += inverse[j][k] * ciphertext[k];
            }
            decrypted[j] = sum % 26;
        }
        for (j = 0; j < MATRIX_SIZE; j++) {
            message[i + j] = decrypted[j] + 'A';
        }
    }
}

int main() {
    char plaintext[] = "HELLO";
    char ciphertext[] = "PJAZZ"; // Corresponding to "HELLO" encrypted with a key
    int key[MATRIX_SIZE][MATRIX_SIZE];

    // Convert plaintext and ciphertext to uppercase
    for (int i = 0; i < strlen(plaintext); i++) {
        plaintext[i] = toupper(plaintext[i]);
    }
    for (int i = 0; i < strlen(ciphertext); i++) {
        ciphertext[i] = toupper(ciphertext[i]);
    }

    // Convert characters to numbers (A=0, B=1, ..., Z=25)
    int plain_num[strlen(plaintext)];
    int cipher_num[strlen(ciphertext)];
    for (int i = 0; i < strlen(plaintext); i++) {
        plain_num[i] = plaintext[i] - 'A';
    }
    for (int i = 0; i < strlen(ciphertext); i++) {
        cipher_num[i] = ciphertext[i] - 'A';
    }

    // Construct the system of equations and solve for the key matrix
    int a, b, c, d;
    a = (cipher_num[0] - cipher_num[1] - cipher_num[3] + 26) % 26;
    b = (cipher_num[2] - cipher_num[1] - cipher_num[3] + 26) % 26;
    c = (cipher_num[0] - cipher_num[2] - cipher_num[4] + 26) % 26;
    d = (cipher_num[3] - cipher_num[2] - cipher_num[4] + 26) % 26;

    // Fill in the key matrix
    key[0][0] = a;
    key[0][1] = b;
    key[1][0] = c;
    key[1][1] = d;

    // Decrypt using the found key
    hill_decrypt(ciphertext, key);

    printf("Recovered Key Matrix:\n");
    printf("%d %d\n", key[0][0], key[0][1]);
    printf("%d %d\n", key[1][0], key[1][1]);

    printf("Decrypted Plaintext: %s\n", ciphertext);

    return 0;
}
