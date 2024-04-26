#pragma once

#include "SortedMultiMap.h"


class SMMIterator{

	friend class SortedMultiMap;
private:
	//DO NOT CHANGE THIS PART
	
	const SortedMultiMap& map;

	//TODO - Representation

	//The address of the current node in the SLL
	PNod current;

	SMMIterator(const SortedMultiMap& c);

public:
	void first();
	void next();
	bool valid() const;
   	TElem getCurrent() const;
};

