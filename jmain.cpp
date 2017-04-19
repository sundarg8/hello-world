#include <iostream>
#include <stdlib.h>
#include "inc_this.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include "malloc.h"
#include "jemalloc.h"

using namespace std;

#define MAX_SZ_MALLOC ( (5000 * 1   ) + 0)
#define NUM_TRIES   ((1000 * 1) * 1)
int usr_num_tries;
int usr_num_threads;
int sz_malloc;

#define MAX_NUM_TRIES (1000  * 1000 * 100)
#define MAX_NUM_THREADS  50 //actual number provided by main args.

int myMalloc(long tid);
int display_jemalloc_version(void);

void *thr_malloc(void *threadid) {
   long tid;
   tid = (long)threadid;

   pf_ts_th(tid);

   myMalloc(tid);

   pf_te_th(tid);
   pthread_exit(NULL);
}


int main(int argc, char *argv[])
{
    int rc;
    int i;
    pthread_t threads[MAX_NUM_THREADS];

    usr_num_tries  = atoi(argv[2]);
    usr_num_tries = usr_num_tries * (NUM_TRIES / 2);

    sz_malloc  = atoi(argv[3]);
    usr_num_threads = atoi(argv[1]);


    pthread_attr_t attr;
    void *status;
    display_jemalloc_version();

    pf_ts();

    // Initialize and set thread joinable
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    for( i=0; i < usr_num_threads ; i++ ) {
        cout << "main() : creating thread, " << i << endl;
        rc = pthread_create(&threads[i], &attr, thr_malloc, (void *)i );
        if (rc){
            cout << "Error:unable to create thread," << rc << endl;
            exit(-1);
        }
    }

    // free attribute and wait for the other threads
    pthread_attr_destroy(&attr);

    for( i=0; i < usr_num_threads ; i++ ) {
        rc = pthread_join(threads[i], &status);

        if (rc){
            cout << "Error:unable to join," << rc << endl;
            exit(-1);
        }

        cout << "---Main v1: completed thread id :" << i ;
        cout << "  exiting with status :" << status << endl;
    }

    pf_te();
    getchar();
    cout << "Main: program exiting." << endl;
    pthread_exit(NULL);
}

int myMalloc(long tid)
{
    char *p[usr_num_tries];
    size_t sz = sizeof(size_t);
    unsigned int narenas = 0;

    for (int i =0 ; i < usr_num_tries ; i++) {
        p[i] = (char *)malloc (sz_malloc);
        p[i][0]= i;
    }
    for (int i =0 ; i < usr_num_tries ; i++) {
        free(p[i]);
    }


    for (int i =0 ; i < usr_num_tries ; i++) {
        p[i] = (char *)malloc (sz_malloc);
    }
    for (int i =0 ; i < usr_num_tries ; i++) {
        p[i][0]= i;
    }
    for (int i =0 ; i < usr_num_tries ; i++) {
        free(p[i]);
    }
    return 0;
}

int display_jemalloc_version(void)
{
    const char *j;
    size_t s = sizeof(j);
    mallctl("version", &j,  &s, NULL, 0);
    printf("tt_th version -- %s\n", j);
}

