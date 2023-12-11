#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

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
char *read_line(void);

int main(int argc, char *argv[]) {
    int sum = 0;
    

    char *numwrds[] = {ZERO, ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE};
    int numlen[] = {4,3,3,5,4,4,3,5,5,4};
    char *line;

    while (*(line = read_line()) != NLNCHR) {
        int linelen = strlen(line);
        int first = -1, last = -1;

        for (int i = 0; i < linelen; i++) {
            if (is_digit(*(line + i))) {
                // Digit
                if (first == -1) {
                    first = *(line + i) - '0';
                }
                last = *(line + i) - '0';
            }

            // Check each word
            for (int j = 0; j < 10; j++) {
                if (strncmp(line + i, numwrds[j], numlen[j]) == 0) {
                    if (first == -1) {
                        first = j;
                    }
                    last = j;
                    printf("----------------------\n");
                    break;
                }
            }
            
        }

        // Add to sum
        if (first != -1) {
            sum += first * 10 + last;
            printf("%d, %d,, %d\n", first, last, sum);
        }
        
        free(line);
        line = NULL;
    }
    free(line);
    return 0;
}

// Returns 1 if a character is a digit
int is_digit(int c) {
    return ((c = c - '0') >= 0) && (c < 10);
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