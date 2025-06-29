#include "tree.hpp"

FeatureTree::FeatureTree() : root(nullptr) {}

FeatureTree::FeatureTree(const FeatureType& rootType, const string& rootName)
 {
    root = make_shared<SingleNode> (rootType, rootName);
    nodes[rootName] = root;
}

void FeatureTree::addSingleFeature(const string& parent, const string& child, const FeatureType& type)
{
    if(nodes.find(parent) == nodes.end()) 
        return;
    shared_ptr<SingleNode> childNode = make_shared<SingleNode> (type, child); 
    nodes[parent]->addAchild(childNode);
    childNode->setParent(nodes[parent]);
    nodes[child] = childNode;
}

void FeatureTree::addSuperFeature(const string& parent, const vector<string>& children,const  FeatureType& type)
{
    if(nodes.find(parent) == nodes.end()) 
        return;
    shared_ptr<SuperNode> SupNode = make_shared<SuperNode> (type, children);
    nodes[parent]->addAchild(SupNode);
    for (const auto& sib : SupNode->getSiblings())
    {
        nodes[sib->getName()] = sib;
        sib->setParent(nodes[parent]);
    }
}


bool FeatureTree::requestValidation(const OrderedSet& nodeList)
{
    if(!isRootValid(nodeList))
        return false;

    for(int i = 0; i < nodeList.getSize(); i++)
    {
        string nodeName = nodeList.getElementAt(i);
        if(!isNodeValid(nodeName, nodeList, i))
            return false;

        shared_ptr<Node> node = nodes[nodeName];
        vector<shared_ptr<Node>> children = node->getChildren();

        if(!validateChildren(children, nodeList))
            return false;
    }
    return true;
}

bool FeatureTree::isRootValid(const OrderedSet& nodeList)
{
    return nodeList.getElementAt(0) == root->getName();
}

bool FeatureTree::isNodeValid(const string& nodeName, const OrderedSet& nodeList, int index)
{
    if(nodes.find(nodeName) == nodes.end())
        return false;

    if(index > 0)
    {
        shared_ptr<Node> parent = nodes[nodeName]->getParent();
        if(!nodeList.search(parent->getName()))
            return false;
    }

    return true;
}

bool FeatureTree::validateChildren(const vector<shared_ptr<Node>>& children, const OrderedSet& nodeList)
{
    for(const auto& child : children)
    {
        if(!isChildValid(child, nodeList))
            return false;
    }
    return true;
}

bool FeatureTree::isChildValid(const shared_ptr<Node>& child, const OrderedSet& nodeList)
{
    FeatureType childType = child->getType();

    if(childType == MANDATORY)
    {
        return nodeList.search(child->getName());
    }
    else if(childType == OR)
    {
        return validateOrChild(child, nodeList);
    }
    else if(childType == XOR)
    {
        return validateXorChild(child, nodeList);
    }

    return true;
}

bool FeatureTree::validateOrChild(const shared_ptr<Node>& child, const OrderedSet& nodeList)
{
    shared_ptr<SuperNode> superChild = dynamic_pointer_cast<SuperNode>(child);
    vector<shared_ptr<SingleNode>> siblings = superChild->getSiblings();
    bool found = false;

    for(const auto& sib : siblings)
    {
        if(nodeList.search(sib->getName()))
        {
            found = true;
            break;
        }
    }
    return found;
}

bool FeatureTree::validateXorChild(const shared_ptr<Node>& child, const OrderedSet& nodeList)
{
    shared_ptr<SuperNode> superChild = dynamic_pointer_cast<SuperNode>(child);
    vector<shared_ptr<SingleNode>> siblings = superChild->getSiblings();
    int count = 0;

    for(const auto& sib : siblings)
    {
        if(nodeList.search(sib->getName()))
            count++;
    }

    return count == 1;
}

int FeatureTree::getFeatureCount() {return nodes.size();}

bool FeatureTree::isFeatureExists(string nodeName) {return nodes.find(nodeName) != nodes.end();}