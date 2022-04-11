#ifndef LSM_INCLUDED
#define LSM_INCLUDED
struct lsm_linear
{
    int     N;
    double* x;
    double* y;
    double  a;
    double  b;
    double  ad;
    double  bd;
};

struct input
{
    int N;
    double *x;
    double *y;
};

struct lsm_pol
{
    double *x;
    double *y;
    double *a;
    int N;
    int deg;
};


typedef struct lsm_linear lsm_exp;

enum type { LINEAR, EXPONENTIAL, POLINOMIAL };

struct lsm_t
{
    union 
    {
        struct lsm_linear *LINE;
        struct lsm_pol    *POL;
        lsm_exp *EXP;
    } U;
    enum type type;
};


enum format { PNG, PS };

void   LinearLsmCalc  (char *inputname, char *outname, char *xlabel, char *ylabel, enum format fmt);
void   PolinomLsmCalc (int deg, char *inputname, char *outname, char *xlabel, char *ylabel, enum format fmt);
void   ExpLsmCalc     (char *inputname, char *outname, char *xlabel, char *ylabel, enum format fmt);
#endif