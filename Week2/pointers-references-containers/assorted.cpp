#include<iostream>


//Some other notes:
class myclass{
    public:
        //Static functions are functions within class that can be called without an instance of the object
        //  Note: We cannot use class variables inside a static function (none would exist because we don't have an instance!)
        static void print(){
            std::cout << "Hello World" << std::endl;
        }

};

void myprint(){

    //On the other hand static variables are variables that persist between calls to the function
    //Sort of like global variables
    static int a = 5;
    std::cout << a++ << std::endl;
}

//Remember that we need to add argc and argv if we want to get command line arguments in our program
int main(int argc, char * argv[]){
    for(int i =0 ; i<argc; i++){
        std::cout << argv[i] << std::endl;
    }
    myprint();
    
    //Calling a static function
    myclass::print();
}
