//C libraries
#include<cstdio>
#include<stdlib.h>

//C++ libraries (you should be aware of)
#include<iostream>
#include<vector>
#include<string>

//C++ libraries (take a look at them if you're curious)
#include<random>
#include<limits>
#include <iomanip>

/**Problem outline: We want to run a program that runs on the command line that will keep tracks of our groceries in our fridge such that it can:
        => Add new grocery items
        => Each grocery item has a unique 64 bit serial number
        => Increment or decrement the number of a given item
        => Report on what we currently have

    Based on this our program should accept the given commands:
        => Add: should allow us to a grocery item to our fridge (it should create the entry if we don't have it yet or increment that entry if it exists)
        => Remove: should allow us to remove a grocery item from our fridge (decrementing)
        => Report: should report to us what's in our fridge (and how much of that thing)
        => Exit: should exit our program
**/

// ? Setup namespace for std (I'll explain later!)
using namespace std;

/** 
* * A class for generating and printing 64bit serial numbers
* ? I'm not going to explain too much of this because it's slightly hack-y and not particularly relevant, so if you're interested look it up on your own time.
* ? The relevant libraries for this code in particular is random and iomanip if you're curious
* * Relevant functions
* generate64(): Returns a "random" 64 bit number
* printhex(int64_t x): prints x in hex 
**/
class serialNumberGenerator{
    private:
        default_random_engine generator;
    public:
        int64_t generate64(){
            uniform_int_distribution<int64_t> distribution (0, numeric_limits<int64_t>::max());
            return distribution(generator);
        }

        void printhex(int64_t a){
            char prev = cout.fill('0');
            auto prevwidth = cout.width(16);
            cout.width(16);
            cout << hex << uppercase;
            cout << a;
            cout << dec << nouppercase;
            cout.width(prevwidth);
            cout.fill(prev);

        }
};

// TODO: Create a struct that holds one grocery item

// TODO: Create a class that manages our groceries

// TODO: Write a function that transforms user inputs from strings to something usable

int main(){
    serialNumberGenerator generator;

    // TODO: Create our main program loop
    while(1){

        //TODO: Prompt the user to provide a command
        cout << "Hello World";

        //TODO: Switch our behaviour given their command
        int command = 0;
        switch(command){

            // TODO: Case for Add
            case 0:
                break;

            // TODO: Case for Remove
            case 1:
                break;

            // TODO: Case for Report
            case 2:
                break;

            // TODO: Case for Exit
            case 3:
                break;

            // TODO: What if their command doesn't exist!
            default:
                break;
        }

        // ! break while we don't have anything in this loop
        break;

    }
    return 0;
}