#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/des.h>

#define BLOCK_SIZE 8 // DES block size in bytes

// Function to perform CBC mode encryption with 3DES
void des_cbc_encrypt(unsigned char *plaintext, int plaintext_len, unsigned char *key, unsigned char *iv, unsigned char *ciphertext) {
    DES_cblock des_key1, des_key2, des_key3;
    DES_key_schedule ks1, ks2, ks3;

    // Initialize DES keys
    memcpy(des_key1, key, 8);
    memcpy(des_key2, key + 8, 8);
    memcpy(des_key3, key + 16, 8);

    // Set key schedules
    DES_set_key_checked(&des_key1, &ks1);
    DES_set_key_checked(&des_key2, &ks2);
    DES_set_key_checked(&des_key3, &ks3);

    // Initialize initialization vector (IV)
    DES_cblock ivec;
    memcpy(ivec, iv, 8);

    // Encrypt each block in CBC mode
    for (int i = 0; i < plaintext_len; i += BLOCK_SIZE) {
        DES_ede3_cbc_encrypt(plaintext + i, ciphertext + i, BLOCK_SIZE, &ks1, &ks2, &ks3, &ivec, DES_ENCRYPT);
    }
}

int main() {
    unsigned char key[24] = "1234567890abcdef123456"; // 24-byte 3DES key
    unsigned char iv[8] = "abcdefgh"; // Initialization Vector
    unsigned char plaintext[] = "Hello, world!"; // Input plaintext
    int plaintext_len = strlen((char *)plaintext);

    // Allocate memory for ciphertext (include extra block for padding)
    int ciphertext_len = plaintext_len + BLOCK_SIZE;
    unsigned char *ciphertext = malloc(ciphertext_len);

    // Perform 3DES encryption in CBC mode
    des_cbc_encrypt(plaintext, plaintext_len, key, iv, ciphertext);

    // Print the ciphertext in hexadecimal format
    printf("Ciphertext (hex): ");
    for (int i = 0; i < ciphertext_len; i++) {
        printf("%02x ", ciphertext[i]);
    }
    printf("\n");

    // Clean up memory
    free(ciphertext);

    return 0;
}
