
#include <unistd.h>
#include <cstdio>
#include <iostream>
#include <string.h>

int main(){
    int a = 10;

    //Let's play with some forks!
    //Renember that forks duplicate the current process
    //So after the fork call, we'll actually have two processes running our code!
    //What fork returns depends on whether we're the parent process or not
    //      If we're the parent process, it returns the process id of the newly created child process
    //      If we're the child process, it returns 0
    pid_t id = fork();

    //Let's use an if to make our code run differently depending on if we're the parent or the child
    if(id == 0){ //This is the child
        std::cout << "Child: " << "The value of a is " << a << std::endl;
        sleep(1);

        //Remember that fork makes a copy of the process! This includes variables
        //While both process have the same variables if they were created before the fork, these are copies of each other
        //These variables ARE NOT shared between the processes
        //We can share variables between processes, but we would have to do it explictly
        a = 20;
        std::cout << "Child: " << "I have changed the value of a to " << a <<std::endl;
    }
    else{ //This is the parent
        std::cout << "Parent: I have started!" << std::endl;
        std::cout << "Parent: The value of a is " << a << std::endl;
        std::cout << "Parent: I am sleeping" << std::endl;

        //Other note: Sleep IS NOT A GOOD SYCHRONIZATION METHOD. I'm doing it here to shortcut some stuff (and because this is just demo to show a behaviour), 
        //but we'll see later how to do this properly
        sleep(2);
        std::cout << "Parent: The value of a is " << a << std::endl;
    }


    return 0;
}