#include <stdio.h>
#include <math.h>

// Function to calculate the factorial of a number
long long factorial(int n) {
    long long fact = 1;
    for (int i = 1; i <= n; ++i) {
        fact *= i;
    }
    return fact;
}

int main() {
    int n = 25; // Number of unique letters
    long long total_keys = factorial(n);
    long long equivalent_keys = pow(factorial(5), 2) * pow(2, 2);
    long long unique_keys = total_keys / equivalent_keys;

    // Approximate the number of effectively unique keys as a power of 2 using logarithms
    double approx_power_of_2 = log2(unique_keys);

    printf("Number of effectively unique keys: %lld (approximately 2^%.2f)\n", unique_keys, approx_power_of_2);

    return 0;
}
