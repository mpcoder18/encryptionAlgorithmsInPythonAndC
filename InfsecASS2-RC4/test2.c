#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

#define N 256

// Key Scheduling Algorithm (KSA)
void key_scheduling(uint8_t *s, uint8_t *key, size_t keyLength) {
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
uint8_t pseudo_random_generation(uint8_t *s, int *i, int *j) {
*i = (*i + 1) % N;
*j = (*j + s[*i]) % N;

// Swap s[i] and s[j]
uint8_t temp = s[*i];
s[*i] = s[*j];
s[*j] = temp;

return s[(s[*i] + s[*j]) % N];
}

// RC4 Stream Cipher
void RC4(uint8_t *key, size_t keyLength, uint8_t *input_text, size_t textLength, uint8_t *output_text) {
uint8_t s[N];
key_scheduling(s, key, keyLength);

int i = 0, j = 0;

for (size_t k = 0; k < textLength; k++) {
    uint8_t key_byte = pseudo_random_generation(s, &i, &j);
    output_text[k] = input_text[k] ^ key_byte;
}
}

int main() {
FILE *data_file = fopen("0.out", "rb");
if (data_file == NULL) {
    perror("Error opening 0.out file");
    return 1;
}

// Reading text from "0.out" file
uint8_t text[1024];
size_t textLength = fread(text, 1, sizeof(text), data_file);
fclose(data_file);

for (size_t i = 0; i < textLength; i++) {
    printf("%02x ", text[i]);
}
printf("\n");

// Open the key and text from "0.in" file
data_file = fopen("0.in", "rb");
if (data_file == NULL) {
    perror("Error opening 0.in file");
    return 1;
}

uint8_t key[256];
size_t keyLength = fread(key, 1, sizeof(key), data_file);

// Split the key and text by 0xFF delimiter
uint8_t *splitText = memchr(key, 0xFF, keyLength);
if (splitText == NULL) {
    fprintf(stderr, "Error: No 0xFF delimiter found in the key and text\n");
    return 1;
}

size_t key_real_length = splitText - key;
uint8_t *text_part = splitText + 1;
size_t text_part_length = keyLength - (key_real_length + 1);

fclose(data_file);

// Output buffer for decrypted text
uint8_t output_text[1024];

// Apply RC4 encryption/decryption
RC4(key, key_real_length, text_part, text_part_length, output_text);

// Print the decrypted output
for (size_t i = 0; i < text_part_length; i++) {
    printf("%02x ", output_text[i]);
}
printf("\n");

return 0;
}