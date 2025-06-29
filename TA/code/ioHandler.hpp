#ifndef IOHANDLER
#define IOHANDLER

#include <queue>
#include <sstream>
#include <algorithm>

#include "orderedSet.hpp"
#include "tree.hpp"

const string STEP_MARKER_SMALL = "#";
const string STEP_MARKER_MEDIUM = "##";
const string STEP_MARKER_LARGE = "###";

const string VALID = "Valid";
const string INVALID = "Invalid";
const string CONF_SEPARATOR = "+++";

const string ERROR_MESSAGE = "Bad Description! Build Your Tree Again.";


const char EQUAL_SIGN = '=';
const char QUESTION_MARK = '?';
const char OPEN_BRACE = '{';
const char CLOSE_BRACE = '}';
const char ITEM_SEPARATOR = ',';




class IoHandler
{
private:
    queue<string> outputQueue; 
    FeatureTree tree;

public:
    void gettingInput();
    void constructTree(string line);
    void inputFeaturesDescription();
    void inputConfigurationList();
    void processFeatureDescription(const string& desc);
    void processMultipleChildren(const string& temp, const string& parentName);
    void processSingleChildExpression(const string& temp, const string& parentName);
    void printOutput();
    string removeSpaces(string str);
    bool isValidFeatureName(const string& name);


};


#endif