#include<iostream>

using namespace std;


//The template notation allows us to create functions that work with multiple different variable types!
//For example, in this case we have a swap function that works with any varaible type!
//In this case, we use the generic variable type T, meaning that all variables of type T must be the same type
//We could also be more specifc about the type of variable type we want. For example using "int" instead of "class" would limit us to interger types
//We also add more generic types to this declaration, letting use multiple different variable types.
template <class T>
void myswap(T &a, T &b){
    
    //Since we declare the variables as references, what we actually get are alias of the passed values
    //This gives us "pass by reference" behaviour, ie. when we change the value of the variables instead the function, we also change the value of the variables passed as arguement
    T temp = a;
    a = b;
    b = temp;
    return;
}

int main(){
    
    //Every variable has two qualities that we can get: value and address
    int a = 4;
    int b = 7;
    cout << "The value of a is: " << a << endl;
    cout << "The address of a is: " << &a << endl;

    //Pointers are ways for us to store and manipulate address
    int * a_pointer = &a;
    cout << "The address that a_pointer points to is: " << a_pointer << endl;
    cout << "The value that a_pointers points to is: " << *a_pointer << endl;
    
    //Remember:
    // &: gets an address from a variable
    // \*: gets a value from a pointer 

    //Remember that C style arrays are just collections of memory!
    int arr[5] = {0,1,2,3,4};

    //
    cout << "When we print an array, we can see that it's just a pointer: " << arr << endl;
    cout << "Thus we can access array values in a number of different ways: " << endl;
    cout << "We can use array notation, arr[0]: " << arr[0] << endl;
    cout << "We can dereference the pointer, *arr: " << *arr << endl;
    cout << "We can even use pointer math to get other values, *(arr+2):" << *(arr+2) << endl;

    /*References are a more contained version of pointers
    *   There are a number of key differences between pointers and references:
            -References must be initalized on declaration
            -References cannot be changed once initalized
            -You cannot do math with references
        Thus references are sort of like alias for our variables
            -See swap function for a use-case of this
    */
    
    //Initalizing a reference
    int &a_ref = a;
    cout << "You can see that with references, we don't need to dereference them to get their value. The value of a_ref is: " <<a_ref << endl;


    //See above for detail on our swap function
    cout << "Before our swap: " << endl;
    cout << "The value of a is: " << a << endl;
    cout << "The value of b is: "  << b << endl;

    myswap(a,b);
    cout << "After our swap: " << endl;
    cout << "The value of a is: " << a << endl;
    cout << "The value of b is: "  << b << endl;

    string c = "Hello";
    string d = "World";

    cout << "Because we made our functions a template, we can use different variables types with our swap function!" << endl;
    cout << "Before our swap: " << endl;
    cout << "The value of c is: " << c << endl;
    cout << "The value of d is: "  << d << endl;

    myswap(c,d);

    cout << "After our swap: " << endl;
    cout << "The value of c is: " << c << endl;
    cout << "The value of d is: "  << d << endl;
}