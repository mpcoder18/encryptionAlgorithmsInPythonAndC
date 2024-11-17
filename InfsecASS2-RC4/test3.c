/*
gebruik gewoon weer dezelfde input en output als bij vernam.




*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// RC4 Key Scheduling Algorithm (KSA)
void rc4Func(unsigned char *key, size_t keyLength, unsigned char *S) {
for (int i = 0; i < 256; i++) {
    S[i] = i;
}

int j = 0;
for (int i = 0; i < 256; i++) {
    j = (j + S[i] + key[i % keyLength]) % 256;
    // Swap S[i] and S[j]
    unsigned char temp = S[i];
    S[i] = S[j];
    S[j] = temp;
}
}

// RC4 Pseudo-Random Generation Algorithm (PRGA)
void rc4Crypt(unsigned char *S, unsigned char *data, size_t dataLength) {
int i = 0, j = 0;

for (size_t n = 0; n < dataLength; n++) {
    i = (i + 1) % 256;
    j = (j + S[i]) % 256;
    
    // Swap S[i] and S[j]
    unsigned char temp = S[i];
    S[i] = S[j];
    S[j] = temp;
    
    // Generate keystream byte
    unsigned char K = S[(S[i] + S[j]) % 256];
    
    // XOR data with keystream byte
    data[n] ^= K;
}
}

int main() {
unsigned char *buffer = NULL;
size_t size = 0;
size_t keyLength = 0;
size_t textLength = 0;

// Read from stdin in binary mode
fseek(stdin, 0, SEEK_END);
size = ftell(stdin);
fseek(stdin, 0, SEEK_SET);

// Allocate memory for buffer
buffer = (unsigned char *)malloc(size);
if (!buffer) {
    perror("Failed to allocate buffer");
    return 1;
}

// Read the entire file into buffer
fread(buffer, 1, size, stdin);

unsigned char *key = buffer;
unsigned char *text = NULL;

for (size_t i = 0; i < size; i++) {
    if (buffer[i] == 0xFF) {  // Find the delimiter 0xFF
        keyLength = i;
        text = buffer + i + 1;
        textLength = size - keyLength - 1;
        break;
    }
}

if (!text) {
    fprintf(stderr, "Invalid input format: no delimiter 0xFF found.\n");
    free(buffer);
    return 1;
}

// Initialize RC4 state array
unsigned char S[256];
rc4Func(key, keyLength, S);

// Encrypt/Decrypt the text using RC4
rc4Crypt(S, text, textLength);

// Output the encrypted/decrypted data
fwrite(text, 1, textLength, stdout);

free(buffer);

return 0;
}
