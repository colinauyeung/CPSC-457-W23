#include<list>
#include<vector>
#include<set>
#include<unordered_map>
#include<iostream>

using namespace std;

//In this file, we'll look at a number of different C++ data structures!
int main(){

    //First up is vectors
    //Vectors are a C++ wrapper for arrays which gives us object orientated features
    //C++ has multiple array wrappers:
    //  -Arrays: like it says on the tin, just arrays wrapped with C++ object orientation
    //  -Vectors: Dynamically resizing arrays
    //  -Deques: Similar to vectors in usage, but with a different implementation under the hood

    //See: https://cplusplus.com/reference/vector/vector/
    cout << "Vectors: " << endl;
    vector<int> myvec = {0,1,2,3,4};
    //We can add to the vector using push_back
    myvec.push_back(5);

    //We can insert into the vector using iterators, explaination a little later
    auto vecit = myvec.begin();
    vecit = next(vecit, 3);
    myvec.insert(vecit, 3);

    cout << "Values in vec: " << endl;
    for(auto i:myvec){
        cout << i << ",";
    }
    cout << endl;

    //We can get values from vectors either using array notation or object notation
    cout << myvec[1] << endl;
    cout << myvec.at(1) << endl;

    //Next up is lists
    //Unlike vectors which are arrays, lists are doublely linked lists
    //This gives them two important differences:
    //      -Arrays have constant time value access, doubely linked lists have linear time value access
    //      -Arrays need linear time to add or remove elements, doubely linked lists only need constant time to add or remove elements
    //See: https://cplusplus.com/reference/list/ 
    list<int> mylist = {0,1,2,3,4};
    
    //We can add to the list similarly to vectors
    cout << endl << "Lists: " << endl;
    mylist.push_back(5);
    auto listit = mylist.begin();
    listit = next(listit, 3);
    mylist.insert(listit, 3);
    cout << "Values in list: " << endl;
    for(auto i:mylist){
        cout << i << ",";
    }
    cout << endl;

    cout << endl << "Iterators: " << endl;
    //Iterators are essentially wrapped pointers for C++ data structures
    //They give us access to elements within the data structure like pointers would with C arrays
    //We can do several things with iterators:
    //      -We can get the value of what the iterator points to using the \* operator
    //      -We can do (limited) math with iterators to move them around
    

    //Most data types give us access to two iterators
    //  The iterator to the start of the data structure
    auto it = mylist.begin();
    //  The iterator to the "end" of the data structure
    //      Note this is not the last element, but rather the hypothetical element after the last, ie. it's value does not exist!
    auto endit = mylist.end();

    //If we want the iterator to point to something else in the data structure, we can:
    //  We can increment and decrement them, this will move the iterator forward or backward one element
    it++;
    it--;
    //  Or we use next and prev
    it = next(it, 1); 
    it = prev(it, 1);

    //We can also use iterators to form a "For Each" style loop
    for(auto i = mylist.begin(); i!=mylist.end(); i++){
        cout << *i << ",";
    }
    cout << endl;


    //Sets are what they say on the tin, an implementation of mathematical sets
    //This means two things:
    //  -Values in sets are unique, ie. only one of each value is allowed in the set
    //  -Sets are sorted
    //See: https://cplusplus.com/reference/set/
    cout << endl << "Sets: " << endl;
    set<int> myset = {0, 10, 20, 30, 40};
    cout << "Values in set: " << endl;
    for(auto i: myset){
        cout << i << ",";
    }
    cout << endl;

    //We can try to add things with insert
    auto ret = myset.insert(20);
    
    // Insert returns a pair where:
    //  -the first value is the iterator to where value exists in the set
    //  -the second value is whether this value was added to the set by the call (true) or the value are already in the set (false) 
    cout << *ret.first << ";" << ret.second << endl;
    ret = myset.insert(27);
    cout << *ret.first << ";" << ret.second << endl;
    cout << "Values in set: " << endl;
    for(auto i: myset){
        cout << i << ",";
    }
    cout << endl;


    //Finally, we have maps
    //Maps are exactly that maps, similar to hashmaps in Java or dictionaries in python
    //They store element via a "key", this key is how we can access the elements
    //See: https://cplusplus.com/reference/unordered_map/
    cout << endl << "Maps: " << endl;
    unordered_map<string, int> mymap;
    //We can add to the map using the [] operator similar to python or Java
    mymap["Map"] = 5;
    //We can also use object style calls
    mymap.emplace("Map2", 5);

    //Note, we try to access a key that doesn't exist, C++ will just create the key with no value
    mymap["Great"] = mymap["Wall"];
    
    //Other note: unlike like python, when we use a for-each, C++ will give us pairs of keys and values.
    for(auto i:mymap){
        cout << i.first << ":" << i.second << endl;
    }

}
