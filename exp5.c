#include <stdio.h>

// Function to calculate the greatest common divisor (gcd) using Euclid's algorithm
int gcd(int a, int b) {
    int temp;
    while (b != 0) {
        temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Function to find modular multiplicative inverse using extended Euclidean algorithm
int modInverse(int a, int m) {
    int m0 = m, t, q;
    int x0 = 0, x1 = 1;
    if (m == 1)
        return 0;
    while (a > 1) {
        q = a / m;
        t = m;
        m = a % m, a = t;
        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }
    if (x1 < 0)
        x1 += m0;
    return x1;
}

// Function to encrypt plaintext using affine Caesar cipher
char encrypt(int a, int b, char plaintext) {
    if (plaintext >= 'a' && plaintext <= 'z') {
        return ((a * (plaintext - 'a') + b) % 26) + 'a';
    } else if (plaintext >= 'A' && plaintext <= 'Z') {
        return ((a * (plaintext - 'A') + b) % 26) + 'A';
    } else {
        return plaintext; // Ignore non-alphabetic characters
    }
}

// Main function
int main() {
    int a, b;
    char plaintext[1000];

    printf("Enter the value of a: ");
    scanf("%d", &a);

    // Check if 'a' is allowed
    if (gcd(a, 26) != 1) {
        printf("Error: 'a' must be coprime with 26 for the cipher to be one-to-one.\n");
        return 1;
    }

    printf("Enter the value of b: ");
    scanf("%d", &b);

    printf("Enter the plaintext: ");
    scanf(" %[^\n]", plaintext);

    printf("Encrypted text: ");
    for (int i = 0; plaintext[i] != '\0'; i++) {
        printf("%c", encrypt(a, b, plaintext[i]));
    }
    printf("\n");

    return 0;
}
