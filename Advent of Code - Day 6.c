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
int parse_num(char *str);
char *read_line(void);
int contains(int *arr, int elem, int n);
int sum(int arr[], int n);


int main(int argc, char *argv[]) {
    int *times = (int*)malloc(4 * sizeof(int));
    char *line = read_line();
    int linelen = strlen(line), n = 0;
    for (int i = 0; i < linelen; i++) {
        int num = parse_num(line + i);
        if (num != 0) {
            times[n] = num;
            n++;
            i += floor(log10(num));
        }
    }

    free(line);
    line = read_line();
    int *distances = (int*)malloc(n * sizeof(int));
    n = 0;
    for (int i = 0; i < linelen; i++) {
        int num = parse_num(line + i);
        if (num != 0) {
            distances[n] = num;
            n++;
            i += floor(log10(num));
        }
    }

    printf("tttttttttttttttttttttttttttttttt: ");
    for (int i = 0; i < n; i++) {
        printf("%d, ", times[i]);
    }
    printf("\n");
    for (int i = 0; i < n; i++) {
        printf("%d, ", distances[i]);
    }
    printf("\n");

    for (int i = 0; i < n; i++) {
        int x = 0;
        int func = times[i] * x - pow(x, 2);
        while (func <= distances[i]) {
            x++;
            func = times[i] * x - pow(x, 2);
        }
        x--;
        printf("%d,", times[i] - 2 * x - 1);
    }

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
