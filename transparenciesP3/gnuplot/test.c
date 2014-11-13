#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *fp;
    fp = popen("gnuplot", "w");
    fprintf(fp, "set terminal x11 persist\n");
    fprintf(fp, "plot sin(x)\n");
    //fprintf(fp, "e\n");
    fflush(fp);
    getc(stdin);
    return 0;
    pclose(fp);

}
