#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include <string.h>
#include "gnuplot.h"


FILE *gnuplot_start (char *scriptname, char *picture_name);
void gnuplot_plot (FILE *script, struct output_t *out, char *input_name, struct lsm_t *LSM);
void gnuplot_script_gen (struct output_t *out, char *input_name, struct lsm_t *LSM);

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
void gnuplot (struct output_t *out, char *input_name, struct lsm_t *LSM)
{
    gnuplot_script_gen (out, input_name, LSM);

    char *chmod = calloc (MAX_CMD_SIZE, sizeof(char));
    strcat (chmod, "chmod +x ");
    strcat (chmod, out->script_name);
    system (chmod);
    free (chmod);

    char *run_script = calloc (MAX_CMD_SIZE, sizeof(char));
    strcat (run_script, "./");
    strcat (run_script, out->script_name);
    system (run_script);
    free (run_script);
}
#undef MAX_CMD_SIZE


void gnuplot_script_gen (struct output_t *out, char *input_name, struct lsm_t *LSM)
{
    FILE *script = gnuplot_start (out->script_name, out->picture_name);
    gnuplot_plot (script, out, input_name, LSM);
    fclose (script);
}



FILE *gnuplot_start (char *script_name, char *picture_name)
{
    assert (script_name);
    assert (picture_name);
    size_t picture_name_len = strlen (picture_name);

    FILE *script = fopen (script_name, "w");
    fprintf (script, "#! /usr/bin/gnuplot\n");

    if (strcmp (picture_name + picture_name_len - 4, ".png") == 0)
        fprintf (script, "set terminal png size 1200, 1000\n");
    else if (strcmp (picture_name + picture_name_len - 3, ".ps") == 0)
        fprintf (script, "set terminal postscript eps enhanced color solid\n");
    
    fprintf (script, "set output \"%s\"\n", picture_name);
    fprintf (script, "set font \"Times, 20\"\n");
    fprintf (script, "set style line 1 lc rgb \"blue\" lw 4\n");
    fprintf (script, "set style line 2 lc rgb \"red\" lw 4 ps 3\n");
    fprintf (script, "set style line 3 lc rgb \"black\" lw 2\n");
    fprintf (script, "set grid xtics ytics\n");
    fprintf (script, "set xzeroaxis linestyle 3\n");
    fprintf (script, "set yzeroaxis linestyle 3\n");
    return script;
}

#define MAX_NAME_LEN 256
void gnuplot_plot (FILE *script, struct output_t *out, char *input_name, struct lsm_t *LSM)
{
    assert(out);

    int N      = 0;
    double min_x  = 0;
    double max_x  = 0;
    double diff_x = 0;
    double min_y  = 0;
    double max_y  = 0;
    double diff_y = 0;


    
    
    fprintf (script, "set xlabel \"%s\" font \"Times, 20\"\n", out->xlabel);
    fprintf (script, "set ylabel \"%s\" font \"Times, 20\"\n", out->ylabel);

    switch (LSM->type)
    {
    case LINEAR:
        N = LSM->U.LINE->N;
        max_x  = _max (LSM->U.LINE->x, N);
        min_x  = _min (LSM->U.LINE->x, N);
        diff_x = max_x - min_x;

        max_y  = _max (LSM->U.LINE->y, N);
        min_y  = _min (LSM->U.LINE->y, N);
        diff_y = max_y - min_y;

        fprintf (script, "set xrange [%lf : %lf]\n", min_x - 0.1*diff_x, max_x + 0.1*diff_x);
        fprintf (script, "set yrange [%lf : %lf]\n", min_y - 0.1*diff_y, max_y + 0.1*diff_y);
        fprintf (script, "plot %lf * x %+lf linestyle 1, \"%s\" with points linestyle 2 notitle\n", LSM->U.LINE->a, LSM->U.LINE->b, input_name);
        break;
    case EXPONENTIAL:
        N = LSM->U.EXP->N;
        max_x  = _max (LSM->U.EXP->x, N);
        min_x  = _min (LSM->U.EXP->x, N);
        diff_x = max_x - min_x;

        max_y  = exp (_max (LSM->U.EXP->y, N));
        min_y  = exp (_min (LSM->U.EXP->y, N));
        diff_y = max_y - min_y;

        fprintf (script, "set xrange [%lf : %lf]\n", min_x - 0.1*diff_x, max_x + 0.1*diff_x);
        fprintf (script, "set yrange [%lf : %lf]\n", min_y - 0.1*diff_y, max_y + 0.1*diff_y);
        fprintf (script, "plot exp (%lf * x %+lf) linestyle 1, \"%s\" with points linestyle 2 notitle\n", LSM->U.EXP->a, LSM->U.EXP->b, input_name);
        break;
    case POLINOMIAL:
        N = LSM->U.POL->N;
        max_x  = _max (LSM->U.POL->x, N);
        min_x  = _min (LSM->U.POL->x, N);
        diff_x = max_x - min_x;

        max_y  = _max (LSM->U.POL->y, N);
        min_y  = _min (LSM->U.POL->y, N);
        diff_y = max_y - min_y;

        fprintf (script, "set xrange [%lf : %lf]\n", min_x - 0.1*diff_x, max_x + 0.1*diff_x);
        fprintf (script, "set yrange [%lf : %lf]\n", min_y - 0.1*diff_y, max_y + 0.1*diff_y);
        
        fprintf (script, "plot %lf ", LSM->U.POL->a[0]);
        for (int i = 1; i <= LSM->U.POL->deg; i++)
            fprintf (script, "%+e * x**%d ", LSM->U.POL->a[i], i);
        fprintf (script, "linestyle 1, \"%s\" with points linestyle 2 notitle\n", input_name);
        break;
    }
}
#undef MAX_NAME_LEN