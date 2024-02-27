#include <stdio.h>

// Function to calculate the greatest common divisor (GCD) using Euclid's algorithm
int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

// Function to calculate the modular exponentiation
int modExp(int base, int exp, int mod) {
    int result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1)
            result = (result * base) % mod;
        exp = exp / 2;
        base = (base * base) % mod;
    }
    return result;
}

// Function to find the multiplicative inverse using extended Euclidean algorithm
int multiplicativeInverse(int e, int fn) {
    int m0 = fn, t, q;
    int x0 = 0, x1 = 1;
    if (fn == 1)
        return 0;
    while (e > 1) {
        // q is quotient
        q = e / fn;
        t = fn;
        // fn is remainder now, process same as Euclid's algo
        fn = e % fn, e = t;
        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }
    // Make x1 positive
    if (x1 < 0)
        x1 += m0;
    return x1;
}

int main() {
    int e = 31, n = 3599;
    int p, q;
    
    // Find prime factors p and q
    for (int i = 2; i < n; i++) {
        if (n % i == 0 && gcd(i, n / i) == 1) {
            p = i;
            q = n / i;
            break;
        }
    }
    
    // Calculate f(n)
    int fn = (p - 1) * (q - 1);
    
    // Find the multiplicative inverse of e modulo f(n)
    int d = multiplicativeInverse(e, fn);
    
    // Print the private key
    printf("Private Key (d): %d\n", d);
    
    return 0;
}
