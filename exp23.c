#include <stdio.h>

// Initial permutation table
int IP[] = {2, 6, 3, 1, 4, 8, 5, 7};

// Final permutation table
int FP[] = {4, 1, 3, 5, 7, 2, 8, 6};

// Expansion permutation table
int EP[] = {4, 1, 2, 3, 2, 3, 4, 1};

// Permutation table P4
int P4[] = {2, 4, 3, 1};

// S-boxes
int S0[4][4] = {
    {1, 0, 3, 2},
    {3, 2, 1, 0},
    {0, 2, 1, 3},
    {3, 1, 3, 2}
};

int S1[4][4] = {
    {0, 1, 2, 3},
    {2, 0, 1, 3},
    {3, 0, 1, 0},
    {2, 1, 0, 3}
};

// Key generation
void generateSubKeys(int key[], int K1[], int K2[]) {
    // Perform permutation P10
    int P10[] = {3, 5, 2, 7, 4, 10, 1, 9, 8, 6};
    int temp[10];
    for (int i = 0; i < 10; i++) {
        temp[i] = key[P10[i] - 1];
    }
    
    // Left shift 1
    int LS1[] = {2, 3, 4, 5, 1, 7, 8, 9, 10, 6};
    int left_shifted_key1[10];
    for (int i = 0; i < 10; i++) {
        left_shifted_key1[i] = temp[LS1[i] - 1];
    }
    
    // Left shift 2
    int LS2[] = {3, 4, 5, 1, 2, 8, 9, 10, 6, 7};
    int left_shifted_key2[10];
    for (int i = 0; i < 10; i++) {
        left_shifted_key2[i] = temp[LS2[i] - 1];
    }
    
    // Perform permutation P8 to get K1
    int P8[] = {6, 3, 7, 4, 8, 5, 10, 9};
    for (int i = 0; i < 8; i++) {
        K1[i] = left_shifted_key1[P8[i] - 1];
    }
    
    // Perform permutation P8 to get K2
    for (int i = 0; i < 8; i++) {
        K2[i] = left_shifted_key2[P8[i] - 1];
    }
}

// Initial permutation
void initialPermutation(int input[], int output[]) {
    for (int i = 0; i < 8; i++) {
        output[i] = input[IP[i] - 1];
    }
}

// Final permutation
void finalPermutation(int input[], int output[]) {
    for (int i = 0; i < 8; i++) {
        output[i] = input[FP[i] - 1];
    }
}

// Expansion permutation
void expansionPermutation(int input[], int output[]) {
    for (int i = 0; i < 8; i++) {
        output[i] = input[EP[i] - 1];
    }
}

// XOR operation
void xorOperation(int a[], int b[], int result[], int size) {
    for (int i = 0; i < size; i++) {
        result[i] = a[i] ^ b[i];
    }
}

// S-box substitution
void sBox(int input[], int output[]) {
    int row, col;
    row = 2 * input[0] + input[3];
    col = 2 * input[1] + input[2];
    int value = S0[row][col];
    output[0] = (value & 2) / 2;
    output[1] = value & 1;
    
    row = 2 * input[4] + input[7];
    col = 2 * input[5] + input[6];
    value = S1[row][col];
    output[2] = (value & 2) / 2;
    output[3] = value & 1;
}

// Permutation P4
void permutationP4(int input[], int output[]) {
    for (int i = 0; i < 4; i++) {
        output[i] = input[P4[i] - 1];
    }
}

// Function to apply the F function
void fFunction(int R[], int K[], int result[]) {
    int expanded_R[8];
    expansionPermutation(R, expanded_R);
    xorOperation(expanded_R, K, result, 8);
    int S_output[4];
    sBox(result, S_output);
    permutationP4(S_output, result);
}

// Function to perform encryption
void encrypt(int plaintext[], int key[], int ciphertext[], int counter[]) {
    int K1[8], K2[8];
    generateSubKeys(key, K1, K2);
    
    int plaintext_block[8];
    int ciphertext_block[8];
    int temp[8];
    
    for (int i = 0; i < 3; i++) {
        // Increment counter
        counter[7]++;
        for (int j = 7; j > 0; j--) {
            if (counter[j] > 1) {
                counter[j] = 0;
                counter[j - 1]++;
            }
        }
        
        // Set plaintext block
        for (int j = 0; j < 8; j++) {
            plaintext_block[j] = plaintext[8 * i + j] ^ counter[j];
        }
        
        // Initial permutation
        initialPermutation(plaintext_block, temp);
        
        // Round 1
        fFunction(temp + 4, K1, ciphertext_block);
        xorOperation(plaintext_block, ciphertext_block, temp, 4);
        for (int j = 0; j < 4; j++) {
            temp[j] = ciphertext_block[j];
        }
        
        // Round 2
        fFunction(temp + 4, K2, ciphertext_block);
        xorOperation(ciphertext_block, temp, ciphertext_block, 4);
        
        // Copy to ciphertext
        for (int j = 0; j < 8; j++) {
            ciphertext[8 * i + j] = ciphertext_block[j];
        }
    }
}

// Function to perform decryption
void decrypt(int ciphertext[], int key[], int plaintext[], int counter[]) {
    int K1[8], K2[8];
    generateSubKeys(key, K1, K2);
    
    int ciphertext_block[8];
    int decrypted_plaintext[8];
    int temp[8];
    
    for (int i = 0; i < 3; i++) {
        // Increment counter
        counter[7]++;
        for (int j = 7; j > 0; j--) {
            if (counter[j] > 1) {
                counter[j] = 0;
                counter[j - 1]++;
            }
        }
        
        // Set ciphertext block
        for (int j = 0; j < 8; j++) {
            ciphertext_block[j] = ciphertext[8 * i + j] ^ counter[j];
        }
        
        // Round 1
        fFunction(ciphertext_block + 4, K2, decrypted_plaintext);
        xorOperation(ciphertext_block, decrypted_plaintext, temp, 4);
        for (int j = 0; j < 4; j++) {
            temp[j] = decrypted_plaintext[j];
        }
        
        // Round 2
        fFunction(temp + 4, K1, decrypted_plaintext);
        xorOperation(decrypted_plaintext, temp, decrypted_plaintext, 4);
        
        // Copy to plaintext
        for (int j = 0; j < 8; j++) {
            plaintext[8 * i + j] = decrypted_plaintext[j];
        }
    }
}

// Function to print binary array
void printBinary(int array[], int size) {
    for (int i = 0; i < size; i++) {
        printf("%d", array[i]);
    }
    printf("\n");
}

int main() {
    int plaintext[] = {0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0}; // Plaintext
    int key[] = {0, 1, 1, 1, 1, 1, 1, 0, 1, 0}; // Key
    int counter[] = {0, 0, 0, 0, 0, 0, 0, 0}; // Counter
    int ciphertext[36];
    int decrypted_plaintext[36];
    
    // Encrypt
    encrypt(plaintext, key, ciphertext, counter);
    printf("Encrypted: ");
    printBinary(ciphertext, 36);
    
    // Decrypt
    decrypt(ciphertext, key, decrypted_plaintext, counter);
    printf("Decrypted: ");
    printBinary(decrypted_plaintext, 36);
    
    return 0;
}
