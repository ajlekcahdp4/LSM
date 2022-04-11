#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <math.h>
#include "lsm.h"
#include "../gnuplot/gnuplot.h"
#include "../SLE/SLE.h"


#define MAX_STR_SIZE 256

double Sum      (double* a, int N);
double SumMul   (double* a, double* b, int N);
double SumSq    (double* a, int N);
double Get_a    (double* x, double* y, int N);
double Get_b    (double* x, double* y, int N);
double Get_ad   (double*x, double* y, int N);
double Get_bd   (double*x, double* y, int N);

lsm_exp *ExpCalc (struct input *INP);

void LsmPrint (struct lsm_linear* LINE, char *outname);
void PolinomLsmPrint (struct lsm_pol *POL, size_t deg, char *outname);
void ExpLsmPrint (lsm_exp *EXP, char *outname);
//==================================================================================================
//=============================================INPUT================================================
//==================================================================================================

double *InputRow (FILE *file, int N)
{
    double *row = calloc (N, sizeof(double));
    for (int i = 0; i < N; i++)
    {
        fscanf(file, "%lf", row + i);
    }
    return row;
}

#define START_SIZE 32
struct input *Input (char *inputname)
{
    int res  = 2;
    int size = 0;
    double x = NAN;
    double y = NAN;
    struct input * INP = calloc (1, sizeof (struct input));
    INP->x = calloc (START_SIZE, sizeof(double));
    INP->y = calloc (START_SIZE, sizeof(double));
    
    FILE* inputfile = fopen (inputname, "r");
    assert (inputfile);

    while (res == 2)
    {
        res = fscanf (inputfile, "%lf %lf", &x, &y);
        INP->x[size] = x;
        INP->y[size] = y;
        size += 1;
    }
    INP->N = size - 1;
    
    fclose (inputfile);
    return INP;
}


//==================================================================================================
//===========================================LINEAR=LSM=============================================
//==================================================================================================
double Sum (double* a, int N)
{
    double S = 0;
    for (int i = 0; i < N; i++)
        S += a[i];
    return S;
}

double SumMul (double* a, double* b, int N)
{
    double S = 0;
    for (int i = 0; i < N; i++)
        S += a[i] * b[i];
    return S;
}

double SumSq (double* a, int N)
{
    double S = 0;
    for (int i = 0; i < N; i++)
        S += a[i] * a[i];
    return S;
}

double Get_a (double* x, double* y, int N)
{
    double a = (N*SumMul(x, y, N) - Sum(x, N)*Sum(y, N))/(N*SumSq(x, N) - (Sum(x, N) * Sum(x, N)));
    return a;
}

double Get_b (double* x, double* y, int N)
{
    double b = (Sum(y, N) - Get_a(x, y, N)*Sum(x, N))/N;
    return b;
}
double Get_ad (double *x, double* y, int N)
{
    double a = Get_a (x, y, N);
    double ad = (1 / sqrt((double)N)) * sqrt( ((SumSq(y, N) / N) - (Sum(y, N) * Sum(y, N)) / (N*N)) / ((SumSq(x, N) / N) - (Sum(x, N) * Sum(x, N)) / (N*N) ) - (a * a));
    return ad;
}

double Get_bd (double*x, double* y, int N)
{
    double bd = Get_ad (x, y, N) * sqrt(SumSq(x, N) / N - (Sum (x, N) * Sum (x, N)) / (N*N));
    return bd;
}


struct lsm_linear *LinearCalc (struct input *INP)
{
    struct lsm_linear *LINE = calloc (1, sizeof (struct lsm_linear));
    assert (LINE);

    LINE->N = INP->N;
    LINE->x = calloc (LINE->N, sizeof(double));
    LINE->y = calloc (LINE->N, sizeof(double));
    assert (LINE->y);
    assert (LINE->x);

    memcpy (LINE->x, INP->x, LINE->N * sizeof(double));
    memcpy (LINE->y, INP->y, LINE->N * sizeof(double));

    LINE->a  = Get_a   (LINE->x, LINE->y, LINE->N);
    LINE->b  = Get_b   (LINE->x, LINE->y, LINE->N);
    LINE->ad = Get_ad  (LINE->x, LINE->y, LINE->N);
    LINE->bd = Get_bd  (LINE->x, LINE->y, LINE->N);

    return LINE;
}


void LinearLsmCalc (char *inputname, char *outname, char *xlabel, char *ylabel, enum format fmt)
{
    struct input *INP = Input(inputname);

    struct lsm_linear *LINE = LinearCalc (INP);
    free (INP->x);
    free (INP->y);
    free (INP);

    char *script_name = calloc (MAX_STR_SIZE, sizeof(char));
    char *picture_name = calloc (MAX_STR_SIZE, sizeof(char));

    LsmPrint (LINE, outname);

    strcat (script_name, outname);
    strcat (script_name, ".sh");

    strcat (picture_name, outname);
    if (fmt == PNG)
        strcat (picture_name, ".png");
    else
        strcat (picture_name, ".ps");

    struct lsm_t *LSM = calloc (1, sizeof (struct lsm_t));
    LSM->type = LINEAR;
    LSM->U.LINE = LINE;

    struct output_t *out = calloc (1, sizeof(struct output_t));
    out->fmt = fmt;
    out->picture_name = picture_name;
    out->script_name = script_name;
    out->xlabel = xlabel;
    out->ylabel = ylabel;

    gnuplot (out, LSM);
    
    free (out);
    free (script_name);
    free (picture_name);
    free (LSM);

    free (LINE->x);
    free (LINE->y);
    free (LINE);
}

//==================================================================================================
//==========================================POLINOM=LSM=============================================
//==================================================================================================

struct lsm_pol *PolinomCalc (struct input *INP, size_t deg)
{
    struct lsm_pol *POL = calloc (1, sizeof(struct lsm_pol));
    assert (POL);

    POL->N = INP->N;
    POL->x = calloc (POL->N, sizeof(double));
    POL->y = calloc (POL->N, sizeof(double));
    assert (POL->x && POL->y);

    memcpy (POL->x, INP->x, POL->N * sizeof(double));
    memcpy (POL->y, INP->y, POL->N * sizeof(double));

    POL->a = SolveSLE (INP, deg);
    POL->deg = deg;
    
    return POL;
}



void PolinomLsmCalc (int deg, char *inputname, char *outname, char *xlabel, char *ylabel, enum format fmt)
{
    struct input *INP = Input (inputname);

    struct lsm_pol *POL = PolinomCalc (INP, deg);
    free (INP->x);
    free (INP->y);
    free (INP);
    

    PolinomLsmPrint (POL, deg, outname);

    char *script_name = calloc (MAX_STR_SIZE, sizeof(char));
    char *picture_name = calloc (MAX_STR_SIZE, sizeof(char));

    strcat (script_name, outname);
    strcat (script_name, ".sh");

    strcat (picture_name, outname);

    if (fmt == PNG)
        strcat (picture_name, ".png");
    else
        strcat (picture_name, ".ps");

    struct lsm_t *LSM = calloc (1, sizeof (struct lsm_t));
    LSM->type = POLINOMIAL;
    LSM->U.POL = POL;

    struct output_t *out = calloc (1, sizeof(struct output_t));
    out->fmt = fmt;
    out->picture_name = picture_name;
    out->script_name = script_name;
    out->xlabel = xlabel;
    out->ylabel = ylabel;

    gnuplot (out, LSM);

    free(out);
    free (script_name);
    free (picture_name);
    free (LSM);
    
    free (POL->x);
    free (POL->y);
    free (POL->a);
    free (POL);
}
//==================================================================================================
//===========================================EXP_LSM================================================
//==================================================================================================


lsm_exp *ExpCalc (struct input *INP)
{
    lsm_exp *EXP = calloc (1, sizeof(lsm_exp));
    assert (EXP);

    EXP->N = INP->N;
    EXP->x = calloc (EXP->N, sizeof(double));
    EXP->y = calloc (EXP->N, sizeof(double));
    assert (EXP->x && EXP->y);

    for (int i = 0; i < EXP->N; i++)
        EXP->x[i] = INP->x[i];
    for (int i = 0; i < EXP->N; i++)
        EXP->y[i] = log (INP->y[i]);

    EXP->a  = Get_a   (EXP->x, EXP->y, EXP->N);
    EXP->b  = Get_b   (EXP->x, EXP->y, EXP->N);
    EXP->ad = Get_ad  (EXP->x, EXP->y, EXP->N);
    EXP->bd = Get_bd  (EXP->x, EXP->y, EXP->N);
    
    return EXP;
}



void ExpLsmCalc (char *inputname, char *outname, char *xlabel, char *ylabel, enum format fmt)
{
    struct input *INP = Input (inputname);

    lsm_exp *EXP = ExpCalc (INP);
    

    ExpLsmPrint (EXP, outname);
    free (INP->x);
    free (INP->y);
    free (INP);

    char *script_name = calloc (MAX_STR_SIZE, sizeof(char));
    char *picture_name = calloc (MAX_STR_SIZE, sizeof(char));

    strcat (script_name, outname);
    strcat (script_name, ".sh");

    strcat (picture_name, outname);
    strcat (picture_name, ".png");

    struct lsm_t *LSM = calloc (1, sizeof (struct lsm_t));
    LSM->type = EXPONENTIAL;
    LSM->U.EXP = EXP;

     struct output_t *out = calloc (1, sizeof(struct output_t));
    out->fmt = fmt;
    out->picture_name = picture_name;
    out->script_name = script_name;
    out->xlabel = xlabel;
    out->ylabel = ylabel;


    gnuplot (out, LSM);

    free(out);  
    free (script_name);
    free (picture_name);
    free (LSM);

    free (EXP->x);
    free (EXP->y);
    free (EXP);
}

//==================================================================================================
//============================================OUTPUT================================================
//==================================================================================================


void LsmPrint (struct lsm_linear* LINE, char *outname)
{
    //===================for_prog====================
    char *datafilename = calloc (MAX_STR_SIZE, sizeof(char));
    assert (datafilename);

    strcat (datafilename, "data/");
    strcat (datafilename, outname);

    FILE *datafile = fopen (datafilename, "w");
    assert (datafile);
    free (datafilename);

    for (int i = 0; i < LINE->N; i++)
        fprintf (datafile, "%.4g %.4g\n", LINE->x[i], LINE->y[i]);
    fprintf (datafile, "\n");
    fclose (datafile);

    //===================for_user====================
    FILE* out = fopen (outname, "w");

    fprintf (out, "Number of measurements: ");
    fprintf (out, "%d\n\n", LINE->N);

    fprintf (out, "Measured values:\n");
    
    fprintf (out, "X      Y\n");

    for (int i = 0; i < LINE->N; i++)
        fprintf (out, "%-6.4g %-6.4g\n", LINE->x[i], LINE->y[i]);
    fprintf (out, "\n\n");

    fprintf (out, "Coefficients of y = k*x + b:\n");
    fprintf (out, "k = %.4g\n", LINE->a);
    fprintf (out, "b = %.4g\n", LINE->b);
    fprintf (out, "k_dev = %.4g\n", LINE->ad);
    fprintf (out, "b_dev = %.4g\n", LINE->bd);

    fclose (out);

}

void PolinomLsmPrint (struct lsm_pol *POL, size_t deg, char *outname)
{
    //===================for_prog====================
    char *datafilename = calloc (MAX_STR_SIZE, sizeof(char));
    assert (datafilename);

    strcat (datafilename, "data/");
    strcat (datafilename, outname);

    FILE *datafile = fopen (datafilename, "w");
    assert (datafile);

    for (int i = 0; i < POL->N; i++)
        fprintf (datafile, "%.4g %.4g\n", POL->x[i], POL->y[i]);
    fprintf (datafile, "\n");

    for (int i = 0; i <= deg; i++)
        fprintf (datafile, "%.4g ", POL->a[i]);

    fclose (datafile);

    //===================for_user====================
    FILE* out = fopen (outname, "w");
    fprintf (out, "Number of measurements: %d\n\n", POL->N);

    fprintf (out, "Measured values:\n");
    
    fprintf (out, "X      Y\n");
    for (int i = 0; i < POL->N; i++)
        fprintf (out, "%-6.4g %-6.4g\n", POL->x[i], POL->y[i]);
    fprintf (out, "\n\n");

    fprintf (out, "Coefficients of the polinom (from zero-coefficient to %d-coefficiient):\n", POL->N);
    for (int i = 0; i <= deg; i++)
        fprintf (out, "%.4g ", POL->a[i]);
    fprintf (out, "\n");

    free (datafilename);
    fclose (out);    
}

void ExpLsmPrint (lsm_exp *EXP, char *outname)
{
    //===================for_prog====================
    char *datafilename = calloc (MAX_STR_SIZE, sizeof(char));
    assert (datafilename);

    strcat (datafilename, "data/");
    strcat (datafilename, outname);
    printf ("%s\n", datafilename);

    FILE *datafile = fopen (datafilename, "w");
    assert (datafile);

    for (int i = 0; i < EXP->N; i++)
        fprintf (datafile, "%.4g %.4g\n", EXP->x[i], exp(EXP->y[i]));
    fprintf (datafile, "\n");
    
    
    fclose (datafile);

    //===================for_user====================
    FILE *out = fopen (outname, "w");

    fprintf (out, "Number of measurements: %d\n\n", EXP->N);

    fprintf (out, "Measured values:\n");

    fprintf (out, "X      Y\n");

    
    for (int i = 0; i < EXP->N; i++)
        fprintf (out, "%-6.4g %-6.4g\n", EXP->x[i], exp(EXP->y[i]));
    fprintf (out, "\n\n");

    fprintf (out, "Coefficients of the exponent y = exp (k*x + b):\n");
    fprintf (out, "k = %.4g\n", EXP->a);
    fprintf (out, "b = %.4g\n", EXP->b);
    fprintf (out, "k_dev = %.4g\n", EXP->ad);
    fprintf (out, "b_dev = %.4g\n", EXP->bd);

    free (datafilename);
    fclose (out);
}
#undef MAX_STR_SIZE