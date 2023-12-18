// #include <stdio.h>
// #include <stdlib.h>
// #include <assert.h>
// #include <string.h>
// #include <math.h>

// #define NLNCHR '\n'
// #define BSTRLN 20
// #define ZERO  "zero"
// #define ONE   "one"
// #define TWO   "two"
// #define THREE "three"
// #define FOUR  "four"
// #define FIVE  "five"
// #define SIX   "six"
// #define SEVEN "seven"
// #define EIGHT "eight"
// #define NINE  "nine"

// int is_digit(int c);
// int to_digit(int c);
// int parse_num(char *str, int *is0);
// char *read_line(void);
// int contains(int *arr, int elem, int n);
// int sum(int arr[], int n);
// void print_int_arr(int *arr, int n);

// int check_valid(char *row, int rowLen, int *arngmts, int n);
// int calc_all(char *row, int rowLen, int *arngmts, int n);
// int num_hash(char *row, int rowLen);

// // Brute force cus I cbs lmao
// // Part two is too hard for my puny brain heres a solution from moshepiekarski
// int main(int argc, char *argv[]) {
//     int sum = 0;
//     char *line;
//     while (*(line = read_line()) != NLNCHR) {
//         int lineLen = strlen(line);
//         // Split up into row and numbers 
//         char *row;
//         int i = 0, rowLen = 0;
//         for (i = 0; i < lineLen; i++) {
//             if (line[i] == ' ') {
//                 row = (char*)calloc((5 * i) + 1 + 5, sizeof(char));
//                 memcpy(row, line, (i) * sizeof(char));
//                 row[i] = '?';
//                 memcpy(row + i + 1, line, (i) * sizeof(char));
//                 row[2 * i + 1] = '?';
//                 memcpy(row + 2 * i + 2, line, (i) * sizeof(char));
//                 row[3 * i + 2] = '?';
//                 memcpy(row + 3 * i + 3, line, (i) * sizeof(char));
//                 row[4 * i + 3] = '?';
//                 memcpy(row + 4 * i + 4, line, (i) * sizeof(char));

//                 rowLen = strlen(row) + 1;
//                 printf("%s", row);
//                 // printf("%s ", row);
//                 break;
//             }
//         }

//         int n = (lineLen - i) / 2, is0 = 0;
//         // printf("%d\n", n);
//         int *arngmts = (int*)malloc(5 * n * sizeof(int));
//         n = 0;
//         for (i = 0; i < lineLen; i++) {
//             int num = parse_num(line + i, &is0);
//             if (num != 0) {
//                 arngmts[n] = num;
//                 n++;
//                 i += floor(log10(num));
//             }
//         }

//         memcpy(arngmts + n, arngmts, n * sizeof(int));
//         memcpy(arngmts + 2 * n, arngmts, 2 * n * sizeof(int));
//         memcpy(arngmts + 4 * n, arngmts, n * sizeof(int));
//         n *= 5;

//         printf(" ");
//         for (int i = 0; i < n; i++) {
//             if (i != 0) {
//                 printf(",");
//             }
//             printf("%d", arngmts[i]);
//         }

//         printf("\n");
//         // print_int_arr(arngmts, n);
//         // print_int_arr(arngmts, n);

//         // Start
//         // printf("%d\n", check_valid(row, rowLen, arngmts, n));
//         // sum += calc_all(row, rowLen, arngmts, n);
//         // printf("Res: %d\n", calc_all(row, rowLen, arngmts, n));
        
        
//         free(line); line = NULL;
//     }


//     free(line);
//     printf("Sum: %d\n", sum);
//     return 0;
// }

// int num_hash(char *row, int rowLen) {
//     int sum = 0;
//     for (int i = 0; i < rowLen; i++)
//     {
//         if (row[i] == '#') {
//             sum++;
//         }
//     }
//     return sum;
// }

// int calc_all(char *row, int rowLen, int *arngmts, int n) {
//     int rsum = 0;

//     int i = 0;
//     for (int j = 0; j < n; j++) {
//         int run = 0;
//         for (; i < rowLen; i++) {
//             if (run > arngmts[j]) {
//                 return 0;
//             }
//             if (row[i] == '?') {
//                 break;
//             } else if (row[i] == '#') {
//                 run++;
//                 continue;
//             } else if (row[i] == '.' && run > 0) {
//                 break;
//             }
//         }
//     }
    

//     for (int i = 0; i < rowLen; i++)
//     {
//         if (row[i] == '?') {
//             char *newstr = (char*)malloc(rowLen * sizeof(char));
//             strncpy(newstr, row, rowLen);

//             newstr[i] = '#';
//             if (num_hash(row, rowLen) > sum(arngmts, n)) {
//                 printf("|");
//                 return 0;
//             }
//             rsum += calc_all(newstr, rowLen, arngmts, n);
//             newstr[i] = '.';
//             rsum += calc_all(newstr, rowLen, arngmts, n);
//             free(newstr);
//             return rsum;
//         }
//     }
    
    
//     return check_valid(row, rowLen, arngmts, n);
// }

// int check_valid(char *row, int rowLen, int *arngmts, int n) {
//     int run = 0, pp = 0;
//     for (int i = 0; i < rowLen; i++)
//     {
//         if (row[i] == '#') {
//             run++;
//         } else {
//             if (run > 0) {
//                 if (pp == n) {
//                     return 0;
//                 }
//                 if (run == arngmts[pp]) {
//                     pp++;
//                 } else {
//                     return 0;
//                 }
//             }
//             run = 0;
//         }
//     }

//     if (pp != n) {
//         return 0;
//     }

//     return 1;
// }

// // Returns 1 if a character is a digit
// int is_digit(int c) {
//     return ((c = c - '0') >= 0) && (c < 10);
// }

// // Returns a integer digit given a character digit
// int to_digit(int c) {
//     return c - '0';
// }

// // Turns string of numbers into an integer, 
// // stopping at the first non digit it encounters
// // Now accepts negative numbers
// int parse_num(char *str, int *is0) {
//     int isNegative = -1;
//     int i = 0, ret = 0;
//     if (str[0] == '-') {
//         isNegative = 1;
//         i++;
//     }

//     if (str[0] == '0') {
//         *is0 = 1;
//     }
    
//     while (is_digit(str[i])) {
//         ret *= 10;
//         ret += (isNegative * -1) * to_digit(str[i]);
//         i++;
//     }

//     return ret;
// }

// // Reads one input line, including the newline character
// char *read_line(void) {
//     int n = 0, lineLen = BSTRLN;
//     char ch = getchar(), *line;
//     line = (char*)malloc(lineLen * sizeof(char));
//     assert(line);

//     if (ch == EOF) {
//         line[0] = '\n'; line[1] = '\0';
//         return line;
//     }

//     while (1) {
//         /* Make character array longer */
//         if (n + 1 >= lineLen) {
//             lineLen *= 2;
//             line = realloc(line, lineLen * sizeof(char));
//             assert(line);
//         }
//         line[n++] = ch;
//         /* Break at a newline or EOF character */
//         if (ch == NLNCHR || ch == EOF) {
//             break;
//         }

//         ch = getchar();
//     }
//     line[n] = '\0';
//     return line;
// }


// // Returns 1 if the array contains the element specified, up to n
// int contains(int *arr, int elem, int n) {
//     for (int i = 0; i < n; i++) {
//         if (arr[i] == elem) {
//             return 1;
//         }
//     }
//     return 0;
// }

// // Returns 1 if the array contains the element specified, up to n
// char contains_char(char *arr, char elem, int n) {
//     for (int i = 0; i < n; i++) {
//         if (arr[i] == elem) {
//             return 1;
//         }
//     }
//     return 0;
// }

// // Returns the sum of the list, within integer overflow bounds
// int sum(int arr[], int n) {
//     int sum = 0;
//     for (int i = 0; i < n; i++) {
//         sum += arr[i];
//     }
//     return sum;
// }

// // Prints an integer array
// void print_int_arr(int *arr, int n) {
//     printf("[");
//         for (int i = 0; i < n; i++) {
//             printf("%d, ", arr[i]);
//         }
//     printf("]\n");
// }



#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char memo[5500][2][210]={0};
long memr[5500]={0};
int k=0;
long long arrange(char *springs, char *targets, char target);

int main (int argc, char * argv[])
{
    char *filename = "C:/Users/User/Documents/Google Drive Sync/GitHub/Advent-of-Code-2023/input.txt";
    long result=0;
    int part=1;
    char buf[40], targets[210], springs[210],*bufp, *ebufp;
    int i;
    FILE * fp;
    if(argc > 1)
        part=atoi(argv[1]);
    if(argc > 2)
        filename=argv[2];
    if((fp = fopen(filename, "r"))==NULL)
    {
        printf("error opening file %s\n", filename);
        return 1;
    }
    while(fgets(buf, 40, fp) != NULL)
    {
        i=0;
        memset(springs,0,210);
        memset(targets,0,210);
        //TODO This shouldn't be needed
        memset(memo,0,sizeof(memo));
        memset(memr,0,sizeof(memr));
        bufp=strtok(buf," ");
        ebufp=strcpy(springs,bufp);
        if(part==2)
            for(int j=0;j<4;j++)
            {
                *(ebufp++)='?';
                ebufp=strcpy(ebufp,bufp);
            }
        bufp=strtok(NULL,"\n");
        do
        {
            targets[i++]=strtol(bufp,&bufp,10);
            bufp++;
        }while(targets[i-1]);
        i--;
        if(part==2){
            for(int j=0;j<5;j++){
                memcpy(targets+(i*j),targets,i);
            }
        }
        result += arrange(springs,targets,targets[0]);
    }
    printf("%ld\n",result);
    return 0;
}

long long arrange(char *springs, char *targets, char target)
{
    long long i=0, j, result=0,out;
    for(j=0;memo[j][0][0]&&j<5000;j++)
    {
        if(!memcmp(springs,memo[j][0], 210) && !memcmp(targets,memo[j][1], 210)){
            return memr[j];
        }
    }
    for(int x=0;x<210;x++) {
        switch(springs[x])
        {
        case'#':
            if(--targets[i]<0){
                return 0;
            }
            break;
        case'.':
            if(targets[i]==0)
            {
                i++;
                target=targets[i];
            }
            else if(targets[i]==target) {
                continue;
            }
            else {
                return 0;
            }
            break;
        case '?':;
            char *newt=(char*)calloc(210,1);
            char *news=(char*)calloc(210,1);
            memcpy(news,springs+x,210-x);
                news[0]='#';
                memcpy(newt,targets+i,210-i);
                result+=arrange(news,newt,target);
                k%=5000;
                    memr[k]=result;
                    memcpy(memo[k][0],news,210);
                    memo[k][0][0]='#';
                    memcpy(memo[k++][1],targets+i,210-i);
                news[0]='.';
                memcpy(newt,targets+i,210-i);
                out=arrange(news,newt,target);
                k%=5000;
                    memr[k]=out;
                    memcpy(memo[k][0],news, 210);
                    memo[k][0][0]='.';
                    memcpy(memo[k++][1],targets+i,210-i);
            free(newt);
            free(news);
            return out+result;
        default:
            if((targets[i]|targets[i+1])==0)
                return 1;
            return 0;
        }
    }
    return 0;
}