#include<stdio.h>
#include<iostream>
#include<string>

int main(){

    //So we're saw in our fork_exec.cpp and fork_pipe.cpp how to run outside programs from within our program and catch their output
    //But of course in both examples it was a lot of work! We needed to set up forked processes and then replace on with the program and then set up pipes
    //It's just a lot...
    //So we actually have some functions that will handle all of that for us!

    //So system is doing basically exactly what we did in fork_exec.cpp (although under the hood it's actually quite a bit different in implementation)
    //It's just going to run whatever program we give it as a string and print the results to standard out
    //In this case we don't even have create the argument list! 
    system("ls -al");

    //On the other hand, if we want to catch the output like in fork_pipe.cpp, we'll have to do a bit more work...

    //First let's setup the command we want to run and buffer to put things into
    std::string command = "ls -al";
    char buff[1024];

    //Next I'm going to make a results string as a C++ style string
    std::string res = "";

    //Next we can use popen!
    //This basically does what we did in fork_pipe.cpp
    //What it's going to do is it's going to run the program we tell it to (in this cause "ls")
    //And we're given a file as an access point
    //This is both where it's going to give us the output of the program and where we can put things into if we wanted to communicate with the program
    //Note: This uses C style files which we'll talk about later
    auto fp = popen(command.c_str(), "r");

    //So we're going to use fgets here. This is basically read() but for C style files
    //Same basic calling convention, execpt different order of arguments and it will return NULL instead of 0 when it's done reading
    while(fgets(buff, 1024, fp) != NULL){
            res.assign(buff);
            if(res.length() >= 4){
                if(res[3] == 'x'){
                    std::cout << res;
                }
            }
            res.clear();
    }

    //MAKES SURE TO CLOSE YOUR FILES
    pclose(fp);
    return 0;
}