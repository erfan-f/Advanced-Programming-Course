#include <vector>
#include <memory>
#include <string>

using namespace std;

const char PLUS_MARK = '+';
const char OR_OPERATOR = '|';
const char XOR_OPERATOR = '^';
const char SPACE = ' ';

enum FeatureType {MANDATORY, OPTIONAL, OR, XOR};

class Node
{
protected:
    FeatureType type;
    vector<shared_ptr<Node>>  children;
    shared_ptr<Node> parent = nullptr;
public:
    Node();
    Node(const FeatureType& _type);
    virtual string getName() const = 0;
    void addAchild(shared_ptr<Node> _child);
    void setParent(shared_ptr<Node> _parent);
    FeatureType getType();
    vector<shared_ptr<Node>> getChildren(); 
    shared_ptr<Node> getParent();
};

class SingleNode : public Node
{
private:
    string name;

public:
    SingleNode(const FeatureType& _type, const string& _name);
    string getName() const override;
    
};

class SuperNode : public Node
{
private:
    vector<shared_ptr<SingleNode>> siblingsNode;
public:
    SuperNode(const FeatureType& _type, const vector<string>& _nodesName);
    string getName() const override;
    vector<shared_ptr<SingleNode>> getSiblings();
};

