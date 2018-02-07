/******************************************************************************
* 
* DESCRIPTION:

* Yksinkertainen pthread softa, jossa on muuan bugi. Selvitä mikä ja yritä ratkaista ongelma
* 
******************************************************************************/
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#define NUM_THREADS	5

void *PrintHello(void *threadid)
{
    int i;
    double myresult=0.0;
    printf("thread=%ld: starting...\n", (long)threadid);
    for (i=0; i<1000000; i++)
       myresult += sin(i) * tan(i);
    printf("thread=%ld result=%e. Done.\n",(long)threadid,myresult);
    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
    pthread_t threads[NUM_THREADS];
    int rc;
    long t;
    for(t=0;t<NUM_THREADS;t++)
    {
        printf("Main: creating thread %ld\n", t);
        rc = pthread_create(&threads[t], NULL, PrintHello, (void *)t);
        if (rc)
        {
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(-1);
        }
    }
    sleep(2);
    printf("Main: Done on not!.\n");
}