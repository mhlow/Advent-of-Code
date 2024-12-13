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

void findS(char **maze, int height, int width, int *x, int *y);
void next_pipe(char **maze, int height, int width, int *x, int *y, int *lastx, int *lasty);

int main(int argc, char *argv[]) {
    int maxLines = 10, lines = 0, lineLen = 0;
    char **maze = (char**)malloc(maxLines * sizeof(char*));
    assert(maze);

    char *line;
    while (*(line = read_line()) != NLNCHR) {
        lineLen = strlen(line);
        maze[lines] = line;
        lines++;

        while (lines >= maxLines) {
            maxLines *= 2;
            maze = (char**)realloc(maze, maxLines * sizeof(char*));
            assert(maze);
        }
        
    }
    
    int startX, startY;
    findS(maze, lines, lineLen, &startX, &startY);
    printf("Start is at (%d, %d)\n", startX, startY);

    int area = 0;
    int x = startX, y = startY + 1, lastx = startX, lasty = startY, steps = 1;
    while (maze[y][x] != 'S') {
        next_pipe(maze, lines, lineLen, &x, &y, &lastx, &lasty);
        maze[lasty][lastx] = 254;

        // area += (lastx * y - x * lasty);
        area += (y + lasty) * (lastx - x);
        steps++;
    }

    area = abs(area) / 2;
    int inside = 1 - (steps / 2) + area;
    printf("Inside has %d tiles\n", inside);

    printf("Steps for whole loop: %d\n", steps);

    for (int i = 0; i < lines; i++) {
        printf("%s", maze[i]);
        free(maze[i]);
    }
    free(maze);
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

void findS(char **maze, int height, int width, int *x, int *y) {
    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            if (maze[row][col] == 'S') {
                *x = col;
                *y = row;
                break;
            }
        }
    }
}

void next_pipe(char **maze, int height, int width, int *x, int *y, int *lastx, int *lasty) {
    switch (2 * (*lastx - *x) + 1 * (*lasty - *y))
    {
    case 1: // From bottom
        *lasty = *y;
        switch (maze[*y][*x])
        {
        case '7':
            (*x)--;
            break;
        case 'F':
            (*x)++;
            break;
        case '|':
            (*y)--;
            break;

        default:
            printf("BIG ERROR MY BOY\n");
            break;
        }
        break;

    case -1: // From top
        *lasty = *y;
        switch (maze[*y][*x])
        {
        case 'J':
            (*x)--;
            break;
        case 'L':
            (*x)++;
            break;
        case '|':
            (*y)++;
            break;

        default:
            printf("BIG ERROR MY BOY\n");
            break;
        }
        break;

    case 2: // From right
        *lastx = *x;
        switch (maze[*y][*x])
        {
        case 'L':
            (*y)--;
            break;
        case 'F':
            (*y)++;
            break;
        case '-':
            (*x)--;
            break;

        default:
            printf("BIG ERROR MY BOY\n");
            break;
        }
        break;

    case -2: // From left
        *lastx = *x;
        switch (maze[*y][*x])
        {
        case '7':
            (*y)++;
            break;
        case 'J':
            (*y)--;
            break;
        case '-':
            (*x)++;
            break;

        default:
            printf("BIG ERROR MY BOY\n");
            break;
        }
        break;

    default:
        printf("ANOTHER ERROR MY BOY\n");
        break;
    }


    // switch (maze[*y][*x])
    // {
    // case '7':
    //     /* code */
    //     break;
    // case 'J':
    //     /* code */
    //     break;
    // case 'L':
    //     /* code */
    //     break;
    // case 'F':
    //     /* code */
    //     break;
    // case '|':
    //     /* code */
    //     break;
    // case '-':
    //     /* code */
    //     break;
    // case 'S':

    //     break;

    // default:
    //     printf("BIG ERROR MY BOY\n");
    //     break;
    // }

}
