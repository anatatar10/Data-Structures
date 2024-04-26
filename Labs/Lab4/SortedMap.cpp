#include "SMIterator.h"
#include "SortedMap.h"
#include <exception>
#include <math.h>
using namespace std;

//symbolic constant that indicates a free location in the hash table

//function that gives the hashCode of an element
int hashCode(TKey k) {
    return abs(k);
}

//the hash function
int SortedMap::h(TKey k, int i) const {
    return (hashCode(k) % m + i * (1 + (hashCode(k) % (m - 1)))) % m;
}

SortedMap::SortedMap(Relation r) {
    //TODO - Implementation
    m = 1000;
    this->e = new TElem[this->m];
    this->relation = r;
    this->length = 0;
    this->deleted = std::make_pair(-111111, -111111);
    for (int i = 0; i < m; i++) {
        e[i] = NULL_TPAIR;
    }
}

void SortedMap::resize()
{
    int oldM = m;
    m = m * 2;
    TElem* oldE = e;
    e = new TElem[m];
    for (int i = 0; i < m; i++)
        e[i] = NULL_TPAIR;
    length = 0;
    for (int i = 0; i < oldM; i++) {
        TElem e1 = this->e[i];
        int j = 0;
        int pos = h(e1.first, j);
        while (j < this->m && e[pos] != this->empty) {
            if (e[pos].first == e1.first)
                break;
            j++;
            pos = h(e1.first, j);
        }
        e[pos].first = e->first;
        e[pos].second = e->second;

    }
    delete[] oldE;
}

bool SortedMap::rel(TKey c1, TKey c2)
{
    // the function will return true if "c1 <= c2", otherwise false

    if (c1 <= c2)
        return true;
    return false;

    //BC: θ(1);
    //WC: θ(1);
    //AC: O(1);
}

TValue SortedMap::add(TKey k, TValue v) {
    //TODO - Implementation

    if (this->length == this->m) {
        resize();
    }
    int i = 0;
    int index = h(k, i);
    while (i < this->m && this->e[index] != NULL_TPAIR && this->e[index] != this->deleted && relation(k, e[index].first)) {
        if (this->e[index].first == k)
            break;
        i++;
        index = h(k, i);
    }
    TValue old = this->e[index].second;
    TElem newValue = std::make_pair(k, v);
    if (old == NULL_TPAIR.second || old == this->deleted.second) {
        this->length++;
        this->e[index] = newValue;
        return NULL_TVALUE;
    }
    else {
        this->e[index] = newValue;
        return old;
    }
}

TValue SortedMap::search(TKey k) const {
    //TODO - Implementation

    int i = 0;
    int index = h(k, i);
    while (i < this->m && this->e[index].first != k && this->e[index] != NULL_TPAIR && relation(k, e[index].first)) {
        i++;
        index = h(k, i);
    }
    if (i == this->m || this->e[index] == NULL_TPAIR)
        return NULL_TVALUE;
    return this->e[index].second;
}

TValue SortedMap::remove(TKey k) {
    //TODO - Implementation
    int i = 0;
    int index = h(k, i);
    while (i < m && e[index].first != NULL_TKEY && e[index].first != k && e[index] != NULL_TPAIR && relation(k, e[index].first)) {
        i++;
        index = h(k, i);
    }
    if (i == m || this->e[index] == NULL_TPAIR)
        return NULL_TVALUE;
    else {
        if (e[index].first == k) {
            TValue oldValue = e[index].second;
            e[index] = this->deleted;
            length--;
            return oldValue;
        }
    }
}

int SortedMap::size() const {

    return this->length;
}

bool SortedMap::isEmpty() const {

    return this->length == 0;
}

SMIterator SortedMap::iterator() const {
    return SMIterator(*this);
}

SortedMap::~SortedMap() {
    //TODO - Implementation
    delete[] this->e;
}