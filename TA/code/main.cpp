#include "ioHandler.hpp"
using namespace std;


/*
Assumptions: In this project, it is assumed that each line contains only one of the combinations (+, ^, or |)
for example, the combination (A = B | C + D) is not allowed.

It is assumed that +, which is the default mode, will result in the formation of single nodes(mandatory or optional),
while the combinations ^ and | will lead to the formation of super nodes.

The manually implemented OrderedSet data structure consists of a vector and a hash(unordered_set) to enable O(1) time complexity for 
search and insertion while preserving the insertion order of elements.

This project has been compiled using -std=c++20.

Erfan Falahati
SID: 810102491
*/

int main()
{
    IoHandler handler;
    handler.gettingInput();
    handler.printOutput();
    return 0;
}