#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lsm/lsm.h"

#define MAX_ANSWER_SIZE 256

void ClearInputBuffer ()
{
    while (getchar() != '\n') {;}
}

int main ()
{
    int res = 0;
    char *answ   = calloc (MAX_ANSWER_SIZE, sizeof(char));
    char *input  = calloc (MAX_ANSWER_SIZE, sizeof(char));
    char *output = calloc (MAX_ANSWER_SIZE, sizeof(char));
    printf ("What approximation do you want to use?\n");
    while (res != 1)
    {
        printf ("Please, Answer \'l\' - linear, \'e\' - exponential or \'p\' - polinomial\n");
        scanf ("%s", answ);
        if (strcmp (answ, "l") == 0)
        {
            printf ("Enter input file name: ");
            scanf ("%s", input);
            printf ("Enter output file name: ");
            scanf ("%s", output);
            LinearLsmCalc (input, output);
            res = 1;
        }
        else if (strcmp (answ, "e") == 0)
        {
            printf ("Enter input file name: ");
            scanf ("%s", input);
            printf ("Enter output file name: ");
            scanf ("%s", output);
            ExpLsmCalc (input, output);
            res = 1;
        }
        else if (strcmp (answ, "p") == 0)
        {
            int deg = 0;
            while (res != 1)
            {
                printf ("What degree of polinom do you want?\n");
                res = scanf ("%lu", &deg);
                if (res == 0)
                    printf ("Please, enter the positive integer number\n");
                ClearInputBuffer ();
            }
            printf ("Enter input file name: ");
            scanf ("%s", input);
            printf ("Enter output file name: ");
            scanf ("%s", output);
            PolinomLsmCalc (deg, input, output);
            res = 1;
        }
        else
        {
            res = 0;
            ClearInputBuffer();
        }
    }
    free (answ);
    free (input);
    free (output);
    return 0;
}