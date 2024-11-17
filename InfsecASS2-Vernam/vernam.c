/*
fread and fwrite for binary 
ÿ is de laatste character voor de extended ascii
^ is de xor operation
het mooie van de xor is dat het symmetrisch is en dus decrypt en encrypt hetzelfde proces hebben



*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STOP_CHAR 255  // 'ÿ' character in extended ASCII


void oneTimePad(const unsigned char *plaintext, const unsigned char *key, unsigned char *result, size_t len) {
    for (size_t i = 0; i < len; i++) {
        result[i] = plaintext[i] ^ key[i];
    }
}

int main() {
 unsigned buffer[4096];
 unsigned char key[2048], plaintext[2048];
 unsigned char result[2048];
size_t keyLen = 0, plaintextLen = 0;

size_t inputLen = fread(buffer, 1, sizeof(buffer), stdin);

// separate the input into key and plaintext when STOP_cHAR occurs
size_t i = 0;
while (i < inputLen && buffer[i] != STOP_CHAR) {
    key[keyLen++] = buffer[i++];
}

// skip the STOP_CHAR
if (i < inputLen && buffer[i] == STOP_CHAR) {
    i++;
}

// read the remaining part as plaintext
while (i < inputLen) {
    plaintext[plaintextLen++] = buffer[i++];
}

// check if the lengths of key and plaintext match
if (keyLen != plaintextLen) {
    fprintf(stderr, "Error: Key length must match the plaintext length.\n");
    return 1;
}

// Xor
oneTimePad(plaintext, key, result, plaintextLen);
fwrite(result, 1, plaintextLen, stdout);

return 0;
}