

struct lsm_linear {
    int     N;
    double* x;
    double* y;
    double  a;
    double  b;
    double  ad;
    double  bd;
};


struct input {
    int N;
    double *x;
    double *y;
};

struct lsm_pol {
    int N;
    double *x;
    double *y;
    double *a;
};


typedef struct lsm_linear lsm_exp;

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