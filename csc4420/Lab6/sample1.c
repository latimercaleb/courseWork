#include<pthread.h>
#include<stdio.h>

#define NUM_THREADS 5

void *PrintHello(void *threadid)
{
    long tid;
    tid = (long)threadid;
    printf("Hello World! It's me, thread #%ld!\n", tid);
    pthread_exit(NULL);
}
int main (int argc, char *argv[])
{
	// create an array of thread struct instances with appropriate length
    pthread_t threads[NUM_THREADS];
    long t;
    for(t=0; t<NUM_THREADS; t++){
        printf("In main: creating thread %ld\n", t);
        // start a new thread and call the appropriate routine with. You need to handle errors.
        pthread_create(&threads[t],NULL,PrintHello,(void*)t);
        // args of the routine should be cast as (void *)t
    }
    /* Last thing that main() should do */
    pthread_exit(NULL); // not mandatory but is recommended
}
