#include "../lsm/lsm.h"

struct output_t
{
    char *script_name;
    char *picture_name;
    char *xlabel;
    char *ylabel;
    enum format fmt;
};

void gnuplot (struct output_t *out, char *input_name, struct lsm_t *LSM);