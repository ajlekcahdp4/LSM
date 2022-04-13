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

enum ERRORS { NO_ERROR, ERROR_INPUT_FILE_DOES_NOT_EXISTS };

int LinearLsmCalc  (char *inputname, char *outname, char *xlabel, char *ylabel, enum format fmt);
int PolinomLsmCalc (int deg, char *inputname, char *outname, char *xlabel, char *ylabel, enum format fmt);
int ExpLsmCalc     (char *inputname, char *outname, char *xlabel, char *ylabel, enum format fmt);
#endif