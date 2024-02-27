#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/rsa.h>
#include <openssl/pem.h>

// Function to print an error message and exit
void handleErrors() {
    printf("Error occurred.\n");
    exit(1);
}

int main() {
    // Initialize RSA object
    RSA *rsa = NULL;

    // Generate key pair
    int bits = 2048;
    unsigned long e = RSA_F4; // RSA_F4 is the recommended exponent value
    BIGNUM *bn = BN_new();
    BN_set_word(bn, e);

    rsa = RSA_new();
    if (!RSA_generate_key_ex(rsa, bits, bn, NULL)) {
        handleErrors();
    }

    // Encrypt
    const char *plaintext = "Hello, RSA!";
    int plaintext_len = strlen(plaintext);
    unsigned char *encrypted = (unsigned char*)malloc(RSA_size(rsa));
    int encrypted_len = RSA_public_encrypt(plaintext_len, (unsigned char*)plaintext, encrypted, rsa, RSA_PKCS1_PADDING);
    if (encrypted_len == -1) {
        handleErrors();
    }
    
    // Decrypt
    unsigned char *decrypted = (unsigned char*)malloc(encrypted_len);
    int decrypted_len = RSA_private_decrypt(encrypted_len, encrypted, decrypted, rsa, RSA_PKCS1_PADDING);
    if (decrypted_len == -1) {
        handleErrors();
    }
    decrypted[decrypted_len] = '\0'; // Add null terminator to decrypted string

    // Print results
    printf("Original: %s\n", plaintext);
    printf("Encrypted: ");
    for (int i = 0; i < encrypted_len; i++) {
        printf("%02x", encrypted[i]);
    }
    printf("\nDecrypted: %s\n", decrypted);

    // Free memory
    RSA_free(rsa);
    BN_free(bn);
    free(encrypted);
    free(decrypted);

    return 0;
}
