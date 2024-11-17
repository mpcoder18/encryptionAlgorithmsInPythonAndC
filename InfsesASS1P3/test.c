#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>

#define MAX_SIZE 1000
#define MAX_VECTORS 100

typedef struct {
    double stdev;
    int vector[26];
} FrequencyVector;

typedef struct {
    char *cipher;
    int lower;
    int upper;
    FrequencyVector maximum_vector;
} VigenereBreaker;

int input_number() {
    int user_input;
    while (1) {
        if (scanf("%d", &user_input) != 1) {
            printf("Not an integer\n");
            while (getchar() != '\n'); // clear input buffer
            continue;
        }
        break;
    }
    return user_input;
}

void input_text(char *cipher) {
    getchar(); // clear newline from previous input
    fgets(cipher, MAX_SIZE, stdin);
    // Remove non-alpha characters and convert to lowercase
    char *ptr = cipher;
    char *end = cipher + strlen(cipher);
    char *out = cipher;
    while (ptr < end) {
        if (isalpha((unsigned char)*ptr)) {
            *out++ = tolower((unsigned char)*ptr);
        }
        ptr++;
    }
    *out = '\0'; // null-terminate the string
}

double standard_deviation(int *vector) {
    double mean = 0.0;
    double sum = 0.0;
    for (int i = 0; i < 26; i++) {
        sum += vector[i] * vector[i];
    }
    mean = sum / 26;
    double variance = sqrt(mean - (sum / 26) * (sum / 26));
    return variance;
}

void map_cipher(VigenereBreaker *breaker, int bound, FrequencyVector *vectors) {
    for (int i = 0; i < bound; i++) {
        memset(vectors[i].vector, 0, sizeof(vectors[i].vector));
        for (int j = i; j < strlen(breaker->cipher); j += bound) {
            vectors[i].vector[breaker->cipher[j] - 'a']++;
        }
    }
}

char shift(char c) {
    return (char)((((c - 'a') - 4 + 26) % 26) + 'a');
}

void most_used_letters(VigenereBreaker *breaker, char *key_letters) {
    for (int i = 0; i < 26; i++) {
        if (breaker->maximum_vector.vector[i] > 0) {
            key_letters[i] = (char)(i + 'a');
        }
    }
}

void break_cipher(VigenereBreaker *breaker) {
    FrequencyVector vectors[MAX_VECTORS];
    for (int i = breaker->lower; i <= breaker->upper; i++) {
        double stdev = 0.0;
        map_cipher(breaker, i, vectors);
        for (int j = 0; j < i; j++) {
            stdev += standard_deviation(vectors[j].vector);
        }
        if (breaker->maximum_vector.stdev < stdev) {
            breaker->maximum_vector.stdev = stdev;
            memcpy(breaker->maximum_vector.vector, vectors, sizeof(FrequencyVector) * i);
        }
        printf("The sum of %d std. devs: %.2f\n", i, stdev);
    }

    char key[26] = {0};
    most_used_letters(breaker, key);
    printf("\nKey guess:\n");
    for (int i = 0; i < 26; i++) {
        if (key[i] != 0) {
            printf("%c", shift(key[i]));
        }
    }
    printf("\n");
}

int main() {
    int lower_bound = input_number();
    int upper_bound = input_number();
    char text[MAX_SIZE];
    input_text(text);

    VigenereBreaker breaker;
    breaker.cipher = text;
    breaker.lower = lower_bound;
    breaker.upper = upper_bound;
    breaker.maximum_vector.stdev = -1.0;

    break_cipher(&breaker);
    return 0;
}