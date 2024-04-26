#include "SMIterator.h"
#include "SortedMap.h"
#include <exception>

using namespace std;

void SMIterator::move() {
    while (current < length && array[current].first == NULL_TKEY)
    {
        current++;
    }
}


SMIterator::SMIterator(const SortedMap& m) :
    map(m) {
    this->current = 0;
    this->length = map.length;
    this->array = new TElem[this->length];
    this->k = 0;
    for (int i = 0; i < map.m; i++) {
        if (map.e[i] != map.deleted && map.e[i] != map.empty) {
            this->array[this->k++] = map.e[i];
        }
    }
    for (int i = 0; i < k - 1; i++) {
        if (!map.relation(this->array[i].first, this->array[i + 1].first)) {
            TElem aux;
            aux = this->array[i];
            this->array[i] = this->array[i + 1];
            this->array[i + 1] = aux;
        }
    }
    move();
}


void SMIterator::first() {
    current = 0;
    move();
}

void SMIterator::next() {
    if (!valid()) {
        throw std::exception();
    }
    current++;
    move();
}

bool SMIterator::valid() const {
    return (current < map.m);
}

TElem SMIterator::getCurrent() const {
    if (!valid()) {
        throw std::exception();
    }
    return map.e[current];
}