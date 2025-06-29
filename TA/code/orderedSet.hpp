#ifndef ORDEREDSET
#define ORDEREDSET

#include <vector>
#include <string>
#include <unordered_set>

using namespace std;


class OrderedSet {
private:
    vector<string> elements;   
    unordered_set<string> hash; 

public:
    const string& getElementAt(int index) const;
    void insert(string value);
    bool search(string value) const;
    int getSize() const;
};

#endif