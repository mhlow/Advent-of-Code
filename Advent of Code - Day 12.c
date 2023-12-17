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

int check_valid(char *row, int rowLen, int *arngmts, int n);
int calc_all(char *row, int rowLen, int *arngmts, int n);

// Brute force cus I cbs lmao
int main(int argc, char *argv[]) {
    int sum = 0;
    char *line;
    while (*(line = read_line()) != NLNCHR) {
        int lineLen = strlen(line);
        // Split up into row and numbers 
        char *row;
        int i = 0, rowLen = 0;
        for (i = 0; i < lineLen; i++) {
            if (line[i] == ' ') {
                row = (char*)calloc((5 * i) + 1 + 5, sizeof(char));
                memcpy(row, line, (i) * sizeof(char));
                row[i] = '?';
                memcpy(row + i + 1, line, (i) * sizeof(char));
                row[2 * i + 1] = '?';
                memcpy(row + 2 * i + 2, line, (i) * sizeof(char));
                row[3 * i + 2] = '?';
                memcpy(row + 3 * i + 3, line, (i) * sizeof(char));
                row[4 * i + 3] = '?';
                memcpy(row + 4 * i + 4, line, (i) * sizeof(char));

                rowLen = strlen(row) + 1;
                printf("%s\n", row);
                // printf("%s ", row);
                break;
            }
        }

        int n = (lineLen - i) / 2, is0 = 0;
        // printf("%d\n", n);
        int *arngmts = (int*)malloc(5 * n * sizeof(int));
        n = 0;
        for (i = 0; i < lineLen; i++) {
            int num = parse_num(line + i, &is0);
            if (num != 0) {
                arngmts[n] = num;
                n++;
                i += floor(log10(num));
            }
        }

        memcpy(arngmts + n, arngmts, n * sizeof(int));
        memcpy(arngmts + 2 * n, arngmts, 2 * n * sizeof(int));
        memcpy(arngmts + 4 * n, arngmts, n * sizeof(int));
        n *= 5;
        print_int_arr(arngmts, n);
        // print_int_arr(arngmts, n);

        // Start
        // printf("%d\n", check_valid(row, rowLen, arngmts, n));
        sum += calc_all(row, rowLen, arngmts, n);
        // printf("Res: %d\n", calc_all(row, rowLen, arngmts, n));
        
        
        free(line); line = NULL;
    }


    free(line);
    printf("Sum: %d\n", sum);
    return 0;
}

int num_hash(char *row, int rowLen, int *arngmts, int n) {
    for (int i = 0; i < count; i++)
    {
        /* code */
    }
    
}

int calc_all(char *row, int rowLen, int *arngmts, int n) {
    int sum = 0;
    

    for (int i = 0; i < rowLen; i++)
    {
        if (row[i] == '?') {
            char *newstr = (char*)malloc(rowLen * sizeof(char));
            strncpy(newstr, row, rowLen);

            newstr[i] = '#';
            sum += calc_all(newstr, rowLen, arngmts, n);
            newstr[i] = '.';
            sum += calc_all(newstr, rowLen, arngmts, n);
            free(newstr);
            return sum;
        }
    }
    
    
    return check_valid(row, rowLen, arngmts, n);
}

int check_valid(char *row, int rowLen, int *arngmts, int n) {
    int run = 0, pp = 0;
    for (int i = 0; i < rowLen; i++)
    {
        if (row[i] == '#') {
            run++;
        } else {
            if (run > 0) {
                if (pp == n) {
                    return 0;
                }
                if (run == arngmts[pp]) {
                    pp++;
                } else {
                    return 0;
                }
            }
            run = 0;
        }
    }

    if (pp != n) {
        return 0;
    }

    return 1;
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
    int n = 0, lineLen = BSTRLN;
    char ch = getchar(), *line;
    line = (char*)malloc(lineLen * sizeof(char));
    assert(line);

    if (ch == EOF) {
        line[0] = '\n'; line[1] = '\0';
        return line;
    }

    while (1) {
        /* Make character array longer */
        if (n + 1 >= lineLen) {
            lineLen *= 2;
            line = realloc(line, lineLen * sizeof(char));
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

// Returns 1 if the array contains the element specified, up to n
char contains_char(char *arr, char elem, int n) {
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


