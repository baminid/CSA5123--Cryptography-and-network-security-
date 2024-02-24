#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26

// Function to decrypt the message using additive cipher with a given key
void decrypt_message(char *ciphertext, int key) {
    int len = strlen(ciphertext);
    int i;

    for (i = 0; i < len; i++) {
        if (isalpha(ciphertext[i])) {
            char base = isupper(ciphertext[i]) ? 'A' : 'a';
            char decrypted_char = ((ciphertext[i] - base - key + ALPHABET_SIZE) % ALPHABET_SIZE) + base;
            printf("%c", decrypted_char);
        } else {
            printf("%c", ciphertext[i]);
        }
    }
    printf("\n");
}

// Function to count the frequency of each letter in the message
void count_frequency(char *message, int *frequency) {
    int len = strlen(message);
    int i;

    for (i = 0; i < len; i++) {
        if (isalpha(message[i])) {
            frequency[tolower(message[i]) - 'a']++;
        }
    }
}

// Function to find the most likely key based on letter frequency analysis
int find_key(int *frequency) {
    int max_frequency = 0;
    int max_index = 0;

    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (frequency[i] > max_frequency) {
            max_frequency = frequency[i];
            max_index = i;
        }
    }

    // Assuming 'e' is the most common letter in English, which is at index 4 ('a' is 0)
    return (max_index + ALPHABET_SIZE - 4) % ALPHABET_SIZE;
}

int main() {
    char ciphertext[] = "Lxfopv ef qe xka"; // Example ciphertext
    int frequency[ALPHABET_SIZE] = {0};
    int key;

    // Count the frequency of each letter in the ciphertext
    count_frequency(ciphertext, frequency);

    // Find the most likely key based on letter frequency analysis
    key = find_key(frequency);

    printf("Most likely key: %d\n", key);

    // Decrypt the ciphertext using the most likely key
    decrypt_message(ciphertext, key);

    return 0;
}
