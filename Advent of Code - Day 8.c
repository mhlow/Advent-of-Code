// Part two of this task requires assumptions about how the map is generatred,
// namely that each loop will contain only one unique Z, and that the length 
// of the loop is exactly how far away the first Z is.
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

#define LEFT 'L'
#define RIGHT 'R'

int is_digit(int c);
int to_digit(int c);
int parse_num(char *str);
char *read_line(void);
int contains(int *arr, int elem, int n);
int sum(int arr[], int n);

int to_num(char *str);

typedef struct node node_t;

struct node {
    int id;
    node_t *left;
    node_t *right;
};

int main(int argc, char *argv[]) {
    char *instrns = read_line();
    int instrnsLen = strlen(instrns) - 1;
    assert(*read_line() == NLNCHR);

    int nodesLen = 20, isFirst = 1;
    node_t nodes[17576];
    assert(nodes);

    int numStart = 10, m = 0;
    node_t *starts = (node_t*)malloc(numStart * sizeof(node_t));
    assert(starts);
    

    char *line;
    while (*(line = read_line())!= NLNCHR) {
        int num = to_num(line);
        nodes[num].id = num;
        nodes[num].left = nodes + to_num(line + 7);
        nodes[num].right = nodes + to_num(line + 12);
        // printf("Num: %d, Left: %d, Right: %d\n", num, to_num(line + 7), to_num(line + 12));
        if (line[2] == 'A') {
            starts[m] = nodes[num];
            m++;
            if (m + 1 >= numStart) {
                numStart *= 2;
                starts = (node_t*)realloc(starts, numStart * sizeof(node_t));
                assert(starts);
                printf("Allocated more memory\n");
            }
        }
        free(line); line = NULL;
    }
    free(line);
    // int steps = 0;
    // node_t *curr = &nodes[0];
    // while (curr->id != 17575) {
    //     printf("%5d, %d, %c, %c%c%c\n", curr->id, steps % instrnsLen, instrns[steps % instrnsLen], curr->id / (int) pow(26, 2) + 'A', (curr->id % (int) pow(26, 2)) / 26 + 'A', curr->id % 26 + 'A');
    //     if (instrns[steps % instrnsLen] == LEFT) {
    //         curr = curr->left;
    //     } else if (instrns[steps % instrnsLen] == RIGHT) {
    //         curr = curr->right;
    //     } else {
    //         printf("---------------------------------------Error\n");
    //     }
    //     steps++;
    // }

    int steps = 0;
    int loops[6] = {0};
    while (1) {
        // Check for Z
        for (int i = 0; i < m; i++) {
            if (starts[i].id % 26 == 25 && loops[i] == 0) {
                loops[i] = steps;
            }
        }

        if (!contains(loops, 0, m)) {
            
            printf("[");
                for (int i = 0; i < m; i++) {
                    printf("%d, ", loops[i]);
                }
            printf("]\n");

            break;
        }

        printf("[");
        for (int i = 0; i < m; i++) {
            printf("%c%c%c, ", (starts + i)->id / (int) pow(26, 2) + 'A', ((starts + i)->id % (int) pow(26, 2)) / 26 + 'A', (starts + i)->id % 26 + 'A');
        }
        printf("]\n");

        // printf("%5d, %d, %c, %c%c%c\n", (starts + 1)->id, steps % instrnsLen, instrns[steps % instrnsLen], (starts + 1)->id / (int) pow(26, 2) + 'A', ((starts + 1)->id % (int) pow(26, 2)) / 26 + 'A', (starts + 1)->id % 26 + 'A');
        // Let each follow
        if (instrns[steps % instrnsLen] == LEFT) {
            for (int i = 0; i < m; i++) {
                starts[i] = *(starts[i].left);
            }
        } else if (instrns[steps % instrnsLen] == RIGHT) {
            for (int i = 0; i < m; i++) {
                starts[i] = *(starts[i].right);
            }
        } else {
            printf("---------------------------------------Error\n");
        }

        steps++;
    }


    printf("Steps = %d", steps);
    free(starts);
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

// Takes a character pointer to 3 characters and converts them to 
// base 10 as if it were a base 26 number
int to_num(char *str) {
    int sum = 0;
    for (int i = 0; i < 3; i++) {
        sum *= 26;
        sum += str[i] - 'A';
    }
    return sum;
}


