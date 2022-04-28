#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "calcs.h"
#include "gnuplot.h"

FILE *gnuplot_start (char *scriptname, char *picture_name);
void gnuplot_plot (FILE *script, struct output_t *out, char *input_name, struct lsm_t *LSM);
void gnuplot_script_gen (struct output_t *out, char *input_name, struct lsm_t *LSM);

//=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=+=
#define MAX_CMD_SIZE 128
void gnuplot (struct output_t *out, char *input_name, struct lsm_t *LSM)
{
    gnuplot_script_gen (out, input_name, LSM);

    char *chmod = calloc (MAX_CMD_SIZE, sizeof (char));
    strcat (chmod, "chmod +x ");
    strcat (chmod, out->script_name);
    system (chmod);
    free (chmod);

    char *run_script = calloc (MAX_CMD_SIZE, sizeof (char));
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

    if ( strcmp (picture_name + picture_name_len - 4, ".png") == 0 )
        fprintf (script, "set terminal png size 1200, 1000\n");
    else if ( strcmp (picture_name + picture_name_len - 3, ".ps") == 0 )
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
    assert (out);

    int N           = LSM->N;
    double min_x    = 0;
    double max_x    = 0;
    double diff_x   = 0;
    double min_y    = 0;
    double max_y    = 0;
    double diff_y   = 0;
    double accuracy = NAN;

    fprintf (script, "set xlabel \"%s\" font \"Times, 20\"\n", out->xlabel);
    fprintf (script, "set ylabel \"%s\" font \"Times, 20\"\n", out->ylabel);

    switch ( LSM->type )
    {
    case LINEAR:
        max_x  = _max (LSM->x, N);
        min_x  = _min (LSM->x, N);
        diff_x = max_x - min_x;

        max_y  = _max (LSM->y, N);
        min_y  = _min (LSM->y, N);
        diff_y = max_y - min_y;

        accuracy = 0.01 * min_y;

        fprintf (script, "set xrange [%g : %g]\n", min_x - 0.1 * diff_x, max_x + 0.1 * diff_x);
        fprintf (script, "set yrange [%g : %g]\n", min_y - 0.1 * diff_y, max_y + 0.1 * diff_y);
        if ( fabs (LSM->b) < accuracy )
            fprintf (script, "plot %g * x linestyle 1, \"%s\" with points linestyle 2 notitle\n", LSM->a, input_name);
        else
            fprintf (script, "plot %g * x %+g linestyle 1, \"%s\" with points linestyle 2 notitle\n", LSM->a, LSM->b,
                     input_name);
        break;
    case EXPONENTIAL:
        N      = LSM->N;
        max_x  = _max (LSM->x, N);
        min_x  = _min (LSM->x, N);
        diff_x = max_x - min_x;

        max_y  = exp (_max (LSM->y, N));
        min_y  = exp (_min (LSM->y, N));
        diff_y = max_y - min_y;

        accuracy = 0.01 * min_y;

        fprintf (script, "set xrange [%g : %g]\n", min_x - 0.1 * diff_x, max_x + 0.1 * diff_x);
        fprintf (script, "set yrange [%g : %g]\n", min_y - 0.1 * diff_y, max_y + 0.1 * diff_y);
        if ( fabs (LSM->b) < accuracy )
            fprintf (script, "plot exp (%g * x) linestyle 1, \"%s\" with points linestyle 2 notitle\n", LSM->a,
                     input_name);
        else
            fprintf (script, "plot exp (%g * x %+g) linestyle 1, \"%s\" with points linestyle 2 notitle\n", LSM->a,
                     LSM->b, input_name);
        break;
    case POLINOMIAL:
        N      = LSM->N;
        max_x  = _max (LSM->x, N);
        min_x  = _min (LSM->x, N);
        diff_x = max_x - min_x;

        max_y  = _max (LSM->y, N);
        min_y  = _min (LSM->y, N);
        diff_y = max_y - min_y;

        fprintf (script, "set xrange [%g : %g]\n", min_x - 0.1 * diff_x, max_x + 0.1 * diff_x);
        fprintf (script, "set yrange [%g : %g]\n", min_y - 0.1 * diff_y, max_y + 0.1 * diff_y);

        fprintf (script, "plot %g ", LSM->array_coef[0]);
        for ( int i = 1; i <= LSM->deg; i++ )
            fprintf (script, "%+g * x**%d ", LSM->array_coef[i], i);
        fprintf (script, "linestyle 1, \"%s\" with points linestyle 2 notitle\n", input_name);
        break;
    }
}
#undef MAX_NAME_LEN