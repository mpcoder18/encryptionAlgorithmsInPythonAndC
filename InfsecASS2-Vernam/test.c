/*
fread and fwrite for binary 
ÿ is de laatste character voor de extended ascii
^ is de xor operation
het mooie van de xor is dat het symmetrisch is en dus decrypt en encrypt hetzelfde proces hebben



*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// xor
void oneTimePad(const unsigned char *plaintext, const unsigned char *key, unsigned char *result, size_t length) {
    for (size_t i = 0; i < length; i++) {
        result[i] = plaintext[i] ^ key[i];
    }
}

int main() {
unsigned char *buffer = NULL;
size_t size = 0;
size_t keyLength = 0;
size_t textLength = 0;
//reading from stdin
//fseek for pointig to location in a file
fseek(stdin, 0, SEEK_END);
//because you go to seek_END it point to the last thing in the file and with ftell you can get the total amount of bytes
size = ftell(stdin);
//using Seek Set you point the pointer to the beginning
fseek(stdin, 0, SEEK_SET);
// buffer array created
buffer = (unsigned char *)malloc(size);

fread(buffer, 1, size, stdin);
unsigned char *key = buffer;
unsigned char *text = NULL;
for (size_t i = 0; i < size; i++) {
    // using 0xFF instead of Stop_Char because it looks better and is more understandable
    if (buffer[i] == 0xFF) {
        keyLength = i;
        text = buffer + i + 1;
        // if the stopchar is encountered the loop ends and the keylength becomes i and the textLength becomes the size-keyLength-0xFFsign
        textLength = size - keyLength - 1;
        break;
    }
}

// make memory for result
unsigned char *result = (unsigned char *)malloc(textLength);
oneTimePad(text, key, result, textLength);
fwrite(result, 1, textLength, stdout);

free(buffer);
free(result);

return 0;
}