/*
name: vigenereCipher.c
authors:
1. Mardo Parlayan S5578566 m.parlayan@student.rug.nl
2. Elizabeth verbruggen S4540212 e.f.verbruggen@student.rug.nl
3. Julian Wierenga S5628237 j.d.p.l.wierenga@student.rug.nl

*/



#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int mod(int a, int b){
    int r = a % b;
    return r < 0 ? r + b : r;
}
/* Function to read the input till the end of file */
char *inputString(FILE* fp, size_t size, char lastChar){
char *str;
int ch;
size_t len = 0;
str = realloc(NULL, sizeof(char)*size); // size is start size
if(!str)return str;
while(EOF!=(ch=fgetc(fp)) && ch != lastChar){
str[len++]=ch;
    if(len==size){
        str = realloc(str, sizeof(char)*(size+=16));
        if(!str)return str;
    }
}
str[len++]='\0';

return realloc(str, sizeof(char)*len);
}



/* Function to encrypt the text with the given key */
void encrypt(char *text, char *key){
int counter = 0;
for (int i = 0; i < strlen(text); i++){
    if(counter >= strlen(key)){ 
        counter = 0;
    }
    if(isalpha(text[i])){
        char ch = islower(text[i]) ? 'a':'A';
        int shiftValue = key[counter] - 'a';
        text[i] = mod(text[i] - ch + shiftValue, 26) + ch;
        //text[i] = (text[i] - ch + shiftValue)%26 + ch;
        counter++;
    }
}

}

/* Function to decrypt the text with the given key */
void decrypt(char *text, char *key){
int counter = 0;
for (int i = 0; i < strlen(text); i++){
    if(counter >= strlen(key)){ 
        counter = 0;
    }
    if(isalpha(text[i])){
        int isUpper = isupper(text[i]);
        text[i] = tolower(text[i]);
        text[i] = mod(text[i] - key[counter], 26) + 'a';
        //text[i] = (text[i] - key[counter])%26 + 'a';
        if(isUpper){
            text[i] = toupper(text[i]);
            
        }
        counter++;
    }
}
}

int main(int argc, char *argv[]) {
char command;
scanf(" %c ", &command);

char *key = inputString(stdin,10,'\n');
char *text = inputString(stdin, 10,'~');

switch (command){
    case 'e':
        encrypt(text, key);
        break;
    case 'd':
        decrypt(text, key);
        break;
    default:
        break;
}

printf("%s", text);

    return 0;
}