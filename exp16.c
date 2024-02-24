#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26
#define TOP_PLAINTEXTS 10

// English letter frequencies (from most to least common)
const char *english_frequencies = "ETAOINSHRDLCUMWFGYPBVKJXQZ";

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

// Function to compare letter frequency counts for sorting
int compare_frequency(const void *a, const void *b) {
    int *x = (int *)a;
    int *y = (int *)b;
    return *y - *x;
}

// Function to decrypt the message using a given key
void decrypt_message(char *ciphertext, char *key) {
    int len = strlen(ciphertext);
    int i;

    for (i = 0; i < len; i++) {
        if (isalpha(ciphertext[i])) {
            char base = isupper(ciphertext[i]) ? 'A' : 'a';
            printf("%c", key[ciphertext[i] - base]);
        } else {
            printf("%c", ciphertext[i]);
        }
    }
    printf("\n");
}

int main() {
    char ciphertext[] = "Zl hzptw of av zljyl."; // Example ciphertext
    int frequency[ALPHABET_SIZE] = {0};
    char key[ALPHABET_SIZE + 1];
    char plaintext[ALPHABET_SIZE + 1];
    int i, j;

    // Count the frequency of each letter in the ciphertext
    count_frequency(ciphertext, frequency);

    // Sort the frequency array and store the corresponding letters
    int sorted_frequency[ALPHABET_SIZE];
    memcpy(sorted_frequency, frequency, sizeof(frequency));
    qsort(sorted_frequency, ALPHABET_SIZE, sizeof(int), compare_frequency);

    // Guess potential plaintexts based on sorted frequency
    for (i = 0; i < TOP_PLAINTEXTS; i++) {
        // Create a tentative key mapping based on the current frequency order
        for (j = 0; j < ALPHABET_SIZE; j++) {
            int index = frequency[j] == sorted_frequency[j] ? j : (j + i) % ALPHABET_SIZE;
            key[index] = english_frequencies[j];
        }
        key[ALPHABET_SIZE] = '\0'; // Null-terminate the key string

        // Decrypt the ciphertext using the current key mapping
        printf("Potential plaintext #%d: ", i + 1);
        decrypt_message(ciphertext, key);
    }

    return 0;
}
