#include "orderedSet.hpp"

void OrderedSet::insert(string value)
{
    if(hash.find(value) == hash.end()) 
    {
        elements.push_back(value);
        hash.insert(value);
    }
}

bool OrderedSet::search(string value) const
 {
    return hash.find(value) != hash.end(); 
}

int OrderedSet::getSize() const  { return elements.size();}

const string& OrderedSet::getElementAt(int index) const { return elements.at(index);}