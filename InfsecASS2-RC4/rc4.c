#include <stdio.h>
#include <stdlib.h>

unsigned char* keyScheduling(unsigned char* key, int keyLength) {
unsigned char* s = (unsigned char*)malloc(256 * sizeof(unsigned char));
for (int i = 0; i < 256; i++) {
    s[i] = (unsigned char)i;
}

int j = 0;
for (int i = 0; i < 256; i++) {
    j = (j + s[i] + key[i % keyLength]) % 256;
    unsigned char temp = s[i];
    s[i] = s[j];
    s[j] = temp;
}
return s;
}

unsigned char pseudo_random_generation(unsigned char* s) {
static int i = 0, j = 0;
i = (i + 1) % 256;
j = (j + s[i]) % 256;
unsigned char temp = s[i];
s[i] = s[j];
s[j] = temp;
return s[(s[i] + s[j]) % 256];
}

unsigned char* RC4(unsigned char* key, int keyLength) {
    return keyScheduling(key, keyLength);
}

void to_bytes(int number, unsigned char* binaryForm, int* length) {
*length = 0;
while (number > 1) {
    binaryForm[(*length)++] = number % 2;
    number = number / 2;
}
}

int main() {
FILE* data_file = fopen("0.in", "rb");
if (!data_file) {
    perror("Failed to open file");
    return 1;
}

unsigned char key[256];
unsigned char text[256];
size_t keyLength = fread(key, 1, 256, data_file);
size_t text_length = fread(text, 1, 256, data_file);
fclose(data_file);

unsigned char* key_stream = RC4(key, keyLength);

for (size_t i = 0; i < text_length; i++) {
    printf("%c", text[i] ^ pseudo_random_generation(key_stream));
}
printf("\n");

free(key_stream);
return 0;
}