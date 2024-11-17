#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

/*
name: vigenereCipher.c
authors:
1. Mardo Parlayan S5578566 m.parlayan@student.rug.nl
2. Elizabeth verbruggen S4540212 e.f.verbruggen@student.rug.nl
3. Julian Wierenga S5628237 j.d.p.l.wierenga@student.rug.nl

*/


/*
input 1
d 3
wkh vhqdwruv duh frqvslulqj!
the senators are conspiring!

input 2
e 25
fodszqujpo = efdszqujpo ? :P
output
encryption = decryption ? :O

input 3
d 16
"Q ibem iehj ev sekdjho!" iqyt jxu Gkuud. 
"Dem, xuhu, oek iuu, yj jqaui qbb jxu hkddydw oek sqd te, je auuf yd jxu iqcu fbqsu. Yv oek mqdj je wuj iecumxuhu ubiu, oek ckij hkd qj buqij jmysu qi vqij qi jxqj!"
output
"A slow sort of country!" said the Queen. 
"Now, here, you see, it takes all the running you can do, to keep in the same place. If you want to get somewhere else, you must run at least twice as fast as that!"

input 4
e yxbdflrcmtpzwnagevjhoskuqi
Do not let anyone know that the answer is forty-two! dit is arr
output 
Da nah zfh ynqanf pnak hcyh hcf ynjkfv mj lavhq-hka!

d yxbdflrcmtpzwnagevjhoskuqi
Da nah zfh ynqanf pnak hcyh hcf ynjkfv mj lavhq-hka!

 
wat wil ik

hoofdletters zijn ASCII 65 tot en met 90
97 tot 122

hoe weet je alleen of iets na e een string is of niet
*/

// als de letter gelijk is aan de index dan kun je opzoeken in het alfabet wat het eigenlijk moet zijn
// changing the alphabet such that it the text decrypts
char *inputString(FILE* fp, size_t size, char endChar){
char *str;
int ch;
size_t len = 0;
str = realloc(NULL, sizeof(char)*size); // size is start size
if(!str)return str;
while(EOF!=(ch=fgetc(fp)) && ch != endChar){
    str[len++]=ch;
    if(len==size){
        str = realloc(str, sizeof(char)*(size+=16));
        if(!str)return str;
    }
}
str[len++]='\0';

return realloc(str, sizeof(char)*len);
}

/* Function to compute the modulus of a number */
int mod(int a, int b){
    int r = a % b;
    return r < 0 ? r + b : r;
}

/* Function to encrypt a text using a map */
void map(char *text, char mapping[]){
for(int i = 0; i < strlen(text) + 1; i++){
    if(isalpha(text[i]) && isupper(text[i])){
        text[i] = mapping[(text[i] - 'A') % 26];
        text[i] = toupper(text[i]);
    }else if(isalpha(text[i])){
        text[i] = mapping[(text[i] - 'a') % 26];
        text[i] = tolower(text[i]);
    }
}
}

/* Function to decrypt a text using a map */
void decryptionMap(char *text, char mapping[]){
for(int i = 0; i < strlen(text) + 1; i++){
    if(isalpha(text[i]) && isupper(text[i])){
        for (int j = 0; j < strlen(mapping) + 1; j++){
            if(text[i] == toupper(mapping[j])){
                text[i] = j + 'A';
                break;
            }
        }
    }else if(isalpha(text[i])){
        for (int j = 0; j < strlen(mapping) + 1; j++){
            if(text[i] == tolower(mapping[j])){
                text[i] = j + 'a';
                break;
            }
        }
    }
}
}

/* Function to encrypt/decrypt a text with a shift value */
void shift(char *text, int shiftValue){
for(int i = 0; i < strlen(text) + 1; i++){
    if(isalpha(text[i]) && isupper(text[i])){
        text[i] = mod((text[i] - 'A' + shiftValue),26) + 'A';
    }else if(isalpha(text[i])){
        text[i] = mod((text[i] - 'a' + shiftValue),26) + 'a';
    }
}
}

/* Function to handle the input of encrypting or decrypting the text */
void handleInput(char *rules, char *text){
// we do all the encryption/decryption on the alphabet, therefore having to map the resulted alphabet only once
// on the given text
char alphabet[26] = "abcdefghijklmnopqrstuvwxyz";
char *token;
const char s[2] = " ";

token = strtok(rules, s);
while(token != NULL){
    if(token[0] == 'e'){
        token = strtok(NULL, s);
        if(isdigit(token[0]) || token[0] == '-'){
            shift(alphabet, atoi(token));
        }else if (isalpha(token[0])){
            map(alphabet, token);
        }
    }else{
        token = strtok(NULL, s);
        if(isdigit(token[0]) || token[0] == '-'){
            shift(alphabet, -atoi(token));
        }else{
            decryptionMap(alphabet, token);
        }
    }
    token = strtok(NULL, s);
}
map(text, alphabet);
printf("%s", text);
}

int main(int argc, const char * argv[]) {
char *input;
int inputLength;

char *text;
int textLength;

input = inputString(stdin, 10, '\n');

text = inputString(stdin, 10, '~');

handleInput(input, text);

free(input);
free(text);

return 0;
}