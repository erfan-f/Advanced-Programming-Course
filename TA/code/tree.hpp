#ifndef TREE
#define TREE
#include <iostream>
#include <unordered_map>

#include "orderedSet.hpp"
#include "node.hpp"


class FeatureTree
{
private:
    shared_ptr<Node> root = nullptr;
    unordered_map<string, shared_ptr<Node>> nodes;

public:
    FeatureTree();
    FeatureTree(const FeatureType& rootType, const string& rootName);
    void addSingleFeature(const string& parent, const string& child,const  FeatureType& type);
    void addSuperFeature(const string& parent, const vector<string>& children,const  FeatureType& type);
    bool requestValidation(const OrderedSet& nodeList);
    bool isRootValid(const OrderedSet& nodeList);
    bool isNodeValid(const string& nodeName, const OrderedSet& nodeList, int index);
    bool validateChildren(const vector<shared_ptr<Node>>& children, const OrderedSet& nodeList);
    bool isChildValid(const shared_ptr<Node>& child, const OrderedSet& nodeList);
    bool validateOrChild(const shared_ptr<Node>& child, const OrderedSet& nodeList);
    bool validateXorChild(const shared_ptr<Node>& child, const OrderedSet& nodeList);
    int getFeatureCount();
    bool isFeatureExists(string nodeName);

};

#endif