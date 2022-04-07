#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>


#define EPSILON (double)1e-7
#define NULL_DOUBLE (double)0

struct coordinates
{
    size_t row;
    size_t col;
};

struct input 
{
    int N;
    double *x;
    double *y;
};

double** StdinMatrixInit   (size_t N);
double   Gauss_Jordan (double **Matrix, size_t N);
double   DiagonalDet  (double **Matrix, size_t N);
double   Find_Bk      (struct input *INP, size_t k);
double   Find_Ck      (struct input *INP, size_t k);
void     Elimination  (double** Matrix, size_t N, size_t col);
void     DeleteMatrix (double **Matrix, size_t N);
void     PrintMatrix  (double **Matrix, size_t N);
void     SwitchRows   (double **Matrix, size_t N, size_t row1, size_t row2);
void     SwitchCols   (double **Matrix, size_t N, size_t col1, size_t col2);
int      DoubleCompr  (const double x, const double y, double EPS);
struct coordinates *MaxElemInCol    (double **Matrix, size_t N, size_t col);
struct coordinates *MaxElemInMatrix (double** Matrix, size_t n, size_t N);



//===========================================================================================
//=====================================Gauss=Elimination=====================================
//===========================================================================================


double Gauss_Jordan (double** Matrix, size_t N)
{
    double det  = 1.0;
    size_t row  = 0;
    size_t col  = 0;
    size_t Prow = 0;
    size_t Pcol = 0;
    while (col < N)
    {
        struct coordinates *coord = MaxElemInCol (Matrix, N, col);
        Prow = coord->row;
        Pcol = coord->col;
        free (coord);
        if (DoubleCompr (Matrix[Prow][Pcol], NULL_DOUBLE, EPSILON) == 0)
            fprintf (stderr, "MATH_ERROR: The system of the linear equations has infinitely many solutions\n");

        if (col != Prow && Prow > col)
        {
            SwitchRows (Matrix, N, col, Prow);
            det *= -1;
        }
        Elimination (Matrix, N, col);

        col++;
    }
    det *= DiagonalDet (Matrix, N);

    return det;
}


void Elimination (double** Matrix, size_t N, size_t col)
{
    double k  = NULL_DOUBLE;

    for (size_t row = 0; row < N; row++)
    {
        if (row != col)
        {
            k = Matrix[row][col] / Matrix [col][col];
            for (size_t cur_col = col; cur_col <= N + 1; cur_col++)
            {
                Matrix[row][cur_col] -= k * Matrix[col][cur_col];
            }
        }
    }
}

void SwitchRows (double **Matrix, size_t N, size_t row1, size_t row2)
{
    if (row1 < N && row2 < N)
    {
        double *temp_row = Matrix[row1];
        Matrix[row1] = Matrix[row2];
        Matrix[row2] = temp_row;
    }
}

void SwitchCols (double **Matrix, size_t N, size_t col1, size_t col2)
{
    double temp = NAN;
    if (col1 < N && col2 < N)
    {
        for (size_t row = 0; row < N; row++)
        {
            temp = Matrix[row][col1];
            Matrix[row][col1] = Matrix[row][col2];
            Matrix[row][col2] = temp;
        }
    }
}

struct coordinates *MaxElemInCol (double **Matrix, size_t N, size_t col)
{
    double max = NULL_DOUBLE;
    struct coordinates *coord = calloc (1, sizeof (struct coordinates));
    coord->col = col;

    for (size_t row = 0; row < N; row++)
    {
        if (fabs (Matrix[row][col]) > max)
        {
            max = fabs (Matrix[row][col]);
            coord->row = row;
        }
    }
    
    return coord;
}

struct coordinates *MaxElemInMatrix (double** Matrix, size_t n, size_t N)
{
    double max = NULL_DOUBLE;
    struct coordinates *coord = calloc (1, sizeof (struct coordinates));

    for (size_t row = n; row < N; row++)
        for (size_t col = n; col < N; col++)
        {
            if (DoubleCompr (fabs(Matrix[row][col]), max, EPSILON) > 0)
            {
                max = fabs(Matrix[row][col]);
                coord->col = col;
                coord->row = row;
            }
        }    
    

    return coord;
}

int DoubleCompr (const double x, const double y, double EPS) //0 if equal
{
    if (fabs (x - y) < EPS)
        return 0;
    if (x - y < 0)
        return -1;
    return 1;
}



double DiagonalDet  (double **Matrix, size_t N)
{
    double det = 1.0;

    for (size_t i = 0; i < N; i++)
        det *= Matrix[i][i];
    return det;
}



void PrintMatrix (double **Matrix, size_t N)
{
    for (size_t row = 0; row < N; row++)
    {
        for (size_t col = 0; col < N; col++)
            printf ("%+.2f ", Matrix[row][col]);
        printf ("| %+.2f", Matrix[row][N]);
        printf ("\n");
    }
    printf ("\n");
}

double** StdinMatrixInit (size_t N)
{
    int res = 0;
    double** Matrix = 0;
    assert (N);
    Matrix = calloc (N, sizeof (double*));
    assert (Matrix);

    for (size_t i = 0; i < N; i++)
    {
        Matrix[i] = calloc (N + 1, sizeof (double));
        assert (Matrix[i]);
    }

    for (size_t row = 0; row < N; row++)
        for (size_t col = 0; col <= N; col++)
        {
            res = scanf ("%lf", Matrix[row] + col);
            assert (res);
        }
    return Matrix;
}

double **SLEmatrixInit (struct input *INP, int deg)
{
    double **Matrix = calloc (deg + 1, sizeof (double*));
    assert (Matrix);

    for (size_t i = 0; i <= deg; i++)
    {
        Matrix[i] = calloc (deg + 2, sizeof (double));
        assert (Matrix[i]);
    }

    for (size_t row = 0; row <= deg; row++)
    {
        for (size_t col = 0; col <= deg; col++)
        {
            Matrix[row][col] = Find_Ck (INP, col + row);
        }
        Matrix[row][deg + 1] = Find_Bk (INP, row);
    }
    return Matrix;
}





void DeleteMatrix (double** Matrix, size_t N)
{
    for (size_t i = 0; i < N; i++)
        free (Matrix[i]);
    free (Matrix);
}




//===========================================================================================
//===========================================Solve===========================================
//===========================================================================================



double Find_Ck (struct input *INP, size_t k)
{
    double Ck = NULL_DOUBLE;

    for (int i = 0; i < INP->N; i++)
    {
        Ck += pow (INP->x[i], (double)k);
    }
    return Ck;
}

double Find_Bk (struct input *INP, size_t k)
{
    double Bk = NULL_DOUBLE;

    for (int i = 0; i < INP->N; i++)
    {
        Bk += pow (INP->x[i], (double)k) * INP->y[i];
    }
    return Bk;
}


double *SolveSLE (struct input *INP, size_t deg)
{
    double *coefficients = calloc (deg + 1, sizeof(double));

    double **Matrix = SLEmatrixInit (INP, deg);

    Gauss_Jordan (Matrix, deg + 1);

    for (size_t i = 0; i < deg + 1; i++)
    {
        coefficients[i] = Matrix[i][deg + 1] / Matrix[i][i];
    }

    return coefficients;
}
