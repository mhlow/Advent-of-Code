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

void bubble_sort(char **input, int n);
void int_bubble_sort(char **input, int *strengths, int n);
void swapStrings(char **str1, char **str2);
void swapIntegers(int *a, int *b);
int is_str_larger(char *c1, char *c2);
int is_larger(char c1, char c2);
int findLargestPosition(int arr[], int size);

int main(int argc, char *argv[]) {
    char cards[] = {'A', 'K', 'Q', 'J', 'T', '9', '8', '7', '6', '5', '4', '3', '2'};
    int mlines = 20, n = 0;
    char **input = (char**)malloc(mlines * sizeof(char*));
    assert(input);

    char *line;
    while (*(line = read_line()) != NLNCHR) {
        input[n] = line;

        n++;
        if (n + 1 >= mlines) {
            mlines *= 2;
            input = realloc(input, mlines * sizeof(char*));
            assert(input);
        }
    }

    for (int i = 0; i < n; i++) {
        printf("%s", input[i]);
    }
    printf("\n\n");

    bubble_sort(input, n);
    printf("After first merge sort: \n");
    for (int i = 0; i < n; i++) {
        printf("%s", input[i]);
    }
    printf("\n\n");

    int *strength = (int*)calloc(n, sizeof(int));
    for (int i = 0; i < n; i++) {
        int score[13] = {0};
        for (int j = 0; j < 5; j++) {
            for (int k = 0; k < 13; k++) {
                if (input[i][j] == cards[k]) {
                    score[k]++;
                    break;
                }
            }
        }
        // Part 1
        // if (contains(score, 5, 13)) {
        //     strength[i] = 6;
        // } else if (contains(score, 4, 13)) {
        //     strength[i] = 5;
        // } else if (contains(score, 3, 13)) {
        //     if (contains(score, 2, 13)) {
        //         strength[i] = 4;
        //     } else {
        //         strength[i] = 3;
        //     }
        // } else if (contains(score, 2, 13)) {
        //     for (int p = 0; p < 13; p++) {
        //         if (score[p] == 2) {
        //             score[p] = -2;
        //             break;
        //         }
        //     }

        //     if (contains(score, 2, 13)) {
        //         strength[i] = 2;
        //     } else {
        //         strength[i] = 1;
        //     }
            
        // }

        // Part 2
        // if (contains(score, 5, 13)) {
        //     // 5
        //     strength[i] = 6;
        // } else if (contains(score, 4, 13)) {
        //     // 4
        //     strength[i] = 5;
        //     if (score[3] == 1) {
        //         strength[i] = 6;
        //     }
        // } else if (contains(score, 3, 13)) {
        //     // 3
        //     if (contains(score, 2, 13)) {
        //         strength[i] = 4;
        //     } else {
        //         strength[i] = 3;
        //     }

        //     if (score[3] == 1) {
        //         strength[i] = 5;
        //     } else if (score[3] == 2) {
        //         strength[i] = 6;
        //     } else if (score[3] == 3) {
        //         if (contains(score, 2, 13)) {
        //             strength[i] = 6;
        //         } else {
        //             strength[i] = 5;
        //         }
        //     }
        // } else if (contains(score, 2, 13)) {
        //     // 2
        //     for (int p = 0; p < 13; p++) {
        //         if (score[p] == 2) {
        //             score[p] = -2;
        //             break;
        //         }
        //     }

        //     if (contains(score, 2, 13)) {
        //         strength[i] = 2;
        //         if (score[3] == 1) {
        //             strength[i] = 4;
        //         } else if (score[3] == 2 || score[3] == -2) {
        //             strength[i] = 5;
        //         }
        //     } else {
        //         strength[i] = 1;
        //         if (score[3] == 1) {
        //             strength[i] = 3;
        //         } else if (score[3] == 2 || score[3] == -2) {
        //             strength[i] = 3;
        //         }
        //     }
        // } else if (score[3] == 1) {
        //     strength[i] = 1;
        // }

        // Attempt 2
        int pos = findLargestPosition(score, 13);
        score[pos] += score[3];
        score[3] = 0;

        if (contains(score, 5, 13)) {
            strength[i] = 6;
        } else if (contains(score, 4, 13)) {
            strength[i] = 5;
        } else if (contains(score, 3, 13)) {
            if (contains(score, 2, 13)) {
                strength[i] = 4;
            } else {
                strength[i] = 3;
            }
        } else if (contains(score, 2, 13)) {
            for (int p = 0; p < 13; p++) {
                if (score[p] == 2) {
                    score[p] = -2;
                    break;
                }
            }

            if (contains(score, 2, 13)) {
                strength[i] = 2;
            } else {
                strength[i] = 1;
            }
            
        }
    }

    printf("Strength: [");
    for (int i = 0; i < n; i++) {
        printf("%d,", strength[i]);
    }
    printf("]\n");

    int_bubble_sort(input, strength, n);
    printf("After everything: \n");
    for (int i = 0; i < n; i++) {
        printf("%s", input[i]);
    }
    printf("\n\n");

    int winnings = 0;
    for (int i = 0; i < n; i++) {
        winnings += (i + 1) * parse_num(input[i] + 6);
    }
    printf("Winnings: %d\n", winnings);

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

void swapStrings(char **str1, char **str2) {
    char *temp = *str1;
    *str1 = *str2;
    *str2 = temp;
}

// Function to swap two integers
void swapIntegers(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Function to perform stable bubble sort on an array of pairs
void bubble_sort(char **input, int n) {
    int i, j;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            // Compare integers for sorting
            if (is_str_larger(input[j], input[j + 1]) == 1) {
                // Swap pairs
                swapStrings(&input[j], &input[j + 1]);
            }
        }
    }
}


// Function to perform stable bubble sort on an array of pairs
void int_bubble_sort(char **input, int *strengths, int n) {
    int i, j;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            // Compare integers for sorting
            if (strengths[j] > strengths[j + 1]) {
                // Swap pairs
                swapIntegers(&strengths[j], &strengths[j + 1]);
                swapStrings(&input[j], &input[j + 1]);
            }
        }
    }
}

int is_str_larger(char *c1, char *c2) {
    for (int i = 0; i < 5; i++) {
        if (is_larger(c1[i], c2[i]) == -2) {
            return -2;
        }

        if (is_larger(c1[i], c2[i]) == 1) {
            return 1;
        }

        if (is_larger(c1[i], c2[i]) == -1) {
            return -1;
        }
    }
    return 0;
}

int is_larger(char c1, char c2) {
    if (c1 == c2) {
        return 0;
    }
    // char cards[] = {'A', 'K', 'Q', 'J', 'T', '9', '8', '7', '6', '5', '4', '3', '2'};
    char cards[] = {'A', 'K', 'Q', 'T', '9', '8', '7', '6', '5', '4', '3', '2', 'J'};
    int len = sizeof(cards)/sizeof(*cards);
    for (int i = 0; i < len; i++) {
        if (c1 == cards[i]) {
            return 1;
        }
        if (c2 == cards[i]) {
            return -1;
        }
    }
    return -2;
}

int findLargestPosition(int arr[], int size) {
    if (size <= 0) {
        // Handle the case of an empty array or invalid size
        return -1;
    }

    int maxPosition = 0;  // Assume the first element is the largest

    for (int i = 1; i < size; i++) {
        if (i == 3) {
            continue;
        }
        // Compare with the current maximum element
        if (arr[i] > arr[maxPosition]) {
            maxPosition = i;  // Update the position of the largest element
        }
    }

    return maxPosition;
}

