#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "SLE.h"
#include "calcs.h"
#include "gnuplot.h"
#include "lsm.h"

#define MAX_STR_SIZE 256

double Get_a (double *x, double *y, int N);
double Get_b (double *x, double *y, int N);
double Get_ad (double *x, double *y, int N);
double Get_bd (double *x, double *y, int N);

void LsmPrint (struct lsm_t *LINE, char *outname);
void PolinomLsmPrint (struct lsm_t *POL, char *outname);
void ExpLsmPrint (struct lsm_t *EXP, char *outname);

//==================================================================================================
//=============================================INPUT================================================
//==================================================================================================

double *InputRow (FILE *file, int N)
{
    double *row = calloc (N, sizeof (double));
    for ( int i = 0; i < N; i++ )
    {
        fscanf (file, "%lf", row + i);
    }
    return row;
}

//==================================================================================================

struct input *InputResize (struct input *INP, int capacity)
{
    INP->x = realloc (INP->x, capacity * sizeof (double));
    INP->y = realloc (INP->y, capacity * sizeof (double));
    return INP;
}

//==================================================================================================

#define START_SIZE ((int)32)

struct input *Input (char *inputname)
{
    int res           = 2;
    int size          = 0;
    int capacity      = START_SIZE;
    double x          = NAN;
    double y          = NAN;
    struct input *INP = calloc (1, sizeof (struct input));
    INP->x            = calloc (capacity, sizeof (double));
    INP->y            = calloc (capacity, sizeof (double));

    FILE *inputfile = fopen (inputname, "r");
    if ( inputfile == NULL )
    {
        fprintf (stderr, "ERROR: input file does not exists\n");
        free (INP->x);
        free (INP->y);
        free (INP);
        return NULL;
    }

    while ( res == 2 )
    {
        if ( size == capacity )
        {
            capacity *= 2;
            INP = InputResize (INP, capacity);
        }
        res          = fscanf (inputfile, "%lf %lf", &x, &y);
        INP->x[size] = x;
        INP->y[size] = y;
        size += 1;
    }
    INP->N = size - 1;

    fclose (inputfile);
    return INP;
}

//==================================================================================================

char *ChangeExtenshion (char *filename, char *new_extension)   // don't free old name
{
    size_t old_len = strlen (filename);
    size_t ext_len = strlen (new_extension);
    size_t new_len = old_len + ext_len;

    char *newname   = calloc (new_len + 1, sizeof (char));
    size_t i        = 0;
    unsigned char c = 0;

    while ( c != '.' && i < old_len )
    {
        c          = filename[i];
        newname[i] = c;
        i++;
    }
    if ( c == old_len )
        newname[i] = '.';
    strcat (newname, new_extension);

    return newname;
}

//==================================================================================================

struct output_inf *SetOutputInf (char *outname, char *xlabel, char *ylabel, enum format fmt)
{
    char *picture_name = NULL;
    char *script_name = ChangeExtenshion (outname, "sh");

    if ( fmt == PNG )
        picture_name = ChangeExtenshion (outname, "png");
    else
        picture_name = ChangeExtenshion (outname, "ps");

    struct output_inf *out = calloc (1, sizeof (struct output_inf));
    out->fmt             = fmt;
    out->picture_name    = picture_name;
    out->script_name     = script_name;
    out->xlabel          = xlabel;
    out->ylabel          = ylabel;
    return out;
}

//==================================================================================================
//===========================================LINEAR=LSM=============================================
//==================================================================================================

double Get_a (double *x, double *y, int N)
{
    double a = (N * SumMul (x, y, N) - Sum (x, N) * Sum (y, N)) / (N * SumSq (x, N) - (Sum (x, N) * Sum (x, N)));
    return a;
}

double Get_b (double *x, double *y, int N)
{
    double b = (Sum (y, N) - Get_a (x, y, N) * Sum (x, N)) / N;
    return b;
}
double Get_ad (double *x, double *y, int N)
{
    double a  = Get_a (x, y, N);
    double ad = (1 / sqrt ((double)N)) *
        sqrt (((SumSq (y, N) / N) - (Sum (y, N) * Sum (y, N)) / (N * N)) /
                  ((SumSq (x, N) / N) - (Sum (x, N) * Sum (x, N)) / (N * N)) -
              (a * a));
    return ad;
}

double Get_bd (double *x, double *y, int N)
{
    double bd = Get_ad (x, y, N) * sqrt (SumSq (x, N) / N - (Sum (x, N) * Sum (x, N)) / (N * N));
    return bd;
}

double Get_a_dp (double *x, double *y, int N)
{
    double a = (SumMul (x, y, N)) / (SumSq (x, N));
    return a;
}

double Get_ad_dp (double *x, double *y, int N)
{
    double a  = Get_a_dp (x, y, N);
    double ad = sqrt ((SumSq (y, N) / SumSq (x, N) - a * a) / N);
    return ad;
}

//==================================================================================================

struct lsm_t *LinearCalc (struct input *INP)
{
    struct lsm_t *LINE = calloc (1, sizeof (struct lsm_t));
    assert (LINE);

    LINE->type = LINEAR;

    LINE->N = INP->N;
    LINE->x = INP->x;
    LINE->y = INP->y;

    LINE->b = Get_b (LINE->x, LINE->y, LINE->N);

    if ( LINE->b < 0.01 * _min (LINE->x, LINE->N) )
    {
        LINE->b  = (double)0;
        LINE->a  = Get_a_dp (LINE->x, LINE->y, LINE->N);
        LINE->ad = Get_ad_dp (LINE->x, LINE->y, LINE->N);
    }
    else
    {
        LINE->a  = Get_a (LINE->x, LINE->y, LINE->N);
        LINE->ad = Get_ad (LINE->x, LINE->y, LINE->N);
        LINE->bd = Get_bd (LINE->x, LINE->y, LINE->N);
    }
    return LINE;
}

//==================================================================================================

int LinearLsmCalc (char *inputname, char *outname, char *xlabel, char *ylabel, enum format fmt)
{
    struct input *INP = Input (inputname);
    if ( INP == NULL )
        return ERROR_INPUT_FILE_DOES_NOT_EXISTS;

    struct lsm_t *LINE = LinearCalc (INP);
    free (INP);

    LsmPrint (LINE, outname);

    struct output_inf *out = SetOutputInf (outname, xlabel, ylabel, fmt);

    gnuplot (out, inputname, LINE);

    free (out->script_name);
    free (out->picture_name);
    free (out);

    free (LINE->x);
    free (LINE->y);
    free (LINE);

    return 0;
}

//==================================================================================================
//==========================================POLINOM=LSM=============================================
//==================================================================================================

struct lsm_t *PolinomCalc (struct input *INP, size_t deg)
{
    struct lsm_t *POL = calloc (1, sizeof (struct lsm_t));
    assert (POL);

    POL->type = POLINOMIAL;

    POL->N = INP->N;
    POL->x = INP->x;
    POL->y = INP->y;

    POL->array_coef = SolveSLE (INP, deg);
    POL->deg        = deg;

    return POL;
}

//==================================================================================================

int PolinomLsmCalc (int deg, char *inputname, char *outname, char *xlabel, char *ylabel, enum format fmt)
{
    struct input *INP = Input (inputname);

    if ( INP == NULL )
        return ERROR_INPUT_FILE_DOES_NOT_EXISTS;

    struct lsm_t *POL = PolinomCalc (INP, deg);
    free (INP);

    PolinomLsmPrint (POL, outname);

    struct output_inf *out = SetOutputInf (outname, xlabel, ylabel, fmt);

    gnuplot (out, inputname, POL);

    free (out->script_name);
    free (out->picture_name);
    free (out);

    free (POL->x);
    free (POL->y);
    free (POL->array_coef);
    free (POL);

    return 0;
}
//==================================================================================================
//===========================================EXP_LSM================================================
//==================================================================================================

struct lsm_t *ExpCalc (struct input *INP)
{
    struct lsm_t *EXP = calloc (1, sizeof (struct lsm_t));
    assert (EXP);

    EXP->type = EXPONENTIAL;

    EXP->N = INP->N;
    EXP->x = calloc (EXP->N, sizeof (double));
    EXP->y = calloc (EXP->N, sizeof (double));
    assert (EXP->x && EXP->y);

    EXP->x = INP->x;
    for ( int i = 0; i < EXP->N; i++ )
        EXP->y[i] = log (INP->y[i]);

    EXP->b = Get_b (EXP->x, EXP->y, EXP->N);

    if ( EXP->b < 0.01 * _min (EXP->x, EXP->N) )
    {
        EXP->b  = (double)0;
        EXP->a  = Get_a_dp (EXP->x, EXP->y, EXP->N);
        EXP->ad = Get_ad_dp (EXP->x, EXP->y, EXP->N);
    }
    else
    {
        EXP->a  = Get_a (EXP->x, EXP->y, EXP->N);
        EXP->ad = Get_ad (EXP->x, EXP->y, EXP->N);
        EXP->bd = Get_bd (EXP->x, EXP->y, EXP->N);
    }

    return EXP;
}

//==================================================================================================

int ExpLsmCalc (char *inputname, char *outname, char *xlabel, char *ylabel, enum format fmt)
{
    struct input *INP = Input (inputname);
    if ( INP == NULL )
        return ERROR_INPUT_FILE_DOES_NOT_EXISTS;

    struct lsm_t *EXP = ExpCalc (INP);
    free (INP);
    free (INP->y);

    ExpLsmPrint (EXP, outname);

    struct output_inf *out = SetOutputInf (outname, xlabel, ylabel, fmt);

    gnuplot (out, inputname, EXP);

    free (out->script_name);
    free (out->picture_name);
    free (out);

    free (EXP->x);
    free (EXP->y);
    free (EXP);

    return 0;
}

//==================================================================================================
//============================================OUTPUT================================================
//==================================================================================================
#define COMMON_ACCURACY ((double)1e-3)

void LsmPrint (struct lsm_t *LINE, char *outname)
{
    FILE *out = fopen (outname, "w");

    fprintf (out, "Number of measurements: ");
    fprintf (out, "%d\n\n", LINE->N);

    fprintf (out, "Measured values:\n");

    fprintf (out, "%6sX%7sY\n", "", "");

    for ( int i = 0; i < LINE->N; i++ )
        fprintf (out, "%7g %7g\n", LINE->x[i], LINE->y[i]);
    fprintf (out, "\n\n");

    fprintf (out, "Coefficients of y = k*x + b:\n");
    fprintf (out, "k = %g\n", LINE->a);
    fprintf (out, "b = %g\n", LINE->b);
    fprintf (out, "k_dev = %g\n", LINE->ad);
    fprintf (out, "b_dev = %g\n", LINE->bd);

    fclose (out);
}

//==================================================================================================

void PolinomLsmPrint (struct lsm_t *POL, char *outname)
{
    FILE *out = fopen (outname, "w");
    fprintf (out, "Number of measurements: %d\n\n", POL->N);

    fprintf (out, "Measured values:\n");

    fprintf (out, "%6sX%7sY\n", "", "");
    for ( int i = 0; i < POL->N; i++ )
        fprintf (out, "%7g %7g\n", POL->x[i], POL->y[i]);
    fprintf (out, "\n\n");

    fprintf (out, "Coefficients of the polinom (from zero-coefficient to %d-coefficiient):\n", POL->deg);
    for ( int i = 0; i <= POL->deg; i++ )
        fprintf (out, "%g ", POL->array_coef[i]);
    fprintf (out, "\n");

    fclose (out);
}

//==================================================================================================

void ExpLsmPrint (struct lsm_t *EXP, char *outname)
{
    FILE *out = fopen (outname, "w");

    fprintf (out, "Number of measurements: %d\n\n", EXP->N);

    fprintf (out, "Measured values:\n");

    fprintf (out, "%6sX%7sY\n", "", "");

    for ( int i = 0; i < EXP->N; i++ )
        fprintf (out, "%7g %7g\n", EXP->x[i], exp (EXP->y[i]));
    fprintf (out, "\n\n");

    fprintf (out, "Coefficients of the exponent y = exp (k*x + b):\n");

    fprintf (out, "k = %g\n", EXP->a);
    fprintf (out, "b = %g\n", EXP->b);
    fprintf (out, "k_dev = %.g\n", EXP->ad);
    fprintf (out, "b_dev = %.g\n", EXP->bd);

    fclose (out);
}
#undef MAX_STR_SIZE
