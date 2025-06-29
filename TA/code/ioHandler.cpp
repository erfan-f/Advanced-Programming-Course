#include "ioHandler.hpp"


void IoHandler::gettingInput()
{
    string line;
    getline(cin, line);
    while(line != STEP_MARKER_LARGE)
    {

        constructTree(line);
        inputFeaturesDescription();
        inputConfigurationList();
        getline(cin, line);
    }

}

void IoHandler::constructTree(string line)
{
    stringstream ss1(line);
    string temp, rootName;
    FeatureType rootType = MANDATORY, childType;
    getline(ss1, temp, EQUAL_SIGN);
    rootName = removeSpaces(temp);

    FeatureTree newTree(rootType, rootName);
    tree = newTree;

    getline(ss1, temp, EQUAL_SIGN);
    if (temp.find(OR_OPERATOR) != string::npos || temp.find(XOR_OPERATOR) != string::npos)
    {
        processMultipleChildren(temp, rootName);
    }
    else
    {
        processSingleChildExpression(temp, rootName);
    }
}


void IoHandler::inputFeaturesDescription()
{
    string desc;
    getline(cin, desc);
    while(desc != STEP_MARKER_SMALL)
    {
        processFeatureDescription(desc);
        getline(cin, desc);
    }
}

void IoHandler::processFeatureDescription(const string& desc)
{
    stringstream ss(desc);
    string parentName, temp;

    getline(ss, temp, EQUAL_SIGN);
    parentName = removeSpaces(temp);

    
    getline(ss, temp, EQUAL_SIGN);
    if (temp.find(OR_OPERATOR) != string::npos || temp.find(XOR_OPERATOR) != string::npos)
    {
        processMultipleChildren(temp, parentName);
    }
    else
    {
        processSingleChildExpression(temp, parentName);
    }
}

void IoHandler::processMultipleChildren(const string& temp, const string& parentName)
{
    vector<string> children;
    FeatureType childType;
    char delimiter;

    if(temp.find(OR_OPERATOR) != string::npos)
    {
        childType = OR;
        delimiter = OR_OPERATOR;
    }
    else if(temp.find(XOR_OPERATOR) != string::npos)
    {
        childType = XOR;
        delimiter = XOR_OPERATOR;
    }

    stringstream ss2(temp);
    string expression, childName;
    while(getline(ss2, expression, delimiter))
    {
        childName = removeSpaces(expression);
        children.push_back(childName);
    }
    
    tree.addSuperFeature(parentName, children, childType);   
}


void IoHandler::processSingleChildExpression(const string& temp, const string& parentName)
{
    
    stringstream ss2(temp);
    string expression, childName;
    FeatureType childType;
    
    while(getline(ss2, expression, PLUS_MARK))
    {
        expression = removeSpaces(expression);

        if(expression[0] == QUESTION_MARK)
        {
            childType = OPTIONAL;
            childName = expression.substr(1);
        } 
        else
        {
            childType = MANDATORY;
            childName = expression;
        }

        tree.addSingleFeature(parentName, childName, childType);
    }
}


void IoHandler::inputConfigurationList()
{
    string confLine, temp, nodeName;
    getline(cin, confLine);
    while(confLine != STEP_MARKER_MEDIUM)
    {
        OrderedSet nodeSet;
        stringstream ss1(confLine);
        getline(ss1, temp, OPEN_BRACE);
        getline(ss1, temp, CLOSE_BRACE);
        stringstream ss2(temp);
        while(getline(ss2, temp, ITEM_SEPARATOR))
        {
            nodeName = removeSpaces(temp);
            nodeSet.insert(nodeName);
        }     
        outputQueue.push((tree.requestValidation(nodeSet)) ? VALID : INVALID);
        getline(cin, confLine);
    }
    outputQueue.push(CONF_SEPARATOR);
}


void IoHandler::printOutput()
{
    while(!outputQueue.empty())
    {  
        cout << outputQueue.front() << endl;
        outputQueue.pop();
    }
}

string IoHandler::removeSpaces(string str)
{
    str.erase(remove(str.begin(), str.end(), ' '), str.end()); 
    return str; 
}

bool IoHandler::isValidFeatureName(const string& name) {
    for (char c : name) {
        if (!isalpha(c)) return false;
    }
    return true;
}