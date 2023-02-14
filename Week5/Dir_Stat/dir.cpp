
#include <sys/types.h>
#include <dirent.h>
#include <sys/stat.h>

#include<stdio.h>
#include<string>
#include<deque>

#include<assert.h>

//    https://man7.org/linux/man-pages/man3/readdir.3.html
//    struct dirent {
//        ino_t          d_ino;        Inode number
//        off_t          d_off;        Not an offset;
//        unsigned short d_reclen;     Length of this record
//        unsigned char  d_type;       Type of file; not supported
//                                     by all filesystem types 
//        char           d_name[256];  Null-terminated filename 
//    };

//    https://man7.org/linux/man-pages/man2/lstat.2.html
//    struct stat {
//        dev_t     st_dev;         /* ID of device containing file */
//        ino_t     st_ino;         /* Inode number */
//        mode_t    st_mode;        /* File type and mode */
//        nlink_t   st_nlink;       /* Number of hard links */
//        uid_t     st_uid;         /* User ID of owner */
//        gid_t     st_gid;         /* Group ID of owner */
//        dev_t     st_rdev;        /* Device ID (if special file) */
//        off_t     st_size;        /* Total size, in bytes */
//        blksize_t st_blksize;     /* Block size for filesystem I/O */
//        blkcnt_t  st_blocks;      /* Number of 512B blocks allocated */
//        struct timespec st_atim;  /* Time of last access */
//        struct timespec st_mtim;  /* Time of last modification */
//        struct timespec st_ctim;  /* Time of last status change */


/*  In this file, we'll explore how to traverse directories as well as grab some basic information from a file
    In the comments above I've provided two of the structs that we'll be working with in this file. You don't need to do
    anything with these, these are defined in the libraries we're using.

    Note: This is an iterative solution which will not work will for Assignment 2. See Assignment hints for a recursive version.
*/


int main(int argc, char * argv[]){

    //Similar to other code we've seen over the course of the semster, I'm going to grab the input from the commandline
    //As is good practice, I'm going to check the number of arguments I've actually gotten from the command line
    //and error if it is not what I expect
    if(argc!=2){
        printf("Usage: ./dir <filename>\n");
        return 1;
    }


    //Next I'm going to set up two arrays, one for potential directories and the other files
    //The directories array will be used as a stack for the depth first search I'm going to use 
    //a little farther down to traverse the directories.
    
    //If you want to save the directories you encountered, you'll have to use a seperate data structure
    //as at the end of the traversal this array will be empty.
    std::deque<std::string> files;
    std::deque<std::string> directories;

    //grab the root of our traverse from our command line arguments. Note std::string will overloads the
    //assignment, so even though argv[1] is a c style string, std::string will convert it to a c++ string 
    std::string root = argv[1];

    //Let's set up the stack for DFS by adding root
    directories.push_back(root);

    //This is an implementation of DFS for traversing directories.
    //The basic idea is that we will keep adding directories to our stack as we encounter them
    //When check a directory, we'll take it off the stack
    //Thus when we have no more directories, we'll be done

    //What makes this DFS as opposed to BFS is that we'll always check the newest directory added 
    //(as opposed to in DFS where we'll want to check the first directory added first)
    //The swap is quite simple. I'll leave it as an exercise to you
    while(!directories.empty()){

        //Let's grab the top of our stack
        std::string mydir = directories.back();
        directories.pop_back();

        //We are going to try to open the path we encounter from this as a directory
        DIR * dir = opendir(mydir.c_str());

        //If works, then it's a directory
        if(dir){

            //Next let's iterate through all the things in side of this directory
            while(1){

                //Let's grab a thing from the directory
                //Note: each time we call readdir on dir, it will return a new thing in the directory until
                //      there is nothing left, in which case it will return NULL
                dirent * res = readdir(dir);

                //If readdir returned NULL, we're done checking this directory
                if(!res){
                    break;
                }

                //Grab the name
                std::string name = res->d_name;

                //If the name either "." or "..", we've encountered the twoi special elements of a directory
                //the path to the directory itself: "."
                //the path to the parent directory: ".."
                //Let's ignore these
                if(name.compare(".") == 0 || name.compare("..") == 0){
                    continue;
                }

                //We need to transform the name of the thing into an actual path that we can do things with
                std::string path = mydir + "/" + name;

                //Let's for now just assume that everything is a directory (we'll sort this out in the outside loop...)
                directories.push_back(path);
            }
            closedir(dir);
        }

        //If the directory we tried to open isn't actually a directory, let's assume it's a file
        //Now this isn't entire correct, there are things that are neither files nor directories, so we 
        //really should do extra checks, but I'll leave that as an exercise for you
        else{
            files.push_back(mydir);
        }
    }
   
    //Now that we've gotten all of our files...
    for(auto file: files){

        //I'm going to call stat to grab some stats about our files
        //Note unlike like readdir above which returns a struct
        //for stat, we need to allocate the struct first and then stat will write to it
        struct stat s;
        stat(file.c_str(), &s);

        //Let's grab the size out of the return struct (and do some type coersion)
        int64_t size = (int64_t) s.st_size;
        printf("%s %ld\n", file.c_str() ,size);
    }
    
}