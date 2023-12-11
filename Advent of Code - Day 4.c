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

#define PARTTWO 1

int is_digit(int c);
int to_digit(int c);
int parse_num(char *str);
char *read_line(void);
int contains(int *arr, int elem, int n);
int sum(int arr[], int n);

void part_two(int pointsarr[], int cardsarr[], int n);

int main(int argc, char *argv[]) {
    int sum = 0, pointsarr[200] = {0}, cardsarr[200] = {0};
    char *line;
    while (*(line = read_line()) != NLNCHR) {
        int linelen = strlen(line), winning[10] = {0};
        
        int i = 0, cardnum = 0, points = 0;
        char c = line[i];
        // Winning numbers
        while (c != '|') {
            int num;
            num = parse_num(line + i);
            if (num != 0) {
                if (cardnum != 0) {
                    for (int j = 0; j < 10; j++) {
                        if (winning[j] == 0) {
                            winning[j] = num;
                            i += floor(log10(num));
                            break;
                        }
                    }
                } else {
                    cardnum = num;
                    i += floor(log10(num));
                }
                
            }
            
            i++;
            c = line[i];
        }

        // Pulled
        while (i < linelen) {
            int num;
            num = parse_num(line + i);
            if (num != 0) {
                if (contains(winning, num, 10)) {
                    points++;
                }
                i += floor(log10(num));
            }
            i++;
        }

        if (points > 0) {
            pointsarr[cardnum - 1] = points;
            sum += (int) pow(2, points - 1);
        }
        printf("Out: %d\n", (int) pow(2, points - 1));
        free(line);
        line = NULL;
    }

    printf("Sum: %d\n", sum);
    free(line);

    
    part_two(pointsarr, cardsarr, 187);
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

// Part two of problem
void part_two(int pointsarr[], int cardsarr[], int n) {
    // Fill cards with 1s
    for (int i = 0; i < n; i++) {
        cardsarr[i] = 1;
    }

    // Calculate cards
    for (int i = 0; i < n; i++) {

        for (int j = 0; j < pointsarr[i]; j++) {
            cardsarr[j + i + 1] += cardsarr[i];
        }
        // printf("%d,%d,%d,%d,%d,%d\n", cardsarr[0], cardsarr[1], cardsarr[2], cardsarr[3], cardsarr[4], cardsarr[5], cardsarr[6]);
    }

    printf("Total cards: %d", sum(cardsarr, n));
}
