#include "processer.h"

PROCESSER_CONF p_conf= {NULL,0,0};

/**
 * Inits the processer scheme
 * Call this function before create threads madly
 * If this function is not called the shceme will not work
 * You are forewarned
 */
int init_processer(int limit)
{
    p_conf.init = 1;
    p_conf._limit = limit;
}
static int pnext(){
