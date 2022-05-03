#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lsm.h"

#define MAX_ANSWER_SIZE 256

void ClearInputBuffer ()
{
    while ( getchar () != '\n' )
    {
        ;
    }
}


void ClearBuffer (char *buf, size_t size)
{
    for (size_t i = 0; i < size; i++)
        buf[i] = '\0';
}

int ReadWord (char *buf)
{
    int i  = 0;
    char c = getchar ();

    while ( c == '\n' )
        c = getchar ();

    while ( c != '\n' )
    {
        buf[i] = c;
        i++;
        c = getchar ();
    }
    if ( i == 0 )
        return 1;
    return 0;
}

int main ()
{
    int res      = 1;
    int calc_res = 0;
    enum format FMT = 0;
    char *answ   = calloc (MAX_ANSWER_SIZE, sizeof (char));
    char *input  = calloc (MAX_ANSWER_SIZE, sizeof (char));
    char *output = calloc (MAX_ANSWER_SIZE, sizeof (char));
    char *xlabel = calloc (MAX_ANSWER_SIZE, sizeof (char));
    char *ylabel = calloc (MAX_ANSWER_SIZE, sizeof (char));
    char *fmt    = calloc (16, sizeof (char));
    printf ("What approximation do you want to use?\n");
    while ( res != 0 )
    {
        printf ("Please, Answer \'l\' - linear, \'e\' - exponential or \'p\' - polinomial\n");
        scanf ("%s", answ);
        ClearInputBuffer ();
        if ( strcmp (answ, "l") == 0 )
        {
            printf ("Enter input file name: ");
            scanf ("%s", input);
            ClearInputBuffer ();
            printf ("Enter output file name: ");
            scanf ("%s", output);
            ClearInputBuffer ();
            printf ("Enter the name of the abscissa axis: ");
            ReadWord (xlabel);
            printf ("Enter the name of the ordinate axis: ");
            ReadWord (ylabel);

            printf ("Enter the format of picture output\n");
            res = 1;
            while ( res != 0 )
            {
                printf ("Please, choose \"png\" or \"ps\" (postscript): ");
                ClearBuffer(fmt, 16);
                ReadWord (fmt);

                if (strcmp (fmt, "png") == 0)
                {
                    res = 0;
                    FMT = PNG;
                }
                else if (strcmp(fmt, "ps") == 0)
                {
                    res = 0;
                    FMT = PS;
                } 
                ClearBuffer(fmt, 16);
            }
            calc_res = LinearLsmCalc (input, output, xlabel, ylabel, FMT);
            if (calc_res != 0)
                goto free_end_exit;
        }
        else if ( strcmp (answ, "e") == 0 )
        {
            printf ("Enter input file name: ");
            scanf ("%s", input);
            ClearInputBuffer ();
            printf ("Enter output file name: ");
            scanf ("%s", output);
            ClearInputBuffer ();
            printf ("Enter the name of the abscissa axis: ");
            ReadWord (xlabel);
            printf ("Enter the name of the ordinate axis: ");
            ReadWord (ylabel);
            //----------------fmt---------------------------
            printf ("Enter the format of picture output\n");
            res = 1;
            while ( res != 0 )
            {
                printf ("Please, choose \"png\" or \"ps\" (postscript): ");
                ClearBuffer(fmt, 16);
                ReadWord (fmt);

                if (strcmp (fmt, "png") == 0)
                {
                    res = 0;
                    FMT = PNG;
                }
                else if (strcmp(fmt, "ps") == 0)
                {
                    res = 0;
                    FMT = PS;
                } 
            }
            calc_res = ExpLsmCalc (input, output, xlabel, ylabel, FMT);
            if (calc_res != 0)
                goto free_end_exit;
        }
        else if ( strcmp (answ, "p") == 0 )
        {
            size_t deg = 0;
            res = 1;
            while ( res != 0 )
            {
                printf ("What degree of polinom do you want to be used?: ");
                res = scanf ("%lu", &deg);
                if ( res == 0 )
                {
                    printf ("Please, enter the positive integer number\n");
                    res = 1;
                }
                else
                    res = 0;
                ClearInputBuffer ();
            }
            printf ("Enter input file name: ");
            scanf ("%s", input);
            ClearInputBuffer ();
            printf ("Enter output file name: ");
            scanf ("%s", output);
            ClearInputBuffer ();
            printf ("Enter the name of the abscissa axis: ");
            ReadWord (xlabel);
            printf ("Enter the name of the ordinate axis: ");
            ReadWord (ylabel);
            printf ("Enter the format of picture output\n");
            res = 1;
            while ( res != 0 )
            {
                printf ("Please, choose \"png\" or \"ps\" (postscript): ");
                ClearBuffer(fmt, 16);
                ReadWord (fmt);

                if (strcmp (fmt, "png") == 0)
                {
                    res = 0;
                    FMT = PNG;
                }
                else if (strcmp(fmt, "ps") == 0)
                {
                    res = 0;
                    FMT = PS;
                } 
            }
            calc_res = PolinomLsmCalc (deg, input, output, xlabel, ylabel, FMT);
            if (calc_res != 0)
                goto free_end_exit;
        }
        else
        {
            res = 1;
            ClearInputBuffer ();
        }
    }
free_end_exit:
    free (fmt); 
    free (xlabel);
    free (ylabel);
    free (answ);
    free (input);
    free (output);
    return 0;
}