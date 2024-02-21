#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Function to perform monoalphabetic substitution
char monoalphabetic_substitution(char ch, char key) {
    if (isalpha(ch)) {
        char base = islower(ch) ? 'a' : 'A';
        return ((ch - base + key - 'a') % 26) + base;
    } else {
        return ch;
    }
}

// Function to encrypt plaintext using polyalphabetic substitution cipher
void polyalphabetic_substitution(char *plaintext, char *key, char *ciphertext) {
    int key_len = strlen(key);
    int plaintext_len = strlen(plaintext);
    
    for (int i = 0; i < plaintext_len; i++) {
        char current_key = key[i % key_len];
        ciphertext[i] = monoalphabetic_substitution(plaintext[i], current_key);
    }
    ciphertext[plaintext_len] = '\0';
}

int main() {
    char plaintext[100], key[100], ciphertext[100];

    printf("Enter plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);
    plaintext[strcspn(plaintext, "\n")] = '\0'; // Removing newline character
    
    printf("Enter key: ");
    fgets(key, sizeof(key), stdin);
    key[strcspn(key, "\n")] = '\0'; // Removing newline character
    
    polyalphabetic_substitution(plaintext, key, ciphertext);
    
    printf("Ciphertext: %s\n", ciphertext);
    
    return 0;
}
