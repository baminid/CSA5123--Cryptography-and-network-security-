#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_KEY_LENGTH 100

// Function to encrypt the message using the one-time pad Vigenère cipher
void vigenere_encrypt(char *plaintext, int *key, int key_length, char *ciphertext) {
    int len = strlen(plaintext);
    int i;
    
    // Convert the plaintext to uppercase
    for (i = 0; i < len; i++) {
        plaintext[i] = toupper(plaintext[i]);
    }
    
    // Encrypt the plaintext
    for (i = 0; i < len; i++) {
        if (isalpha(plaintext[i])) {
            int shift = key[i % key_length];
            ciphertext[i] = ((plaintext[i] - 'A' + shift) % 26) + 'A';
        } else {
            ciphertext[i] = plaintext[i];
        }
    }
    ciphertext[len] = '\0';
}

// Function to decrypt the ciphertext and find the key
void find_key(char *ciphertext, char *plaintext, int *key, int key_length) {
    int len = strlen(ciphertext);
    int i;
    
    // Convert the ciphertext to uppercase
    for (i = 0; i < len; i++) {
        ciphertext[i] = toupper(ciphertext[i]);
    }
    
    // Find the key by comparing the plaintext and ciphertext
    for (i = 0; i < len; i++) {
        if (isalpha(ciphertext[i])) {
            int shift = (ciphertext[i] - plaintext[i] + 26) % 26;
            key[i % key_length] = shift;
        }
    }
}

int main() {
    char plaintext[] = "send more money";
    int key_stream[] = {9, 0, 1, 7, 23, 15, 21, 14, 11, 11, 2, 8, 9};
    int key_length = sizeof(key_stream) / sizeof(key_stream[0]);
    char ciphertext[MAX_KEY_LENGTH];
    
    // Encrypt the plaintext
    vigenere_encrypt(plaintext, key_stream, key_length, ciphertext);
    printf("Encrypted Ciphertext: %s\n", ciphertext);
    
    // Define the known ciphertext and plaintext for finding the key
    char known_ciphertext[] = "CASH NOT NEEDED";
    char known_plaintext[] = "SEND MORE MONEY";
    
    // Define a key array to store the found key
    int found_key[MAX_KEY_LENGTH];
    
    // Find the key to decrypt the ciphertext to the known plaintext
    find_key(known_ciphertext, known_plaintext, found_key, key_length);
    
    // Print the found key
    printf("Found Key: ");
    for (int i = 0; i < key_length; i++) {
        printf("%d ", found_key[i]);
    }
    printf("\n");
    
    return 0;
}
