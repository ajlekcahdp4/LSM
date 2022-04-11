#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lsm/lsm.h"

#define MAX_ANSWER_SIZE 256

void ClearInputBuffer ()
{
    while (getchar() != '\n') {;}
}

int ReadWord (char *buf)
{
    int i = 0;
    char c = getchar ();
    
    while (c == '\n')
        c = getchar ();

    while (c != '\n')
    {
        buf[i] = c;
        i++;
        c = getchar ();
    }
    if (i == 0)
        return 1;
    return 0;
} 


int main ()
{
    int res = 0;
    char *answ   = calloc (MAX_ANSWER_SIZE, sizeof(char));
    char *input  = calloc (MAX_ANSWER_SIZE, sizeof(char));
    char *output = calloc (MAX_ANSWER_SIZE, sizeof(char));
    char *xlabel = calloc (MAX_ANSWER_SIZE, sizeof(char));
    char *ylabel = calloc (MAX_ANSWER_SIZE, sizeof(char));
    char *fmt    = calloc (16, sizeof(char));
    printf ("What approximation do you want to use?\n");
    while (res != 1)
    {
        printf ("Please, Answer \'l\' - linear, \'e\' - exponential or \'p\' - polinomial\n");
        scanf ("%s", answ);
        if (strcmp (answ, "l") == 0)
        {
            printf ("Enter input file name: ");
            scanf ("%s", input);
            ClearInputBuffer ();
            printf ("Enter output file name: ");
            scanf ("%s", output);
            ClearInputBuffer ();
            printf ("Enter the name of the abscissa axis\n");
            ReadWord (xlabel);
            printf ("Enter the name of the ordinate axis\n");
            ReadWord (ylabel);

            printf ("Enter the format of picture output\n");

            while (res != 1)
            {
                printf ("Please, choose \"png\" or \"ps\" (postscript)\n");
                ReadWord (fmt);
                res = 1;
                if (strcmp (fmt , "png") == 0)
                    LinearLsmCalc (input, output, xlabel, ylabel, PNG);
                else if (strcmp(fmt, "ps") == 0)
                    LinearLsmCalc (input, output, xlabel, ylabel, PS);
                else
                    res = 0;
            }   
            res = 1;
        }
        else if (strcmp (answ, "e") == 0)
        {
            printf ("Enter input file name: ");
            scanf ("%s", input);
            ClearInputBuffer ();
            printf ("Enter output file name: ");
            scanf ("%s", output);
            ClearInputBuffer ();
            printf ("Enter the name of the abscissa axis\n");
            ReadWord (xlabel);
            printf ("Enter the name of the ordinate axis\n");
            ReadWord (ylabel);
            //----------------fmt---------------------------
            printf ("Enter the format of picture output\n");
            while (res != 1)
            {
                printf ("Please, choose \"png\" or \"ps\" (postscript)\n");
                ReadWord (fmt);
                res = 1;
                if (strcmp (fmt , "png") == 0)
                    ExpLsmCalc (input, output, xlabel, ylabel, PNG);
                else if (strcmp(fmt, "ps") == 0)
                    ExpLsmCalc (input, output, xlabel, ylabel, PS);
                else
                    res = 0;
            }   
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
            ClearInputBuffer ();
            printf ("Enter output file name: ");
            scanf ("%s", output);
            ClearInputBuffer ();
            printf ("Enter the name of the abscissa axis\n");
            ReadWord (xlabel);
            printf ("Enter the name of the ordinate axis\n");
            ReadWord (ylabel);
            printf ("Enter the format of picture output\n");
            res = 0;
            while (res != 1)
            {
                printf ("Please, choose \"png\" or \"ps\" (postscript)\n");
                ReadWord (fmt);
                res = 1;
                if (strcmp (fmt , "png") == 0)
                    PolinomLsmCalc (deg, input, output, xlabel, ylabel, PNG);
                else if (strcmp(fmt, "ps") == 0)
                    PolinomLsmCalc (deg, input, output, xlabel, ylabel, PS);
                else
                    res = 0;
            }   
            res = 1;
        }
        else
        {
            res = 0;
            ClearInputBuffer();
        }
    }
    free (xlabel);
    free (ylabel);
    free (answ);
    free (input);
    free (output);
    return 0;
}