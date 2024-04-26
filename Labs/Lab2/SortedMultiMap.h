#pragma once
//DO NOT INCLUDE SMMITERATOR

//DO NOT CHANGE THIS PART
#include <vector>
#include <utility>
typedef int TKey;
typedef int TValue;
typedef std::pair<TKey, TValue> TElem;
#define NULL_TVALUE -111111
#define NULL_TELEM pair<TKey, TValue>(-111111, -111111);
using namespace std;
class SMMIterator;
typedef bool(*Relation)(TKey, TKey);

class Node;

//We define the type PNode as being the address of a Node
typedef Node* PNod;

class Node
{
public:
    friend class SortedMultiMap;
    //constructor
    //Node(TKey c, PNod urm);
    Node(TElem e, PNod urm);
    TElem element();
    PNod next();
private:
    TElem e;
    PNod nextNode;
 
};

class SortedMultiMap {

private:
	//TODO - Representation
    
    //head is the address of the first node in the SLL
    PNod head;
    Relation relation;
    int length;

    friend class SMMIterator;
public:

    // constructor
    SortedMultiMap(Relation r);

    //relation 
    bool rel(TKey c1, TKey c2);

	//adds a new key value pair to the sorted multi map
    void add(TKey c, TValue v);

	//returns the values belonging to a given key
    vector<TValue> search(TKey c) const;

	//removes a key value pair from the sorted multimap
	//returns true if the pair was removed (it was part of the multimap), false if nothing is removed
    bool remove(TKey c, TValue v);

    //returns the number of key-value pairs from the sorted multimap
    int size() const;

    //verifies if the sorted multi map is empty
    bool isEmpty() const;

    // returns an iterator for the sorted multimap. The iterator will returns the pairs as required by the relation (given to the constructor)	
    SMMIterator iterator() const;

    // destructor
    ~SortedMultiMap();
};
