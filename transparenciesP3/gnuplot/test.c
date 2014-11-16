#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *fp;
    fp = popen("gnuplot", "w");
    fprintf(fp, "set terminal x11 persist\n");
    //fputs("set term svg\n", fp);
    //fputs("set out 'grafico.svg'\n", fp);
    
    // 2graficas superpuestas
    fprintf(fp, "plot 'grafica2d.data' with lines, 'grafica2d_2.data' with lines\n");
    
    fflush(fp);
    pclose(fp);
    //getc(stdin);
    return 0;

}
