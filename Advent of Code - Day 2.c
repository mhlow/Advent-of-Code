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
char *read_line(void);
int parse_num(char *str);

typedef struct {
    char *name;
    int len, place;
} colours_t;


int main(int argc, char *argv[]) {
    // Initalise variables
    colours_t red = {
        .name = "red",
        .len = strlen(red.name),
        .place = 0
    };
    colours_t green = {
        .name = "green",
        .len = strlen(green.name),
        .place = 1
    };
    colours_t blue = {
        .name = "blue",
        .len = strlen(blue.name),
        .place = 2
    };
    colours_t colours[] = {red, green, blue};
    int lens[] = {3, 5, 4};

    int sum = 0, prodsum = 0;

    char *line;
    
    while (*(line = read_line()) != NLNCHR) {
        int game = 0;
        int linelen = strlen(line);

        // Create ball array
        // Bag colours are in order
        int bag[] = {0, 0, 0};
        int valid[] = {12, 13, 14};
        
        for (int i = 0; i < linelen; i++) {
            if (is_digit(line[i])) {
                if (game == 0) {
                    // Identify game number
                    game = parse_num(line + i);
                    i += floor(log10(game));
                } else {
                    int num = parse_num(line + i);
                    i += floor(log10(num));

                    // Check each colour
                    for (int j = 0; j < 3; j++) {
                        if (strncmp(colours[j].name, line + i + 2, lens[j]) == 0) {
                            if (bag[j] < num) {
                                bag[j] = num;
                            }
                        }
                    }
                }
            }
        }

        int willcont = 1, prod = 1;
        for (int i = 0; i < 3; i++) {
            if (bag[i] > valid[i]) {
                willcont = 0;
            }
            prod *= bag[i];
        }
        prodsum += prod;

        if (willcont) {
            sum += game;
        }
        free(line);
        line = NULL;
    }
    free(line);
    printf("Sum: %d\n", sum);
    printf("Prod Sum:%d\n", prodsum);
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