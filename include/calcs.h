//! return minimum element in array "arr" of size "size"
double _min (double *arr, size_t size);
//! return maximum element in array "arr" of size "size"
double _max (double *arr, size_t size);
//! return sum of ellements of array "a" of size "N"
double Sum (double *a, int N);
//! return sum of multiplications of elements of arrays "a" and "b" (both should be of size "N")
double SumMul (double *a, double *b, int N);
//! return sum of squares of elements in array "a" of size "N"
double SumSq (double *a, int N);
//! return 0 if equal, 1 if a > b and -1 if a < b
int DoubleCmp (double a, double b, double accuracy);