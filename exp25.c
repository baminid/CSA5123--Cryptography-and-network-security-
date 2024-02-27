#include <stdio.h>

// Function to calculate the greatest common divisor (GCD)
int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

// Function to find the private exponent using the extended Euclidean algorithm
int multiplicativeInverse(int e, int fn) {
    int m0 = fn, t, q;
    int x0 = 0, x1 = 1;
    if (fn == 1)
        return 0;
    while (e > 1) {
        q = e / fn;
        t = fn;
        fn = e % fn, e = t;
        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }
    if (x1 < 0)
        x1 += m0;
    return x1;
}

int main() {
    int e = 31; // Public exponent
    int n = 3599; // Modulus n = pq
    int known_plaintext_block = 123; // Example of known plaintext block with a common factor with n
    
    // Factorizing n using the known plaintext block
    int p = gcd(n, known_plaintext_block);
    int q = n / p;
    
    // Calculate f(n)
    int fn = (p - 1) * (q - 1);
    
    // Find the private exponent d
    int d = multiplicativeInverse(e, fn);
    
    // Print the private key
    printf("Private Key (d): %d\n", d);
    
    return 0;
}
