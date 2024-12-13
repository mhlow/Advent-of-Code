#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <math.h>
#include <gmp.h> 

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

int *find_empty_rows(char **map, int lines, int lineLen, int *numEmptyRows);
int *find_empty_cols(char **map, int lines, int lineLen, int *numEmptyCols);


typedef struct {
    int x, y;
} tile_t;

tile_t *find_gals(char **map, int lines, int lineLen, int *numGals);

int main(int argc, char *argv[]) {
    int maxLines = 10, lines = 0, lineLen = 0;
    mpz_t sum;
    mpz_init(sum);
    mpz_set_ui(sum, 0);
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
    
    int numEmptyRows, numEmptyCols;
    int *emptyRows = find_empty_rows(map, lines, lineLen, &numEmptyRows);
    int *emptyCols = find_empty_cols(map, lines, lineLen, &numEmptyCols);
    print_int_arr(emptyRows, numEmptyRows);
    print_int_arr(emptyCols, numEmptyCols);

    int numGals = 0;
    tile_t *gals = find_gals(map, lines, lineLen, &numGals);
    printf("%d|", numGals);
    for (int i = 0; i < numGals; i++)
    {
        printf("(%d, %d)", gals[i].x, gals[i].y);
    }
    printf("\n");

    for (int i = 0; i < numGals - 1; i++)
    {
        for (int j = i + 1; j < numGals; j++)
        {
            // Calc distance
            // Just add distance if empty row in between
            int dist = 0;
            for (int row = 0; row < numEmptyRows; row++) {
                if ((gals[i].y < emptyRows[row] && gals[j].y > emptyRows[row]) || (gals[j].y < emptyRows[row] && gals[i].y > emptyRows[row])) {
                    dist += 999999;
                }
            }

            for (int col = 0; col < numEmptyCols; col++) {
                if ((gals[i].x < emptyCols[col] && gals[j].x > emptyCols[col]) || (gals[j].x < emptyCols[col] && gals[i].x > emptyCols[col])) {
                    dist += 999999;
                }
            }

            dist += abs(gals[i].x - gals[j].x) + abs(gals[i].y - gals[j].y);
            
            // printf("Dist: %d\n", dist);
            mpz_add_ui(sum, sum, dist);
            // if (sum < 0) {
            //     sum += pow(2, 32);
            //     printf("sd\n");
            // }
            
            mpz_out_str(stdout, 10, sum);
        }
    }
    
    printf("Sum: ");
    mpz_out_str(stdout, 10, sum);
    

    

    for (int i = 0; i < lines; i++) {
        // printf("%s", map[i]);
        free(map[i]);
    }
    free(map);
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


int *find_empty_rows(char **map, int lines, int lineLen, int *numEmptyRows) {
    int *empty = (int*)malloc(lines * sizeof(int)), n = 0;
    for (int i = 0; i < lines; i++) {
        int isEmpty = 1;
        // Check if all are '.'
        for (int j = 0; j < lineLen; j++) {
            if (map[i][j] != '.') {
                isEmpty = 0;
                break;
            }
        }

        if (!isEmpty) {
            continue;
        }

        empty[n] = i;
        n++;
    }
    *numEmptyRows = n;
    return empty;
}

int *find_empty_cols(char **map, int lines, int lineLen, int *numEmptyCols) {
    int *empty = (int*)malloc(lineLen * sizeof(int)), n = 0;
    for (int i = 0; i < lineLen; i++) {
        int isEmpty = 1;
        // Check if all are '.'
        for (int j = 0; j < lines; j++) {
            if (map[j][i] != '.') {
                isEmpty = 0;
                break;
            }
        }

        if (!isEmpty) {
            continue;
        }

        empty[n] = i;
        n++;
    }
    *numEmptyCols = n;
    return empty;
}

tile_t *find_gals(char **map, int lines, int lineLen, int *numGals) {
    int galsMaxSize = 10, n = 0;
    tile_t *gals = (tile_t*)malloc(galsMaxSize * sizeof(tile_t));
    assert(gals);
    for (int i = 0; i < lines; i++)
    {
        for (int j = 0; j < lineLen; j++)
        {
            if (map[i][j] == '#') {
                tile_t newGal = {x: j, y:i};
                gals[n] = newGal;
                n++;

                if (n + 1 >= galsMaxSize) {
                    galsMaxSize *= 2;
                    gals = (tile_t*)realloc(gals, galsMaxSize * sizeof(tile_t));
                    assert(gals);
                }

            }
        }
        
    }
    
    *numGals = n;
    return gals;
}