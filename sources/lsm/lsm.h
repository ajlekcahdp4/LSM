

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




double Sum      (double* a, int N);
double SumMul   (double* a, double* b, int N);
double SumSq    (double* a, int N);
double Get_a    (double* x, double* y, int N);
double Get_b    (double* x, double* y, int N);
double Get_ad   (double*x, double* y, int N);
double Get_bd   (double*x, double* y, int N);
void   LinearLsmCalc  (char *inputname, char *outname);
void   PolinomLsmCalc (int deg, char *inputname, char *outname);
void   ExpLsmCalc     (char *inputname, char *outname);