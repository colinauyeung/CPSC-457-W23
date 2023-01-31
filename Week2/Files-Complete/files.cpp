//Note: These are not C/C++ libraries, these are linux system calls!
#include <fcntl.h>
#include <unistd.h>

#include <iostream>
#include <string.h>
#include <stdio.h>

int main(){

    //Let's declare the file names as C strings first
    char file_read[] = "effect.txt";
    char file_write[] = "response.txt";

    //We're first going to open effect.txt to read from it!
    //For open, in this case we need to supply it with two things:
    //  1. the filename
    //  2. Our access mode + any other flags we may need (for full reference, check out the main page)
    //In this case, we're just reading from the file, so we'll open it with "Read only" access
    //Other thing to note, when we're opening file openning like this, we're actually directly working with linux system calls which means:
    //  1. This is linux specific (although is likely the same with other unix systems)
    //  2. In terms of references, we have to work with the linux man pages
    //  3. We're working at a low enough level at this point that what we're getting back is the raw file descriptors (meaning we don't get anything fancy with work with the files)

    //Other note for reference: our flag arguements are actually macros for specific bit strings which when we get into combining flags, all we're going to do with bit mask them together

    //https://man7.org/linux/man-pages/man2/open.2.html 
    int r_fd = open(file_read, O_RDONLY);


    //We're going to make a buffer to store the character we read from the file
    char buf[20];

    //Now we're going to read information from the file now!
    //So what we supply to read is the file descriptor we got from open, a pointer to the buffer we want to store things in and how big that buffer is (or rather how many bytes we want to read)
    //What read returns is the actual number of bytes we read. This is important!
    //  1. This tells us when we've reached the end of the file (if we read 0 bytes)
    //  2. We might not always get all the bytes we asked for (if there are not enough left for example)
    int res = read(r_fd, buf, 20);

    //We'll loop until we're out of bytes in the file
    while(res != 0){

        //Let's print out the bytes we read
        for(int i = 0; i<res; i++){
            //Note: we can't just treat the buffer as a string! It's likely not going to be null terminated correctly!
            printf("%c", buf[i]);
        }

        //Finally we'll read the next section from the file
        res = read(r_fd, &buf, 20);
        
    }    

    //REMEMBER TO CLOSE YOUR FILES!!
    close(r_fd);

    //Next let's open a file to write to!
    //In case we need to supply more flags to get the behaviour we want
    //      O_RDWR: We want the file in read and write mode
    //      O_CREAT: We want the OS to create the file if it doesn't exist
    //      O_TRUNC: If the file exists, for this case, let's have it delete what's already in there
    //Notice that we're bit or-ing the flags together!
    // One other important things is that if we're using O_CREAT, we also need to specify what permissions the created file should have!
    //      This is handled by S_IRWXU which gives the file full user permissions    
    int w_fd = open(file_write, O_RDWR | O_CREAT | O_TRUNC, S_IRWXU);
    
    //Here we're declaring the string we want to write
    char response[] = "Well Hello There\n";

    //And then write it (we need to give it the file descriptor to write to, the buffer containing the string we want to write and the number of bytes in that string)
    //Note, we're using strlen here to get the length of the string, this does not include the null terminator! So we are not writing it to the file.
    res = write(w_fd, response, strlen(response));
    std::cout << res << std::endl;


    //REMEMBER TO CLOSE YOUR FILES!!
    close(w_fd);

    return 0;
}