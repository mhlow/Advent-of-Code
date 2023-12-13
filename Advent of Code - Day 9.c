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
int parse_num(char *str, int *is0);
char *read_line(void);
int contains(int *arr, int elem, int n);
int sum(int arr[], int n);
void print_int_arr(int *arr, int n);

int main(int argc, char *argv[]) {
    int sum = 0, sump2 = 0;
    char *line;
    while (*(line = read_line()) != NLNCHR) {
        int patternDepth = 0, maxPatternDepth = 30;
        int **pattern = (int**)malloc(maxPatternDepth * sizeof(int*));
        assert(pattern);

        int initialLen = 10;
        int *initial = (int*)malloc(initialLen * sizeof(int));
        assert(initial);

        int linelen = strlen(line), n = 0;
        for (int i = 0; i < linelen; i++) {
            int is0 = 0;
            int num = parse_num(line + i, &is0);
            if (num != 0 || is0 == 1) {
                initial[n] = num;
                n++;

                if (n + 1 >= initialLen) {
                    initialLen *= 2;
                    initial = (int*)realloc(initial, initialLen * sizeof(int));
                    assert(initial);
                    printf("Allocated more memory\n");
                }

                if (!is0) {
                    i += floor(log10(abs(num))) + (num < 0);
                } else {
                    i++;
                }
                
            }
        }

        pattern[0] = initial;
        print_int_arr(pattern[0], n);

        // Calculate sub levels
        int subLen = n;
        while (1) {
            subLen--;
            int *subLev = (int*)malloc(subLen * sizeof(int));
            assert(subLev);

            for (int i = 0; i < subLen; i++) {
                subLev[i] = pattern[n - subLen - 1][i + 1] - pattern[n - subLen - 1][i];
            }
            // pattern[n - subLen + 1][i + 1] - pattern[n - subLen + 1][i]

            pattern[n - subLen] = subLev;
            print_int_arr(subLev, subLen);

            // Break
            int isZeros = 1;
            for (int i = 0; i < subLen; i++) {
                if (subLev[i] != 0) {
                    isZeros = 0;
                    break;
                }
            }

            if (isZeros) {
                break;
            }
        }

        int next = 0, prev = 0;
        for (int i = 0; i < n - subLen; i++) {
            next += pattern[n - subLen - i - 1][subLen + i];
            prev *= -1;
            prev += pattern[n - subLen - i - 1][0];
        }

        printf("%d\n", next);
        printf("%d\n", prev);
        sum += next;
        sump2 += prev;

        for (int i = 0; i < n - subLen + 1; i++) {
            free(pattern[i]);
        }
        free(pattern);
        free(line);
        line = NULL;
    }
    free(line);

    printf("Sum of history: %d\n", sum);
    printf("Sum for prev: %d\n", sump2);
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
// Now accepts negative numbers
int parse_num(char *str, int *is0) {
    int isNegative = -1;
    int i = 0, ret = 0;
    if (str[0] == '-') {
        isNegative = 1;
        i++;
    }

    if (str[0] == '0') {
        *is0 = 1;
    }
    
    while (is_digit(str[i])) {
        ret *= 10;
        ret += (isNegative * -1) * to_digit(str[i]);
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

// Prints an integer array
void print_int_arr(int *arr, int n) {
    printf("[");
        for (int i = 0; i < n; i++) {
            printf("%d, ", arr[i]);
        }
    printf("]\n");
}