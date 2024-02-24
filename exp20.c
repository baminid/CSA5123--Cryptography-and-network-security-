#include <stdio.h>
#include <stdlib.h>
#include <string.h>



// Function to perform ECB mode encryption with DES
void des_ecb_encrypt(unsigned char *plaintext, int plaintext_len, unsigned char *key, unsigned char *ciphertext) {
    
   

    // Initialize DES key
    memcpy(des_key, key, 8);

    // Set key schedule
    DES_set_key_checked(&des_key, &ks);

    // Encrypt each block independently
    for (int i = 0; i < plaintext_len; i += BLOCK_SIZE) {
        DES_ecb_encrypt(plaintext + i, ciphertext + i, &ks, DES_ENCRYPT);
    }
}

// Function to perform ECB mode decryption with DES
void des_ecb_decrypt(unsigned char *ciphertext, int ciphertext_len, unsigned char *key, unsigned char *plaintext) {
    DES_cblock des_key;
    DES_key_schedule ks;

    // Initialize DES key
    memcpy(des_key, key, 8);

    // Set key schedule
    DES_set_key_checked(&des_key, &ks);

    // Decrypt each block independently
    for (int i = 0; i < ciphertext_len; i += BLOCK_SIZE) {
        DES_ecb_encrypt(ciphertext + i, plaintext + i, &ks, DES_DECRYPT);
    }
}

int main() {
    unsigned char key[8] = "12345678"; // 8-byte DES key
    unsigned char plaintext[] = "Hello, ECB!"; // Input plaintext
    int plaintext_len = strlen((char *)plaintext);

    // Allocate memory for ciphertext (include extra block for padding)
    int ciphertext_len = plaintext_len + BLOCK_SIZE;
    unsigned char *ciphertext = malloc(ciphertext_len);

    // Perform ECB encryption
    des_ecb_encrypt(plaintext, plaintext_len, key, ciphertext);

    // Print the ciphertext in hexadecimal format
    printf("Ciphertext (hex): ");
    for (int i = 0; i < ciphertext_len; i++) {
        printf("%02x ", ciphertext[i]);
    }
    printf("\n");

    // Allocate memory for decrypted plaintext
    unsigned char *decrypted_plaintext = malloc(ciphertext_len);

    // Perform ECB decryption
    des_ecb_decrypt(ciphertext, ciphertext_len, key, decrypted_plaintext);

    // Print the decrypted plaintext
    printf("Decrypted plaintext: %s\n", decrypted_plaintext);

    // Clean up memory
    free(ciphertext);
    free(decrypted_plaintext);

    return 0;
}
