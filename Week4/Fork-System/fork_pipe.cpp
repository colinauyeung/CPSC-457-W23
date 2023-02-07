#include <fcntl.h>
#include <unistd.h>
#include <cstdio>
#include <iostream>
#include <string.h>

int main(){

    //So our fork_exec.cpp example let us run "ps" from inside our program, but of course it's not super useful since it just prints to standard out
    //We can't really grab that information and do anything with it in that example
    //This example will show how to grab that information from ps!

    //Note since you won't need to do this exact thing in the assignments, I'm going to gloss over some of the details behind this code

    //The first thing we need to do is to make a pipe
    //Pipes here are exactly the same thing as what we talked about on the command line
    //They are just like real pipes! You can think of them as "files" with one point where we can write information into and another point we can read stuff out of
    int fd[2];
    pipe(fd);

    //Forking and seperating the child and parent code
    pid_t id = fork();
    if(id == 0){ //This is the child

        //With our child process, we're going to be running "ps" again
        //This means that our child process is going to be the process generating the information we want!
        //Then we want the child to the "write" end of the pipe, so let's close the read end of the pipe for the child
        close(fd[0]);

        //Now ti's great and all that we have a pipe for the child to write into, but we're running ps which we have no control of!
        //Namely, it doesn't know we have a pipe and will just write to standard out like it always does!
        //So what we're doing here is redirecting what our process thinks is standard out and replacing it with our pipe
        //Now when our process (ps included!) thinks it's writing to standard out, it'll really be writing to our pipe
        dup2(fd[1], 1);
        close(fd[1]);

        //And now let's just setup and replace the process code with ps
        char * args[] = {"ps", NULL};
        execvp("ps", args);

    }
    else{ 
        
        //So our parent is going to be processing the data from the child, we want it to have the read end of the pipe
        //So let's close the read end for the parent
        close(fd[1]);

        //Now given that the our child is writing to our pipe, we can actually just read from the pipe as if it was any other file!
        //We actually won't get 0 from read until our child closes it's end of the pipe (which in this case happens when it exits)
        char buf;
        while(read(fd[0], &buf, 1) != 0){
            if(buf!='\n'){
                printf("%c-", buf);
            }
            else{
                printf("\n");
            }
        }

        //Let's make sure to close everything before exiting
        close(fd[0]);

    }

    return 0;
}