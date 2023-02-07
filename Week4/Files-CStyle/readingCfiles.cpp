#include <cstdio>
#include <string> 
#include <deque>

/*
    In this example, we'll discuss a few different things in terms of an example piece of code
    1. We'll at one way to deal with strings, particularly how to extract useful information from them
    2. We'll look at C style file streams, particularly fopen, fread, fgets and fclose

    So in terms of the example itself:
    I have a list for a Magic the Gathering deck stored in the file "deck.txt". This file in in the format:
        1. The first line is the name of the deck
        2. Each subsequent line represents a card in the format:
            <name of card>:<numbers of copies in deck>:<cost of card>

    From this file, I want to extract this decklist and transform into a data type that's useful for playing around in code with.
    ie. I want to have the deck list in a useful data structure
*/

//The very first thing we need to do is to create some data structures to hold the deck list in

//I'm going to have a struct for both individuals cards...
struct Card{
    std::string name;
    int numofcopies;
    int cost;
};

//... and the deck as a whole. These will be useful for store our information once we extract it from the text file
struct Deck{
    std::deque<Card> cards;
    std::string name;
};


//Next we have a function for breaking up the lines in our file which hold the card information
//While I could make this specific to this use case, I'm actually just going to write a generic string split method.
//Note: This should look really similar to the one you saw in Assignment 1!

//What the function will do is that it will break up the string based on the delimiter character and return the array of substrings after the string has been broken up
//Analogous to split() method in Python

//First off, we're going to return an array of strings which will be the parts of the string after being broken up by the delimiter
//Next we'll take in as arguments: the string to be broken up and a delimter character
std::deque<std::string> split (std::string line, char delimter){

    //Let's set up the results structure
    std::deque<std::string> res;

    //Next we'll use a string to contain each part we'll be outputting
    std::string current_word = "";

    //For character in the string
    for(char c:line){

        //If we have a delimter
        if(c == delimter){

            //Then we're at the end of this part of the string
            //So I'm going to check that we actually have a part (ie we're not encountering a double delimter)
            if(current_word.length() > 0){

                //Add this part to our results structure
                //NOTE: this passes the part by value, not by reference
                //      ie: the deque will create a copy of current_word and add it to the structure. If we change the original, the one in the deque will not
                res.push_back(current_word);
            }

            //Now we're done with this part
            current_word.clear();
        }

        //If we're not at a delimter, then should be a part of one of the parts
        else{
            current_word.push_back(c);
        }
    }

    //If we get to the end, we might not run into a delimter to the end, but we probably should add the last part anyways
    if(current_word.length() > 0){
        res.push_back(current_word);
    }
    return res;
}



int main(int argc, const char* argv[]){

    //First off we're going to grab the file name from the command line arguments
    //So we need to check that the numbers we got is the number we expect
    if(argc != 2){
        printf("Error input needs to be file\n");
        return 0;
    }

    Deck deck;


    //Next let's open the file!
    //Note: we really should check that the file exists first or if this errors. I'll leave this as an exercise to you.

    //fopen is the C wrapper for open, it gives a number of much nicer APIs for working with files over the straight file descriptor
    //https://cplusplus.com/reference/cstdio/fopen/ 
    FILE * file = fopen(argv[1], "r+");

    char c;

    //Note we probably don't have to do this as the object variable should already be initalized, but it's safer to do it anyways
    deck.name = "";

    //First we'll handle the name at the top of the file

    //This looks a lot like the "bad" code you got for assignment 1!
    //But fread is actually quite a bit different from read in one important way
    //it's a buffered read!
    // In the background, the code is doing the buffering that you did on assignment 1 in the background, so it can minimize the number of read calls it needs to make
    //Note: fread also takes in how big each "character" is, this is really useful when you're working with files in other text standards that may not be 1 byte per character (ie UTF-16)
    while(fread(&c, sizeof(char), 1, file) != 0){
        if(c != '\n'){
            deck.name.push_back(c);
        }
        else{
            break;
        }
    }

    char buffer[1024];
    std::string line = "";

    //Next we'll handle the rest of the lines of the file

    //But fread isn't all we get, we also get fgets
    //fgets is really nice to us, instead of just giving us the raw characters in the file
    //It does two special things
    //  1. It only reads until it either hits a newline or it reaches the number of specificed bytes (which ever comes first)
    //  2. It guarantee that our buffer will be null terminated (ie a proper string!)

    //Thus it will get one line from our file and return it as a proper string
    while(fgets(buffer, 1024, file) != NULL){

        //This is just quickly converting the C style string stored in buffer and storing it as a C++ style string in line
        line.append(buffer);

        //Let's split our line up by our delimter
        auto broken = split(line, ':');

        //We should error if this don't break up correctly
        if(broken.size() != 3){
            printf("File Malformed");
            return 0;
        }

        //Now we'll just grab each part and stick them in a card data structure
        Card card;
        card.name.assign(broken[0]);

        //Note stoi converts a C++ string into a int (if it can). We really should be doing error checking... 
        card.numofcopies = std::stoi(broken[1]);
        card.cost = std::stoi(broken[2]);
        deck.cards.push_back(card);

        //This just resets the stored string
        line.clear();
    }

    //REMEMBER TO CLOSE YOUR FILES
    fclose(file);

    //Calcuate some statistics
    int totalname = 0;
    int totalcost = 0;
    for(auto card:deck.cards){
        totalname = totalname + card.name.length();
        totalcost = totalcost + card.cost;
    }
    int avgname = totalname / deck.cards.size();
    int avgcost = totalcost / deck.cards.size();

    //Now let's write the statistics to a file!
    FILE * wfile = fopen("res.txt", "w+");

    //Writing to files is really easy with C style file streams since it's just like printing to screen
    fprintf(wfile, "Statstics for Deck: %s\n", deck.name.c_str());
    fprintf(wfile, "Average name length: %d\n", avgname);
    fprintf(wfile, "Average cost: %d\n", avgcost);

    //REMEMBER TO CLOSE YOUR FILES
    fclose(wfile);

    printf("%s\n", deck.name.c_str());
    for(int i = 0; i<deck.cards.size(); i++){
        printf("%s: %d %d\n", deck.cards[i].name.c_str(),deck.cards[i].numofcopies, deck.cards[i].cost);
    }

}