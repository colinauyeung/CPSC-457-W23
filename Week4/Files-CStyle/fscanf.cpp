#include <cstdio>
#include <string> 
#include <deque>

/*
    In this example, we'll see basically the same code as readingCfiles, except this time we'll use fscanf to save some coding. You should read that file if you haven't already
*/

struct Card{
    std::string name;
    int numofcopies;
    int cost;
};

struct Deck{
    std::deque<Card> cards;
    std::string name;
};

int main(int argc, const char* argv[]){
    if(argc != 2){
        printf("Error input needs to be file\n");
        return 0;
    }

    Deck deck;

    FILE * file = fopen(argv[1], "r+");
    char buffer[100];

    //Now instead of the other read functions, we can also use fscanf which is really sweet.
    //We're not doing a whole lot here, so I'll explain more in the next example
    fscanf(file, "%s", buffer);
    
    deck.name.assign(buffer);

    int ncopies;
    int cost;

    //Okay, so what fscanf does is that it reads exactly line from a file
    //Then we give it a format that we think the file will be in
    //In this case that format is: "<string> <int> <int>"
    //Based on that format, we also give it pointers to store that stuff in
    //It then tries to match that format with the characters in the string
    //and if finds matches for that format, it will convert and store that data into those pointers

    //In this case I'm telling to expect a string followed by two ints and then the pointers on where to store them when it finds them.
    //This can make parsing much easier!
    while(fscanf(file, "%s %i %i", buffer, &ncopies, &cost)==3){
        printf(buffer);
        Card card;
        card.name.assign(buffer);
        card.numofcopies = ncopies;
        card.cost = cost;
        deck.cards.push_back(card);
    }


    printf("%s\n", deck.name.c_str());
    for(int i = 0; i<deck.cards.size(); i++){
        printf("%s: %d %d\n", deck.cards[i].name.c_str(),deck.cards[i].numofcopies, deck.cards[i].cost);
    }

}