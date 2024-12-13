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

#define ROCK 'O'
#define EMTY '.'
#define SQRK '#'

int is_digit(int c);
int to_digit(int c);
int parse_num(char *str, int *is0);
char *read_line(void);
int contains(int *arr, int elem, int n);
int sum(int arr[], int n);
void print_int_arr(int *arr, int n);


int main(int argc, char *argv[]) {
    int sum = 0;
    
    int breakall = 0, p = 0, q = 0;
    int maxLines = 10, lines = 0, lineLen = 0;
    char **map = (char**)malloc(maxLines * sizeof(char*));
    assert(map);

    char *line;
    while (*(line = read_line()) != NLNCHR) {
        lineLen = strlen(line) - 1;
        map[lines] = line;
        lines++;

        while (lines >= maxLines) {
            maxLines *= 2;
            map = (char**)realloc(map, maxLines * sizeof(char*));
            assert(map);
        }
    }

    // Tilt all rocks 
    // Part 1
    // for (int round = 0; round < lines; round++) {
    //     for (int row = lines - 1; row >= 0; row--) {
    //         for (int col = 0; col < lineLen; col++) {
    //             if (row - 1 >= 0 && map[row][col] == ROCK && map[row - 1][col] == EMTY) {
    //                 map[row][col] = EMTY;
    //                 map[row - 1][col] = ROCK;
    //             }
    //         }
    //     }
    // }


    // Part 2
    // Cbs optimising
    // Cycle
    int bs = 10, n = 0;
    char ***allmaps = (char***)malloc(bs * sizeof(char**));
    assert(allmaps);

    for (int cycle = 0; cycle < 1000000000; cycle++) {
        char **oldmap = (char**)malloc(lines * sizeof(char*));
        assert(oldmap);
        for (int i = 0; i < lines; i++) {
            char *newline = (char*)malloc(lineLen * sizeof(char));
            memcpy(newline, map[i], lineLen * sizeof(char));
            oldmap[i] = newline;
        }

        allmaps[n] = oldmap;
        n++;
        if (n + 1 >= bs) {
            bs *= 2;
            allmaps = (char***)realloc(allmaps, bs * sizeof(char**));
            assert(allmaps);
        }

        // for (int i = 0; i < lines; i++) {
        //     printf("%s", map[i]);
        // }
        // printf("\n");
        

        // North
        for (int round = 0; round < lines; round++) {
            for (int row = lines - 1; row > 0; row--) {
                for (int col = 0; col < lineLen; col++) {
                    if (map[row][col] == ROCK && map[row - 1][col] == EMTY) {
                        map[row][col] = EMTY;
                        map[row - 1][col] = ROCK;
                    }
                }
            }
        }
        // West
        for (int round = 0; round < lineLen; round++) {
            for (int col = lineLen - 1; col > 0; col--) {
                for (int row = 0; row < lines; row++) {
                    if (map[row][col] == ROCK && map[row][col - 1] == EMTY) {
                        map[row][col] = EMTY;
                        map[row][col - 1] = ROCK;
                    }
                }
            }
        }
        // South
        for (int round = 0; round < lines; round++) {
            for (int row = 0; row < lines - 1; row++) {
                for (int col = 0; col < lineLen; col++) {
                    if (map[row][col] == ROCK && map[row + 1][col] == EMTY) {
                        map[row][col] = EMTY;
                        map[row + 1][col] = ROCK;
                    }
                }
            }
        }
        // East
        for (int round = 0; round < lineLen; round++) {
            for (int col = 0; col < lineLen - 1; col++) {
                for (int row = 0; row < lines; row++) {
                    if (map[row][col] == ROCK && map[row][col + 1] == EMTY) {
                        map[row][col] = EMTY;
                        map[row][col + 1] = ROCK;
                    }
                }
            }
        }

        


        for (int mapnum = 0; mapnum < n; mapnum++)
        {
            // for (int i = 0; i < lines; i++) {
            //     printf("%s\n", allmaps[mapnum][i]);
            // }
            // printf("\n");
            
            int isSame = 1;
            for (int i = 0; i < lines; i++) {
                for (int j = 0; j < lineLen; j++) {
                    if (allmaps[mapnum][i][j] != map[i][j]) {
                        isSame = 0;
                        break;
                    }
                }

                if (!isSame) {
                    break;
                }
            }

            if (isSame) {
                printf("Detected loop on mapnum: %d\n", mapnum + 1);
                printf("Found on cycle: %d\n", cycle + 1);
                breakall = 1;
                q = cycle;
                p = mapnum;
                break;
            }
        }

        if (breakall) {
            break;
        }
        // printf("\\--\\--\\--\\--\\--\\--\\--\\--\\--\\\n");
    }


    // Calc load
    for (int row = 0; row < lines; row++) {
        for (int col = 0; col < lineLen; col++) {
            if (allmaps[(999999999  - p + 1) % (q - p + 1) + p][row][col] == ROCK) {
                sum += lines - row;
            }
        }
    }
    
    
    for (int i = 0; i < lines; i++) {
        printf("%s", map[i]);
        free(map[i]);
    }

    
    
    free(map);
    

    printf("Sum: %d", sum);
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

