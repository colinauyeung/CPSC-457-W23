#include <cstdio>
#include <cstdlib>
#include <atomic>
#include <pthread.h>

/*

In this file, we're going to look at a really simple example of using Barriers to create combinations of single threaded and multithreaded code
All we're going to do in this file is print out some message to see where the code is single and multi threaded

*/

//First thing first, we need the barrier as a global variable, so that we can access it from each of the threads
pthread_barrier_t barrier;


//Next we'll have input struct for our threads
struct data{
    int id;
};

//Pretty straightfoward threaded function
void * thread_function(void * args){

    //Grab our variables from the argument struct
    struct data *in_args = (struct data *) args;
    int id = in_args->id;

    //So like we've seen before, raw code within our threaded function will be multithreaded!
    printf("Multitreaded code: Thread %d\n", id);

    //Next let's set up a single thread function
    //We'll start by waiting on the barrier.
    //The idea with the barrier is that all the threads will stop at the barrier and only
    //once all the threads have stopped at the barrier will the barrier release
    //and so after our barrier, all of our threads at the same place
    int flag = pthread_barrier_wait(&barrier);

    //Next we'll check the return value of the wait
    //We are guaranteed that the return value of the wait will be equal to PTHREAD_BARRIER_SERIAL_THREAD
    //for exactly one thread, thus we are guaranteed that one and only one thread will run the body of the if statement
    if(flag == PTHREAD_BARRIER_SERIAL_THREAD){
        printf("Single Threaded code: Thread %d\n", id);
    }

    //We're wait at another barrier so that our other threads don't go past our serial threads
    pthread_barrier_wait(&barrier);

    //...And we're back at multithreaded code
    printf("Multitreaded code: Thread %d\n", id);
    
    pthread_exit(NULL);
}

int main(){

    //Annnnd we'll need to intialize the barrier, pretty straightfoward
    //Just like for a mutex, it takes the pointer to the barrier, an option flag and then finally the number of threads
    //(so that our barrier knows how many threads it should wait for)
    pthread_barrier_init(&barrier, NULL ,4);

    pthread_t pool[4];
    struct data args[4];

    for(int i = 0; i<4; i++){
        args[i].id = i;
    }
    
    for(int i = 0; i<4; i++){
        pthread_create(&pool[i], NULL, thread_function, (void *) &args[i]);
    }
    
    for(int i=0; i<4; i++){
        pthread_join(pool[i], NULL);
    }

    
}