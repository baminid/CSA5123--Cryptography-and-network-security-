#include <stdio.h>
#include <stdint.h>

// Initial permutation table
static const int initial_permutation_table[] = {
    58, 50, 42, 34, 26, 18, 10, 2,
    60, 52, 44, 36, 28, 20, 12, 4,
    62, 54, 46, 38, 30, 22, 14, 6,
    64, 56, 48, 40, 32, 24, 16, 8,
    57, 49, 41, 33, 25, 17, 9, 1,
    59, 51, 43, 35, 27, 19, 11, 3,
    61, 53, 45, 37, 29, 21, 13, 5,
    63, 55, 47, 39, 31, 23, 15, 7
};

// Final permutation table
static const int final_permutation_table[] = {
    40, 8, 48, 16, 56, 24, 64, 32,
    39, 7, 47, 15, 55, 23, 63, 31,
    38, 6, 46, 14, 54, 22, 62, 30,
    37, 5, 45, 13, 53, 21, 61, 29,
    36, 4, 44, 12, 52, 20, 60, 28,
    35, 3, 43, 11, 51, 19, 59, 27,
    34, 2, 42, 10, 50, 18, 58, 26,
    33, 1, 41, 9, 49, 17, 57, 25
};

// Key permutation table (for compression of the original 64-bit key)
static const int key_permutation_table[] = {
    57, 49, 41, 33, 25, 17, 9,
    1, 58, 50, 42, 34, 26, 18,
    10, 2, 59, 51, 43, 35, 27,
    19, 11, 3, 60, 52, 44, 36,
    63, 55, 47, 39, 31, 23, 15,
    7, 62, 54, 46, 38, 30, 22,
    14, 6, 61, 53, 45, 37, 29,
    21, 13, 5, 28, 20, 12, 4
};

// Key shift schedule
static const int key_shift_schedule[] = {
    1, 1, 2, 2, 2, 2, 2, 2,
    1, 2, 2, 2, 2, 2, 2, 1
};

// Expansion permutation table (expands the 32-bit half-block to 48 bits)
static const int expansion_permutation_table[] = {
    32, 1, 2, 3, 4, 5,
    4, 5, 6, 7, 8, 9,
    8, 9, 10, 11, 12, 13,
    12, 13, 14, 15, 16, 17,
    16, 17, 18, 19, 20, 21,
    20, 21, 22, 23, 24, 25,
    24, 25, 26, 27, 28, 29,
    28, 29, 30, 31, 32, 1
};

// Substitution boxes (S-boxes)
static const int s_boxes[8][4][16] = {
    {
        // S1
        {14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7},
        {0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8},
        {4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0},
        {15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13}
    },
    // Remaining S-boxes follow...
};

// Permutation function (P-box)
static const int permutation_function[] = {
    16, 7, 20, 21, 29, 12, 28, 17,
    1, 15, 23, 26, 5, 18, 31, 10,
    2, 8, 24, 14, 32, 27, 3, 9,
    19, 13, 30, 6, 22, 11, 4, 25
};

// Function prototypes
uint64_t permute(uint64_t input, const int *permutation_table, int input_size, int output_size);
void generate_subkeys(uint64_t key, uint64_t *subkeys);
uint64_t feistel(uint64_t r, uint64_t subkey);
uint32_t substitute(uint64_t input);
uint64_t des_decrypt(uint64_t ciphertext, uint64_t *subkeys);

int main() {
    // Example ciphertext and key
    uint64_t ciphertext = 0x1234567890ABCDEF;
    uint64_t key = 0x133457799BBCDFF1;

    // Generate subkeys in reverse order for decryption
    uint64_t subkeys[16];
    generate_subkeys(key, subkeys);

    // Decrypt the ciphertext
    uint64_t plaintext = des_decrypt(ciphertext, subkeys);

    // Print the decrypted plaintext
    printf("Decrypted plaintext: 0x%llx\n", plaintext);

    return 0;
}

// Permutation function (permutes bits of input according to the permutation table)
uint64_t permute(uint64_t input, const int *permutation_table, int input_size, int output_size) {
    uint64_t output = 0;
    for (int i = 0; i < output_size; i++) {
        output |= ((input >> (input_size - permutation_table[i])) & 1) << (output_size - i - 1);
    }
    return output;
}

// Generates 16 subkeys for decryption in reverse order
void generate_subkeys(uint64_t key, uint64_t *subkeys) {
    // Apply the key permutation table (PC-1)
    key = permute(key, key_permutation_table, 64, 56);

    // Split the key into left and right halves
    uint32_t left_half = (key >> 28) & 0xFFFFFFF;
    uint32_t right_half = key & 0xFFFFFFF;

    // Generate subkeys using the key shift schedule
    for (int i = 15; i >= 0; i--) {
        // Perform key shift according to the schedule
        int shift_amount = key_shift_schedule[15 - i];
        left_half = ((left_half << shift_amount) | (left_half >> (28 - shift_amount))) & 0xFFFFFFF;
        right_half = ((right_half << shift_amount) | (right_half >> (28 - shift_amount))) & 0xFFFFFFF;

        // Combine the halves and apply the permutation table (PC-2) to obtain the subkey
        uint64_t combined = ((uint64_t)left_half << 28) | right_half;
        subkeys[i] = permute(combined, key_permutation_table, 56, 48);
    }
}

// Feistel function (applies the Feistel round function)
uint64_t feistel(uint64_t r, uint64_t subkey) {
    // Expansion permutation (expands the 32-bit half-block to 48 bits)
    uint64_t expanded = permute(r, expansion_permutation_table, 32, 48);

    // XOR with subkey
    expanded ^= subkey;

    // S-box substitution
    uint32_t substituted = substitute(expanded);

    // Permutation function (P-box)
    return permute(substituted, permutation_function, 32, 32);
}

// Substitution function (applies S-box substitution)
uint32_t substitute(uint64_t input) {
    uint32_t output = 0;
    for (int i = 0; i < 8; i++) {
        // Extract 6-bit chunk from the input
        uint64_t chunk = (input >> (42 - 6 * i)) & 0x3F;

        // Apply the S-box
        uint8_t row = ((chunk & 0x20) >> 4) | (chunk & 1);
        uint8_t col = (chunk >> 1) & 0xF;
        output |= (uint32_t)s_boxes[i][row][col] << (28 - 4 * i);
    }
    return output;
}

// DES decryption function
uint64_t des_decrypt(uint64_t ciphertext, uint64_t *subkeys) {
    // Initial permutation (IP)
    uint64_t permuted = permute(ciphertext, initial_permutation_table, 64, 64);

    // Split the block into left and right halves
    uint32_t left_half = permuted >> 32;
    uint32_t right_half = permuted & 0xFFFFFFFF;

    // Perform 16 rounds of Feistel cipher
    for (int i = 0; i < 16; i++) {
        uint32_t temp = right_half;
        right_half = left_half ^ feistel(right_half, subkeys[i]);
        left_half = temp;
    }

    // Final permutation (IP^-1)
    uint64_t combined = ((uint64_t)right_half << 32) | left_half;
    return permute(combined, final_permutation_table, 64, 64);
}
