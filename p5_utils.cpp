#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include "p5_utils.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <stddef.h>

typedef unsigned int uint32_t;
typedef unsigned short uint16_t;
typedef unsigned char uint8_t;
#define TRUE 1
#define FALSE 0

extern int usr_num_threads, usr_num_tries, sz_malloc;
struct timespec arr_ts[50];
struct timespec arr_te[50];


clock_t start, end;
double cpu_time_used;
struct timespec ts = {0,0}, te = {0,0};

int pf_ts() {
    ts.tv_sec = 0; ts.tv_nsec = 0;
    te.tv_sec = 0; te.tv_nsec = 0;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return 0;
}

float pf_tt() {
    float tt;
    tt  = ((double)te.tv_sec + 1.0e-9*te.tv_nsec) - ((double)ts.tv_sec + 1.0e-9*ts.tv_nsec);
    //printf("\n\n ---> PROCESS   Time Taken : secs %0.6f , FOR  tries %4d,%03d , size %4d Time %0.6f \n\n", tt,  (usr_num_threads* usr_num_tries*2/1000), ((usr_num_threads* usr_num_tries*2)%1000), sz_malloc ,tt );
    printf("\n\n ---> PROCESS   Time Taken : secs          , FOR  tries %4d,%03d , size %4d Time %0.6f \n\n", (usr_num_threads* usr_num_tries*2/1000), ((usr_num_threads* usr_num_tries*2)%1000), sz_malloc ,tt );
    return tt;
}

float pf_te() {
    clock_gettime(CLOCK_MONOTONIC, &te);
    return pf_tt();
}


int pf_ts_th(long tid) {
    arr_ts[tid].tv_sec = 0; arr_ts[tid].tv_nsec = 0;
    arr_te[tid].tv_sec = 0; arr_te[tid].tv_nsec = 0;
    clock_gettime(CLOCK_MONOTONIC, &arr_ts[tid]);
    return 0;
}

float pf_tt_th(long tid) {
    float tt_th;
    tt_th  = ((double)arr_te[tid].tv_sec + 1.0e-9*arr_te[tid].tv_nsec) - ((double)arr_ts[tid].tv_sec + 1.0e-9*arr_ts[tid].tv_nsec);
    printf("\n\n ---> THREAD %2d Time Taken : secs %0.6f , FOR  tries %4d,%03d , size %4d \n\n", tid, tt_th , (usr_num_tries*2/1000), ((usr_num_tries*2)%1000), sz_malloc);
    return tt_th;
}

float pf_te_th(long tid) {
    clock_gettime(CLOCK_MONOTONIC, &arr_te[tid]);
    return pf_tt_th(tid);
}

int printTime()
{
    time_t now;
    struct tm *local;

    time (&now);
    local =  localtime(&now);
    printf("Time: %s", asctime(local));

    return 0;
}

int printHour()
{
    time_t now;
    struct tm *local;

    time (&now);
    local =  localtime(&now);
    int hr = (local->tm_hour-7 < 0) ? (24+local->tm_hour - 7) : (local->tm_hour -7);
    hr = ( hr > 11) ? (hr - 12) : hr;
    printf("Time %d:%d:%d\n", (hr),(local->tm_min),local->tm_sec);

    return 0;

}

int start_time;
int prt_cmd_list(int n, char *aptr[])
{
    while(--n > 0)
    {
        printf("%s ", *++aptr);
    }
    NL;
    return 0;
}
int pre_run(int argc, char *argv[])
{

     prt_cmd_list(argc, argv);
     printf(" **** Start of Run ***  at  ");
     printHour();
     start = clock();
     //sleep in secs.....  sleep(2);
    return 0;

}

int post_run()
{
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    printf("\n **** END of Run ***  at  ");
    printHour();
    return 0;

}
