#ifndef LSM_INCLUDED
#define LSM_INCLUDED

struct input
{
    int N;
    double *x;
    double *y;
};

enum type
{
    LINEAR,
    EXPONENTIAL,
    POLINOMIAL
};

struct lsm_t
{
    double *x;
    double *y;
    double *array_coef;
    double a;
    double b;
    double ad;
    double bd;
    int N;
    int deg;
    enum type type;
};

enum format
{
    PNG,
    PS
};

enum ERRORS
{
    NO_ERROR,
    ERROR_INPUT_FILE_DOES_NOT_EXISTS,
    ERROR_WRONG_PATH_OR_NAME_FOR_OUTPUT_FILE
};


struct lsm_t *LinearCalc (struct input *INP);
struct lsm_t *PolinomCalc (struct input *INP, size_t deg);
struct lsm_t *ExpCalc (struct input *INP);

int LinearLsmCalc (char *inputname, char *outname, char *xlabel, char *ylabel, enum format fmt);
int PolinomLsmCalc (int deg, char *inputname, char *outname, char *xlabel, char *ylabel, enum format fmt);
int ExpLsmCalc (char *inputname, char *outname, char *xlabel, char *ylabel, enum format fmt);

struct lsm_t *LinearCalc (struct input *INP);
int PolinomLsmPrint (struct lsm_t *POL, char *outname);
int ExpLsmPrint (struct lsm_t *EXP, char *outname);

#endif