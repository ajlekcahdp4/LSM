#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main ()
{
    FILE *gp = popen ("gnuplot", "w");
    assert (gp);
    fprintf (gp, "set terminal png size 800, 600\nset output \"test.png\"\nplot sin(x) lc rgb \"red\", cos(x) lc rgb \"blue\"\n");    
    pclose (gp);
    return 0;
}