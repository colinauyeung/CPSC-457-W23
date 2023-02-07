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
    for(int i = 0; i<1024; i++){
        buff[i] = '\0';
    }

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

            //Same basic idea as from files.cpp, just iterating over the results
            for(int i = 0; i<1024; i++){
                
                //In this case since fgets doesn't return the number of bytes read, I'm just breaking when I find null character (which I've made sure to initalize the buffer to)
                //This just tells me when I've reached the end of the characters that have been read from the file
                if(buff[i] == '\0') break;

                //Next I'm going to check for the end of line, since in this cause I'm going to be printing lines instead of individual characters
                if(buff[i] == '\n'){
                    //This bit of code here, all I'm doing is checking the output of each line of ls has x in the fifth character (basically tell me if the file in that line is executable)
                    //In this case, I'm going to make it so that I only print such files
                    if(res.length() >= 4){
                        if(res[4] == 'x'){
                            std::cout << res << std::endl;
                        }
                    }

                    //Because I want to store each line in res one at a time, when I'm done with this line, we'll clear res
                    res.clear();
                }

                
                //IUf we've encountered a normal character, let's save it to res to be handled when we reach the end of a line
                else{
                    res.push_back(buff[i]);
                }
                
            }

            //Finally when we've done with the output from the file, let's re-initalized our buffer before it gets refreshed with new stuff
            for(int i = 0; i<1024; i++){
                buff[i] = '\0';
            }
    }

    //MAKES SURE TO CLOSE YOUR FILES
    pclose(fp);
    return 0;
}