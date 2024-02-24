#include <stdio.h>
#include <string.h>
#include <ctype.h>

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
    printf("Encryption Steps:\n");
    for (i = 0; i < strlen(message); i += MATRIX_SIZE) {
        printf("Step %d:\n", (i / MATRIX_SIZE) + 1);
        printf("Plaintext: ");
        for (j = 0; j < MATRIX_SIZE; j++) {
            plaintext[j] = message[i + j] - 'A';
            printf("%c ", message[i + j]);
        }
        printf("\n");

        printf("Key Matrix:\n");
        for (j = 0; j < MATRIX_SIZE; j++) {
            for (k = 0; k < MATRIX_SIZE; k++) {
                printf("%d ", key[j][k]);
            }
            printf("\n");
        }

        printf("Multiplying plaintext with key matrix:\n");
        for (j = 0; j < MATRIX_SIZE; j++) {
            sum = 0;
            for (k = 0; k < MATRIX_SIZE; k++) {
                sum += key[j][k] * plaintext[k];
            }
            ciphertext[j] = sum % 26;
            printf("%d ", sum);
        }
        printf("\n");

        printf("Ciphertext: ");
        for (j = 0; j < MATRIX_SIZE; j++) {
            message[i + j] = ciphertext[j] + 'A';
            printf("%c ", message[i + j]);
        }
        printf("\n\n");
    }
}

// Function to find the modular multiplicative inverse of a number
int mod_inverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++)
        if ((a * x) % m == 1)
            return x;
    return 1;
}

// Function to find the determinant of a 2x2 matrix
int determinant(int key[MATRIX_SIZE][MATRIX_SIZE]) {
    return key[0][0] * key[1][1] - key[0][1] * key[1][0];
}

// Function to calculate the inverse of the key matrix
void inverse_key(int key[MATRIX_SIZE][MATRIX_SIZE], int inverse[MATRIX_SIZE][MATRIX_SIZE]) {
    int det = determinant(key);
    int inv_det = mod_inverse(det, 26);
    inverse[0][0] = key[1][1];
    inverse[1][1] = key[0][0];
    inverse[0][1] = -key[0][1];
    inverse[1][0] = -key[1][0];
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            inverse[i][j] *= inv_det;
            inverse[i][j] = (inverse[i][j] % 26 + 26) % 26;
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
    inverse_key(key, inverse);

    // Decrypt the message
    printf("Decryption Steps:\n");
    for (i = 0; i < len; i += MATRIX_SIZE) {
        printf("Step %d:\n", (i / MATRIX_SIZE) + 1);
        printf("Ciphertext: ");
        for (j = 0; j < MATRIX_SIZE; j++) {
            ciphertext[j] = message[i + j] - 'A';
            printf("%c ", message[i + j]);
        }
        printf("\n");

        printf("Inverse Key Matrix:\n");
        for (j = 0; j < MATRIX_SIZE; j++) {
            for (k = 0; k < MATRIX_SIZE; k++) {
                printf("%d ", inverse[j][k]);
            }
            printf("\n");
        }

        printf("Multiplying ciphertext with inverse key matrix:\n");
        for (j = 0; j < MATRIX_SIZE; j++) {
            sum = 0;
            for (k = 0; k < MATRIX_SIZE; k++) {
                sum += inverse[j][k] * ciphertext[k];
            }
            decrypted[j] = sum % 26;
            printf("%d ", sum);
        }
        printf("\n");

        printf("Plaintext: ");
        for (j = 0; j < MATRIX_SIZE; j++) {
            message[i + j] = decrypted[j] + 'A';
            printf("%c ", message[i + j]);
        }
        printf("\n\n");
    }
}

int main() {
    char message[] = "meet me at the usual place at ten rather than eight oclock";
    int key[MATRIX_SIZE][MATRIX_SIZE] = {{9, 4}, {5, 7}};

    // Encrypt the message
    printf("Encryption Process:\n\n");
    hill_encrypt(message, key);

    // Print the encrypted message
    printf("Encrypted Message: %s\n\n", message);

    // Decrypt the message
    printf("Decryption Process:\n\n");
    hill_decrypt(message, key);

    // Print the decrypted message
    printf("Decrypted Message: %s\n", message);

    return 0;
}
