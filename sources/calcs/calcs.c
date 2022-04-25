#include <stdlib.h>
#include <stdio.h>
#include <math.h>

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


int DoubleCmp (double a, double b, double accuracy)
{
    if (accuracy < 0)
    {
        fprintf (stderr, "WARNING: sub zero accuracy, using absolute value of the accuracy given\n");
        accuracy = fabs (accuracy);
    }
    if (fabs(a - b) < accuracy)
        return 0;
    if (a - b > 0)
        return 1;
    return -1;
}