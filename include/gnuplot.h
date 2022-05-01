#include "lsm.h"

struct output_inf
{
    char *script_name;
    char *picture_name;
    char *xlabel;
    char *ylabel;
    enum format fmt;
};

void gnuplot (struct output_inf *out, char *input_name, struct lsm_t *LSM);