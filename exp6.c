#include <stdio.h>

// Function to find modular multiplicative inverse of a mod m
int modInverse(int a, int m) {
    int m0 = m, t, q;
    int x0 = 0, x1 = 1;

    if (m == 1) return 0;

    // Apply extended Euclid Algorithm
    while (a > 1) {
        // q is quotient
        q = a / m;

        t = m;

        // m is remainder now, process same as Euclid's algo
        m = a % m, a = t;

        t = x0;

        x0 = x1 - q * x0;

        x1 = t;
    }

    // Make x1 positive
    if (x1 < 0) x1 += m0;

    return x1;
}

// Function to decrypt the ciphertext using affine cipher
void decryptAffineCipher(char ciphertext[], int a, int b) {
    int i;
    int m = 26; // Total number of alphabets

    // Find modular multiplicative inverse of a
    int a_inverse = modInverse(a, m);

    // Decrypt each character
    for (i = 0; ciphertext[i] != '\0'; ++i) {
        if (ciphertext[i] >= 'A' && ciphertext[i] <= 'Z') {
            // Apply decryption formula
            char decrypted_char = ((a_inverse * (ciphertext[i] - 'A' - b)) % m + m) % m + 'A';
            printf("%c", decrypted_char);
        } else {
            // If character is not an uppercase alphabet, print it as it is
            printf("%c", ciphertext[i]);
        }
    }
}

int main() {
    char ciphertext[] = "BU"; // Ciphertext
    int most_freq = 'B' - 'A'; // Most frequent letter
    int second_most_freq = 'U' - 'A'; // Second most frequent letter

    // Possible values of a are such that they are coprime with 26
    int possible_a[] = {1, 3, 5, 7, 9, 11, 15, 17, 19, 21, 23, 25};
    int num_possible_a = sizeof(possible_a) / sizeof(possible_a[0]);

    // Decrypt using possible values of a and calculate corresponding b
    for (int i = 0; i < num_possible_a; ++i) {
        int a = possible_a[i];
        int b = (second_most_freq - most_freq * a) % 26;
        if (b < 0) b += 26; // Ensure b is positive

        printf("Trying a = %d, b = %d: ", a, b);
        decryptAffineCipher(ciphertext, a, b);
        printf("\n");
    }

    return 0;
}
