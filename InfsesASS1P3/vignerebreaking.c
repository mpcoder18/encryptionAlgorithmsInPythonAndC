#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void read_input(int *a, int *b, char **text) {
    scanf("%d", a);
    scanf("%d", b);
    getchar(); // to consume the newline after the second integer

    size_t size = 1024;
    *text = (char *)malloc(size * sizeof(char));
    (*text)[0] = '\0'; // Initialize the text as an empty string

    while (1) {
        char line[256];
        if (fgets(line, sizeof(line), stdin) == NULL) {
            break; // EOF
        }
        strcat(*text, line);
    }
}

void find_frequencies(const char *text, int frequencies[26]) {
    memset(frequencies, 0, 26 * sizeof(int));
    for (const char *p = text; *p; p++) {
        if (isalpha(*p)) {
            frequencies[tolower(*p) - 'a']++;
        }
    }
}

void find_key(int a, int b, const char *text) {
    double *sd_sums = (double *)malloc((b - a + 1) * sizeof(double));
    for (int possible_key_size = a; possible_key_size <= b; possible_key_size++) {
        char **vectors = (char **)malloc(possible_key_size * sizeof(char *));
        for (int i = 0; i < possible_key_size; i++) {
            vectors[i] = (char *)malloc(strlen(text) + 1);
            vectors[i][0] = '\0'; // Initialize each vector as an empty string
        }
        double sd_sum = 0.0;
        for (int j = 0; text[j] != '\0'; j++) {
            strcat(vectors[j % possible_key_size], (char[]){text[j], '\0'});
        }
        for (int i = 0; i < possible_key_size; i++) {
            int frequencies[26];
            find_frequencies(vectors[i], frequencies);
            double mean = 0.0;
            for (int k = 0; k < 26; k++) {
                mean += frequencies[k];
            }
            mean /= 26.0;
            double variance = 0.0;
            for (int k = 0; k < 26; k++) {
                variance += frequencies[k] * frequencies[k];
            }
            variance = (variance / 26.0) - (mean * mean);
            double sd = sqrt(variance);
            sd_sum += sd;
        }
        sd_sums[possible_key_size - a] = sd_sum;
        for (int i = 0; i < possible_key_size; i++) {
            free(vectors[i]);
        }
        free(vectors);
    }
    for (int key_size = a; key_size <= b; key_size++) {
        printf("The sum of %d std. devs: %.2f\n", key_size, sd_sums[key_size - a]);
    }
    int key_size = 0;
    double max_sd_sum = sd_sums[0];
    for (int i = 1; i <= b - a; i++) {
        if (sd_sums[i] > max_sd_sum) {
            max_sd_sum = sd_sums[i];
            key_size = i + a;
        }
    }
    char *key = (char *)malloc((key_size + 1) * sizeof(char));
    key[key_size] = '\0'; // Null-terminate the key string
    for (int i = 0; i < key_size; i++) {
        char letter_vector[1024] = {0};
        for (int j = i; text[j] != '\0'; j += key_size) {
            strncat(letter_vector, (char[]){text[j], '\0'}, 1);
        }
        int frequencies[26];
        find_frequencies(letter_vector, frequencies);
        int most_frequent_letter = 0;
        for (int k = 1; k < 26; k++) {
            if (frequencies[k] > frequencies[most_frequent_letter]) {
                most_frequent_letter = k;
            }
        }
        int shift = (most_frequent_letter - 4 + 26) % 26;
        key[i] = shift + 'a';
    }
    printf("\nKey guess:\n%s\n", key);
    free(sd_sums);
    free(key);
}

int main() {
    int a, b;
    char *text;
    read_input(&a, &b, &text);
    find_key(a, b, text);
    free(text);
    return 0;
}