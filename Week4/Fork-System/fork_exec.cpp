
#include <unistd.h>
#include<sys/wait.h>
#include <cstdio>
#include <iostream>
#include <string.h>

int main(){

    pid_t id = fork();

    if(id == 0){ //Thjs is the child
        std::cout << "Child: " << "I am running!" << std::endl;
        std::cout << "Child: " << "Transforming into ps" << std::endl;
        char ps[] = "ps";
        char * arg[] = {ps ,NULL};
        execvp("ps", arg);
        std::cout << "Child: " << "I'm back!" << std::endl;
    }
    else{ //This is the parent
        std::cout << "Parent: I have started!" << std::endl;
        std::cout << "Parent: Waiting for Child to finish" << std::endl;
        wait(NULL);
        std::cout << "Parent: Child has finished!" << std::endl;
    }


    return 0;
}