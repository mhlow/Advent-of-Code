// cd "Users\User\Documents\Google Drive Sync\C Projects\Advent of Code"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <math.h>
#include <gmp.h>
// compile with -lgmp on the end in cmd

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
char *read_line(void);
int parse_num(char *str);

int is_part_num(char **input, int value, int x, int y, int linelen, int lines);
int is_symbol(char c);

void find_gears(char **input, int linelen, int lines);

int main(int argc, char *argv[]) {
    int inputsize = 10, sum = 0;
    char **input = (char**)malloc(inputsize * sizeof(char*));
    assert(input);

    char *line;
    int i = 0;
    while (*(line = read_line()) != NLNCHR) {
        input[i] = line;


        i++;
        if (i == inputsize) {
            inputsize *= 2;
            input = realloc(input, inputsize * sizeof(char*));
            assert(input);
        }
    }
    
    int linelen = strlen(*input) - 1, lines = i;

    for (int y = 0; y < lines; y++) {
        for (int x = 0; x < linelen; x++) {
            if (is_digit(input[y][x])) {
                int value = parse_num(input[y] + x);
                if (is_part_num(input, value, x, y, linelen, lines)) {
                    sum += value;
                }
                
                x += floor(log10(parse_num(input[y] + x)));
            }
            
        }
    }

    printf("\nLine length: %d, Num of lines: %d\n", linelen, lines);
    printf("Sum: %d\n", sum);

    find_gears(input, linelen, lines);

    for (int i = 0; i < lines; i++) {
        free(input[i]);
    }
    free(input);
}

// Returns 1 if a character is a digit
int is_digit(int c) {
    return ((c = c - '0') >= 0) && (c < 10);
}

// Returns a integer digit given a character digit
int to_digit(int c) {
    return c - '0';
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

// Checks around the number (vertically, horizontally and diagonally)
// and returns whether or not it is a part number 
int is_part_num(char **input, int value, int x, int y, int linelen, int lines) {
    int vallen = floor(log10(value));
    for (int i = -1; i < 2; i++) {
        for (int j = -1; j < 2 + vallen; j++) {
            // Check y bounds
            if (0 <= y + i && y + i < lines) {
                // Check x bounds
                if (0 <= x + j && x + j < linelen) {
                    // Actually check
                    if (is_symbol(input[y + i][x + j])) {
                        return 1;
                    }
                }
            }
        }
    }
    return 0;
}

// Returns 1 if character is considered a symbol for part num
int is_symbol(char c) {
    // Can optimise
    char symbols[] = {'@', '#', '$', '%', '&', '*', '-', '=', '+', '&', '/'};
    int symlen = sizeof(symbols)/sizeof(*symbols);
    for (int i = 0; i < symlen; i++) {
        if (c == symbols[i]) {
            return 1;
        }
    }
    return 0;
}

void find_gears(char **input, int linelen, int lines) {
    int val1 = 0, val2 = 0;
    int sum = 0;
    for (int y = 0; y < lines; y++) {
        for (int x = 0; x < linelen; x++) {
            if (input[y][x] == '*') {
                // Found a potential gear, search around
                val1 = 0, val2 = 0;
                int valid = 0;
                for (int i = -1; i < 2; i++) {
                    for (int j = -1; j < 2; j++) {
                        int offset = 0, found = 0;
                        while (is_digit(input[y + i][x + j + offset])) {
                            found = 1;
                            offset--;
                        }
                        
                        if (found) {
                            offset++;
                            int val = parse_num(input[y + i] + x + j + offset);

                            printf("|%d,", parse_num(input[y + i] + x + j + offset));

                            if (!val1) {
                                val1 = val;
                            } else if (!val2) {
                                val2 = val;
                                valid = 1;
                            } else {
                                valid = 0;
                                
                            }

                            j += floor(log10(val)) + offset;
                        }
                        
                    }
                }

                if (valid) {
                    printf("%d, %d\n", val1, val2);
                    sum += val1 * val2;
                }
            }
        }
    }

    printf("%d", sum);
}