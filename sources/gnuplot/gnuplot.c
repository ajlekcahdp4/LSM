#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <string.h>
#include "../lsm/lsm.h"


FILE *gnuplot_start (char *scriptname, char *picture_name);
void gnuplot_plot (FILE *script, char *title, char *xlabel, char *ylabel, struct lsm_t *LSM);


double _min (double *arr, size_t size)
{
    double min = arr[0];
    for (size_t i = 0; i < size; i++)
    {
        if (min > arr[i])
            min = arr[i];
    }
    return min;
}

double _max (double *arr, size_t size)
{
    double max = arr[0];
    for (size_t i = 0; i < size; i++)
    {
        if (max < arr[i])
            max = arr[i];
    }
    return max;
}

//=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
#define MAX_CMD_SIZE 128
void gnuplot (char *script_name, char *picture_name, char *title, char *xlabel, char *ylabel, struct lsm_t *LSM)
{
    gnuplot_script_gen (script_name, picture_name, title, xlabel, ylabel, LSM);

    char *chmod = calloc (MAX_CMD_SIZE, sizeof(char));
    strcat (chmod, "chmod +x ");
    strcat (chmod, script_name);
    system (chmod);
    free (chmod);

    char *run_script = calloc (MAX_CMD_SIZE, sizeof(char));
    strcat (run_script, "./");
    strcat (run_script, script_name);
    system (run_script);
    free (run_script);
}
#undef MAX_CMD_SIZE


void gnuplot_script_gen (char *script_name, char *picture_name, char *title, char *xlabel, char *ylabel, struct lsm_t *LSM)
{
    FILE *script = gnuplot_start (script_name, picture_name);
    gnuplot_plot (script, title, xlabel, ylabel, LSM);
    fclose (script);
}



FILE *gnuplot_start (char *script_name, char *picture_name)
{
    assert (script_name);
    assert (picture_name);

    FILE *script = fopen (script_name, "w");
    fprintf (script, "#! /usr/bin/gnuplot\n");
    fprintf (script, "set terminal png size 1200, 900\n");
    fprintf (script, "set output \"%s\"\n", picture_name);
    fprintf (script, "set grid xtics ytics\n");
    fprintf (script, "set style line 1 lc rgb \"blue\" lw 4\n");
    fprintf (script, "set style line 2 lc rgb \"red\" lw 4 ps 20\n");
    return script;
}

void gnuplot_plot (FILE *script, char *title, char *xlabel, char *ylabel, struct lsm_t *LSM)
{
    assert (title);
    assert (xlabel);
    assert (ylabel);

    int N = 0;

    fprintf (script, "set title \"%s\"\n", title);
    fprintf (script, "set xlabel \"%s\"\n", xlabel);
    fprintf (script, "set ylabel \"%s\"\n", ylabel);

    switch (LSM->type)
    {
    case LINEAR:
        N = LSM->U.LINE->N;
        fprintf (script, "set xrange [-1.1 * %lf : 1.1 * %lf]\n", _min(LSM->U.LINE->x, N), _max (LSM->U.LINE->x, N));
        fprintf (script, "set yrange [-1.1 * %lf : 1.1 * %lf]\n", _min(LSM->U.EXP->y, N), _max (LSM->U.EXP->y, N));
        fprintf (script, "plot %lf * x %+lf linestyle 1\n", LSM->U.LINE->a, LSM->U.LINE->b);
        break;
    case EXPONENTIAL:
        N = LSM->U.EXP->N;
        fprintf (script, "set xrange [-1.1 * %lf : 1.1 * %lf]\n", _min(LSM->U.EXP->x, N), _max (LSM->U.EXP->x, N));
        fprintf (script, "set yrange [-1.1 * %lf : 1.1 * %lf]\n", _min(LSM->U.EXP->y, N), _max (LSM->U.EXP->y, N));
        fprintf (script, "plot exp (%lf * a %+lf) linestyle 1\n", LSM->U.EXP->a, LSM->U.EXP->b);
        break;
    case POLINOMIAL:
        N = LSM->U.POL->N;
        fprintf (script, "set xrange [-1.1 * %lf : 1.1 * %lf]\n", _min(LSM->U.EXP->x, N), _max (LSM->U.EXP->x, N));
        fprintf (script, "set yrange [-1.1 * %lf : 1.1 * %lf]\n", _min(LSM->U.EXP->y, N), _max (LSM->U.EXP->y, N));
        
        fprintf (script, "plot %lf ", LSM->U.POL->a[0]);
        for (int i = 1; i <= LSM->U.POL->deg; i++)
            fprintf (script, "%+lf * x**%d ", LSM->U.POL->a[i], i);
        fprintf (script, "linestyle 1\n");
        break;
    }
}