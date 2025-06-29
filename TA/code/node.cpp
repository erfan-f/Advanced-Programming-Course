#include "node.hpp"

Node::Node() : parent(nullptr) {}
Node::Node(const FeatureType& _type): type(_type) {}

void Node::addAchild(shared_ptr<Node> _child) {children.push_back(_child);}


void Node::setParent(shared_ptr<Node> _parent) {parent = _parent;}


FeatureType Node::getType() {return type;}

vector<shared_ptr<Node>> Node::getChildren() {return children;} 

shared_ptr<Node> Node::getParent() {return parent;};

////////////////////////////////////////////////////////////////////////////////////////////////

SingleNode::SingleNode(const FeatureType& _type, const string& _name)
        : Node(_type) {name = _name;}

string SingleNode::getName() const {return name ;}

////////////////////////////////////////////////////////////////////////////////////////////////

SuperNode::SuperNode(const FeatureType& _type, const vector<string>& _nodesName)
    : Node(_type)
{
    for (const auto& name : _nodesName)
        siblingsNode.push_back(make_shared<SingleNode>(_type, name));
}


string SuperNode::getName() const 
{
    string result;
    char mark = (type == OR) ? OR_OPERATOR : XOR_OPERATOR;
    for (int i = 0; i < siblingsNode.size(); i++)
        result += siblingsNode[i]->getName() + SPACE; 

    return result;
}

vector<shared_ptr<SingleNode>> SuperNode::getSiblings()  {return siblingsNode;}