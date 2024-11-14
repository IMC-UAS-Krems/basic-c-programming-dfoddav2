#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <errno.h>

int main(int argc, char *argv[])
{
    // initialize random number generator
    srand(time(NULL));
    int minrand = 1;
    int maxrand = 100;

    // WRITE YOUR CODE HERE

    // --- TASK 1 ---
    // As far as I read, `argc` is the number of arguments passed to the program
    // BUT it does include the program name itself, so we need +1 to the condition
    if (argc != 3)
    {
        printf("Incorrect usage. You provided %d arguments. The correct number of arguments is 2\n", argc - 1); // argc - 1 to exclude the program name
        exit(1);
    }

    // --- TASK 2 ---
    for (int i = 1; i < argc; i++) // For the same reason as before, we start at 1 to exclude the program name
    {
        // int value = atoi(argv[i]); - Kept this here, to show my original approach was using `atoi`
        // BUT I first tried printing the values immediately after converting them and got Segmentation fault
        // - So I tried searching for a solution that handled errors better and found `strtol`

        char *endptr;
        errno = 0;
        long value = strtol(argv[i], &endptr, 10); // strtol converts string to long: long int strtol(const char *str, char **endptr, int base);
        // The logic here is that we initiate an `endptr`, which then gets filled with the first character that is not converted
        // If the endptr is not the null character, then the string is not a number, additionally, if we encounter any other errors we can check `errno`

        // We could for example handle too small or too large numbers
        if (errno == ERANGE)
        {
            printf("The number you provided is out of range\n");
            exit(2);
        }

        if (*endptr != '\0' || value <= 0)
        {
            printf("Incorrect usage. The parameters you provided are not positive integers\n");
            exit(2);
        }
    }

    // --- TASK 3 ---
    // We haven't captured the variables before, so we need to do it now
    // - But now we are sure that they are positive integers anyway
    int nrows = strtol(argv[1], NULL, 10);
    int ncols = strtol(argv[2], NULL, 10);
    int matrix[nrows][ncols];

    for (int i = 0; i < nrows; i++)
    {
        for (int j = 0; j < ncols; j++)
        {
            matrix[i][j] = rand() % (maxrand - minrand + 1) + minrand;
        }
    }

    // --- TASK 4 ---
    FILE *fptr;

    fptr = fopen("matrix.txt", "w");
    for (int i = 0; i < nrows; i++)
    {
        for (int j = 0; j < ncols; j++)
        {
            if (j == ncols - 1)
            {
                fprintf(fptr, "%d", matrix[i][j]); // No whitespace at the end of the line
            }
            else
            {
                fprintf(fptr, "%d ", matrix[i][j]); // "%d " has the space at the end
            }
        }
        if (i == nrows - 1)
        {
            fprintf(fptr, "\r"); // Carriage return at the end of the last row
        }
        else
        {
            fprintf(fptr, "\n"); // Newline at the end of other rows
        }
    }
    fclose(fptr);

    return 0;
}
