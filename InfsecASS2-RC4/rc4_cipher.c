/*
input in principe gewoon hetzelfde als met veranm


*/


#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define N 256
#define DROP_BYTES 256  // Drop the first 256 bytes to mitigate the known RC4 attack

// Key Scheduling Algorithm (KSA)
void textScheduling(uint8_t *s, uint8_t *key, size_t keyLength) {
int j = 0;
for (int i = 0; i < N; i++) {
    s[i] = i;
}
for (int i = 0; i < N; i++) {
    j = (j + s[i] + key[i % keyLength]) % N;
    // Swap s[i] and s[j]
    uint8_t temp = s[i];
    s[i] = s[j];
    s[j] = temp;
}
}

// Pseudo-Random Generation Algorithm (PRGA)
uint8_t randomGeneration(uint8_t *s, int *i, int *j) {
*i = (*i + 1) % N;
*j = (*j + s[*i]) % N;

// Swap s[i] and s[j]
uint8_t temp = s[*i];
s[*i] = s[*j];
s[*j] = temp;

return s[(s[*i] + s[*j]) % N];
}

// RC4 Stream Cipher
void RC4(uint8_t *key, size_t keyLength, uint8_t *input_text, size_t textLength, uint8_t *outputText) {
uint8_t s[N];
textScheduling(s, key, keyLength);

int i = 0, j = 0;

// Drop the first 256 bytes to avoid vulnerabilities in RC4
for (int k = 0; k < DROP_BYTES; k++) {
    randomGeneration(s, &i, &j);
}

// Process the input data
for (size_t k = 0; k < textLength; k++) {
    uint8_t key_byte = randomGeneration(s, &i, &j);
    outputText[k] = input_text[k] ^ key_byte;
}
}

int main() {
// Step 1: Use stdin to get file size and read contents into a buffer
unsigned char *buffer = NULL;
size_t size = 0;
size_t keyLength = 0;
size_t textLength = 0;

// Find size of input from stdin
fseek(stdin, 0, SEEK_END);
size = ftell(stdin);
fseek(stdin, 0, SEEK_SET);

// Allocate memory for the buffer based on input size
buffer = (unsigned char *)malloc(size);
if (buffer == NULL) {
    perror("Error allocating memory");
    return 1;
}

// Read the data from stdin into buffer
fread(buffer, 1, size, stdin);

// Step 2: Find the split point (0xFF) between key and data
unsigned char *split_point = memchr(buffer, 0xFF, size);
if (split_point == NULL) {
    fprintf(stderr, "Error: No 0xFF separator found\n");
    free(buffer);
    return 1;
}

// Key part
keyLength = split_point - buffer;
unsigned char *key = buffer;

// Text part
unsigned char *text_part = split_point + 1;
textLength = size - (keyLength + 1);

// Step 3: Allocate memory for output
unsigned char *outputText = (unsigned char *)malloc(textLength);
if (outputText == NULL) {
    perror("Error allocating memory for output");
    free(buffer);
    return 1;
}

// Step 4: Perform RC4 encryption/decryption
RC4(key, keyLength, text_part, textLength, outputText);

// Step 5: Write the result to stdout
fwrite(outputText, 1, textLength, stdout);

// Step 6: Clean up memory
free(buffer);
free(outputText);

return 0;
}

