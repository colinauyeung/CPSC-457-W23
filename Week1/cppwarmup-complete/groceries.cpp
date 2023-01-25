#include<cstdio>
#include<iostream>
#include<vector>
#include<string>
#include<stdlib.h>

#include<random>
#include<limits>
#include <iomanip>

/**Problem outline: We want to run a program that runs on the command that will keep tracks of our groceries in our fridge such that it can:
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
struct groceryItem{
    string name;
    int quantity;
    int64_t serialNumber; 
};

// TODO: Create a class that manages our fridge
class fridge{
    private:
        vector<groceryItem> items;
        serialNumberGenerator generator;
    public:
        string name;
        int add(string input, int quantity){
            for(auto& item: items){
                if(item.name.compare(input) == 0){
                    item.quantity = item.quantity + quantity;
                    return item.quantity;
                }
            }
            groceryItem newitem;
            newitem.name = input;
            newitem.quantity = quantity;
            newitem.serialNumber = generator.generate64();
            items.push_back(newitem);
            return quantity;
        }

        int remove(string input, int quantity){
            for(auto& item: items){
                if(item.name.compare(input) == 0){
                    item.quantity = item.quantity - quantity;
                    if(item.quantity < 0){
                        int over = item.quantity;
                        item.quantity = 0;
                        return quantity + over;
                    }
                    return quantity;
                }
            }
            return 0;
        }

        void printItems(){
            for(auto item:items){
                cout << item.name << "\n\tquantity: " << item.quantity << "\n\tserial: ";
                generator.printhex(item.serialNumber);
                cout << endl;
            }
        }
};

// TODO: Write a function that transforms user inputs from strings to something usable

int checkcommands(string input){
    if(input.compare("add") == 0 || input.compare("Add") == 0){ return 0;}
    if(input.compare("remove") == 0 || input.compare("Remove") == 0){ return 1;}
    if(input.compare("report") == 0 || input.compare("Report") == 0){ return 2;}
    if(input.compare("exit") == 0 || input.compare("Exit") == 0){ return 3;}
    return -1;
}


int main(){
    serialNumberGenerator generator;
    fridge myFridge;
    myFridge.name = "Dyson";

    // TODO: Create our main program loop
    while(1){
        //TODO: Prompt the user to provide a command
        cout << "Please enter a command: ";
        string input;
        getline(cin, input);

        //TODO: Switch our behaviour given their command
        int command = checkcommands(input);
        switch(command){

            // TODO: Case for Add
            case 0: {
                cout << "What would you like to add: ";
                string name;
                getline(cin, name);
                cout << "How many would you like to add: ";
                string num;
                int intnum;
                while(1){
                    getline(cin, num);
                    try{
                        intnum = stoi(num);
                        break;
                    }
                    catch(exception& e){
                        cout << "Invalid number, please try again: ";
                    }
                }
                int added = myFridge.add(name, intnum);
                cout << "Added " << added << " " << name << endl;
            }
                break;

            // TODO: Case for Remove
            case 1:{
                cout << "What would you like to remove: ";
                string name;
                getline(cin, name);
                cout << "How many would you like to remove: ";
                string num;
                int intnum;
                while(1){
                    getline(cin, num);
                    try{
                        intnum = stoi(num);
                        break;
                    }
                    catch(exception& e){
                        cout << "Invalid number, please try again: ";
                    }
                }
                int removed = myFridge.remove(name, intnum);
                if(removed == 0 && intnum != 0){
                    cout << "Could not remove as " << name << " does not exist" << endl;
                }
                else{
                    cout << "Removed " << removed << " " << name << endl;
                }
            }
                break;

            // TODO: Case for Report
            case 2:
                cout << "Reporting on the contents of fridge " << myFridge.name << ":" << endl;
                myFridge.printItems();
                cout << "End of Report" << endl;
                break;

            // TODO: Case for Exit
            case 3:
                cout << "Ending program......" << endl;
                return 0;

            // TODO: What if their command doesn't exist!
            default:
                cout << "Could not find command. Avaliable commands: add, remove, report, remove" << endl;
                break;
        }

        // ! break while we don't have anything in this loop
        // break;

    }
    return 0;
}