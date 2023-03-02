#include <stdio.h>   
#include <pthread.h>  
#include <string> 
#include <unistd.h>   

/*

    In this file, we'll take a look at a really basic thread code. All this code does is create
    four threads which print out a thread id and a character name. Mostly just to show the structure
    of how to set up threads, give them some input, get them to run code and wait for them to finish. 

*/

// First thing, let's set up some data that we want to give to a thread
// So to use a function with a thread, we need to give the function a very specific
// call signature which only gives us a single input variable. 
// To get around this, we'll pass the thread a struct with the data we want the thread to have
struct input{
    int id;
    char name;
};

// Next up is the code that we actually want the threads to run
// So when we create threads, we give them a function to run
// The function that we want to give threads has to have a specific call signature
// it has to have the signature of "void * foo(void * arg)"
void * hello(void * args){

    // First things first, the input for our thread function is passed to us
    // as a void pointer. The data is there, we just need to convert it to something usable
    // We'll do this by just doing type coersion

    //Also note, we get the input as pass by reference, not pass by value
    struct input * in = ((struct input *) args);

    //Just grab the elements of the input struct into local variables
    int id = in -> id;
    int name = in -> name;

    //Do the print!
    printf("Hello my name is %c and my id is %d\n", name, id);

    //pthread_exit is how we exit out of threads because of this we don't
    //strictly need the "return null".

    //Also we could techinically use the argument of pthread_exit to give 
    //a return value, however most times we'll use other methods to do this instead
    pthread_exit(NULL);
    return NULL;
}

int main(){
    printf("Hello I'm parent \n");

    //Just use a variable to hold the number of threads
    int nthread = 4;

    //Next we'll set up array to store our threads and the respective data we'll
    //send to the threads 
    pthread_t pool[nthread];
    input inputs[nthread];

    //Now iterate through and generate the data we'll send to the threads
    //In this case, just an id number and a character name
    for(int i = 0; i<nthread; i++){
        inputs[i].id = i;
        inputs[i].name = 'a' + i;
    }

    //Next we'll need to iterate through and start each of our threads
    for(int i = 0; i<nthread; i++){

        //This creates the threads, so the arguments are:
        //  1: a pointer to the thread
        //  2: arguments, although for this course, we won't do much with this, so typically you'll see this as null
        //  3: the function we want the thread to run
        //  4: the data we want to give the thread as a single struct. Note, we need to type coerise this to a void pointer
        pthread_create(&pool[i], NULL, hello, (void *) &inputs[i]);
    }

    //Finally we'll join the threads. This just causes the parents to wait for all the
    //threads to finish
    for(int i = 0; i<nthread; i++){

        //Arguments for the join call are:
        //  1: the thread we want to wait for (note this is not a pointer!)
        //  2: again an options flag that we won't use for the most part.
        pthread_join(pool[i], NULL);    
    }
    
    
    printf("Hello I'm back as the parent\n");

}