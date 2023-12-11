// cd "Users\User\Documents\Google Drive Sync\C Projects\Advent of Code"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <math.h>

#define NLNCHR '\n'
#define BSTRLN 20
#define ZERO  "zero"
#define ONE   "one"
#define TWO   "two"
#define THREE "three"
#define FOUR  "four"
#define FIVE  "five"
#define SIX   "six"
#define SEVEN "seven"
#define EIGHT "eight"
#define NINE  "nine"

int is_digit(int c);
int to_digit(int c);
unsigned int parse_num_u(char *str); // Changed for Day 5
int parse_num(char *str);
char *read_line(void);
int contains(int *arr, int elem, int n);
int sum(int arr[], int n);
// --- 
unsigned int *read_seeds(int *nn);
unsigned int *convert(unsigned int *seeds, int n);
unsigned int smallest(unsigned int *arr, int n);

int main(int argc, char *argv[]) {

    unsigned int *seeds;
    int n;
    seeds = read_seeds(&n);
    printf("Seeds: ");
    // for (int i = 0; i < n; i++) {
    //     printf("%u, ", seeds[i]);
    // }
    printf("\n");

    char *line;
    line = read_line();
    free(line); line = NULL;
    seeds = convert(seeds, n);

    printf("Soil: ");
    // for (int i = 0; i < n; i++) {
    //     printf("%u, ", seeds[i]);
    // }
    printf("\n");

    line = read_line();
    free(line); line = NULL;
    seeds = convert(seeds, n);

    printf("Fertilizer: ");
    // for (int i = 0; i < n; i++) {
    //     printf("%u, ", seeds[i]);
    // }
    printf("\n");

    line = read_line();
    free(line); line = NULL;
    seeds = convert(seeds, n);

    printf("Water: ");
    // for (int i = 0; i < n; i++) {
    //     printf("%u, ", seeds[i]);
    // }
    printf("\n");

    line = read_line();
    free(line); line = NULL;
    seeds = convert(seeds, n);

    printf("Light: ");
    // for (int i = 0; i < n; i++) {
    //     printf("%u, ", seeds[i]);
    // }
    printf("\n");

    line = read_line();
    free(line); line = NULL;
    seeds = convert(seeds, n);

    printf("Temperature: ");
    // for (int i = 0; i < n; i++) {
    //     printf("%u, ", seeds[i]);
    // }
    printf("\n");

    line = read_line();
    free(line); line = NULL;
    seeds = convert(seeds, n);

    printf("Humidity: ");
    // for (int i = 0; i < n; i++) {
    //     printf("%u, ", seeds[i]);
    // }
    printf("\n");

    line = read_line();
    free(line); line = NULL;
    seeds = convert(seeds, n);

    printf("Location: ");
    // for (int i = 0; i < n; i++) {
    //     printf("%u, ", seeds[i]);
    // }
    printf("\n");
    printf("%u", smallest(seeds, n));

    free(seeds);
    return 0;
}

// Returns 1 if a character is a digit
int is_digit(int c) {
    return ((c = c - '0') >= 0) && (c < 10);
}

// Returns a integer digit given a character digit
int to_digit(int c) {
    return c - '0';
}

// Turns string of numbers into an integer, 
// stopping at the first non digit it encounters
unsigned int parse_num_u(char *str) {
    int i = 0;
    unsigned int ret = 0;
    while (is_digit(str[i])) {
        ret *= 10;
        ret += to_digit(str[i]);
        i++;
    }
    return ret;
}

// Turns string of numbers into an integer, 
// stopping at the first non digit it encounters
int parse_num(char *str) {
    int i = 0, ret = 0;
    while (is_digit(str[i])) {
        ret *= 10;
        ret += to_digit(str[i]);
        i++;
    }
    return ret;
}

// Reads one input line, including the newline character
char *read_line(void) {
    int n = 0, linelen = BSTRLN;
    char ch = getchar(), *line;
    line = (char*)malloc(linelen * sizeof(char));
    assert(line);

    if (ch == EOF) {
        line[0] = '\n'; line[1] = '\0';
        return line;
    }

    while (1) {
        /* Make character array longer */
        if (n + 1 >= linelen) {
            linelen *= 2;
            line = realloc(line, linelen * sizeof(char));
            assert(line);
        }
        line[n++] = ch;
        /* Break at a newline or EOF character */
        if (ch == NLNCHR || ch == EOF) {
            break;
        }

        ch = getchar();
    }
    line[n] = '\0';
    return line;
}


// Returns 1 if the array contains the element specified, up to n
int contains(int *arr, int elem, int n) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == elem) {
            return 1;
        }
    }
    return 0;
}

// Returns the sum of the list, within integer overflow bounds
int sum(int arr[], int n) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        sum += arr[i];
    }
    return sum;
}

unsigned int *read_seeds(int *nn) {
    char *line;
    int seedslen = 10, n = 0;
    unsigned int *seeds = (unsigned int*)malloc(seedslen * sizeof(unsigned int));
    assert(seeds);

    while (*(line = read_line()) != NLNCHR) {
        int linelen = strlen(line);
        for (int i = 0; i < linelen; i++) {
            if (is_digit(line[i])) {
                unsigned int start = parse_num_u(line + i);
                int len = parse_num(line + i + 2 + (int)floor(log10(start)));

                for (int j = 0; j < len; j++) {
                    seeds[n] = start + j;
                    n++;
                    if (n + 1 >= seedslen) {
                        seedslen *= 2;
                        seeds = realloc(seeds, seedslen * sizeof(unsigned int));
                        assert(seeds);
                    }
                }
                
                i += floor(log10(start)) + floor(log10(len)) + 3;
                printf("%u, %d; ", start, len);
            }
        }
        free(line);
        line = NULL;
    }
    free(line);
    line = NULL;

    *nn = n;
    return seeds;
}

unsigned int *convert(unsigned int *seeds, int n) {
    unsigned int dest, source, len;
    unsigned int *ismapped = (unsigned int*)malloc(n * sizeof(unsigned int));
    while (scanf("%u%u%u", &dest, &source, &len) == 3) {
        for (int i = 0; i < n; i++) {
            if (!ismapped[i]) {
                if (seeds[i] >= source && seeds[i] < source + len) {
                    seeds[i] += dest - source;
                    ismapped[i] = 1;
                }
            }
            
        }
    }
    free(ismapped);
    return seeds;
}

unsigned int smallest(unsigned int *arr, int n) {
    unsigned int ret = *arr;
    for (int i = 0; i < n; i++) {
        if (ret > arr[i]) {
            ret = arr[i];
        }
    }
    return ret;
}