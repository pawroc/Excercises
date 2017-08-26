#include "tags.h"

using namespace std;

Tags::Tags() : maxNameSize(30)
{

}

Attribute Tags::getAtribute(const string& tagName) {
    return Attribute("af", "bdf");
}

string Tags::getTag(const string& cmd) {
    size_t pos;
    pos = cmd.find('~');
    if(pos == string::npos) {
        stringstream msg;
        msg << "Command: " << cmd << " is incorrect. It should has following form: tag_name~attribute_name";
        throw msg;
    }

    string searchedTagName;
    searchedTagName = cmd.substr(0, pos);

    unordered_map<string, Attribute>::iterator it;
    it = mapOfTags.find(searchedTagName);

    if(it == mapOfTags.end())
        return "Not Found!";

    string searchedAttrName;
    searchedAttrName = cmd.substr(pos + 1);

    if((it->second).getAttrName() != searchedAttrName)
        return "Not Found!";

    return (it->second).getAttrValue();
}

bool Tags::putData(stringstream& ss) {
    char tagName[maxNameSize], attrName[maxNameSize], attrValue[maxNameSize], checkTagName[maxNameSize];
    string sAppendedTagName, sPreviousTagName("");
    char c, equalitySign;
    bool isNestedTag = false;   //token giving info if it is nested tag or not. If so, append tags until end of tag is met.
    unordered_map<std::string, Attribute> tempMapOfTags;
    stack<string> stackOfTagNames;
    stringstream msg;

    token tok = leftSharpExpected;

    //there should be a while loop working until end of token is met
    while(tok != endOfTag) {
        switch(tok) {

        case leftSharpExpected:
            ss.get(c);
            if(c != '<') {
                msg << "Syntax is incorrect: '<' is expected!\n";
                throw msg.str();
            }
            tok = tagNameExpected;
            break;

        case tagNameExpected:
            ss.getline(tagName, maxNameSize, ' ');
            if(sPreviousTagName.compare(tagName)) {
                string sTagName(tagName);
                stackOfTagNames.push(sTagName);
                if(isNestedTag) {
                    sAppendedTagName = sPreviousTagName;
                    sAppendedTagName += ".";
                    sAppendedTagName += tagName;
                }
            }else {
                msg << "The name " << tagName << " already exists! Tag names have to be unique!\n";
                throw msg.str();
            }
            tok = attrNameExpected;
            break;

        case attrNameExpected:
            ss.getline(attrName, maxNameSize, ' ');
            tok = equalitySignExpected;
            break;

        case equalitySignExpected:
            ss.get(equalitySign);
            if(equalitySign != '=') {
                msg << "Syntax is incorrect: '=' is expected!\n";
                throw msg.str();
            }
            ss.ignore();    //ignore space after '='
            tok = openingQuotationMarkExpected;
            break;

        case openingQuotationMarkExpected:
            ss.get(c);
            if(c != '\"') {
                msg << "Syntax is incorrect: opening '\"' is expected!\n";
                throw msg.str();
            }
            tok = attrValueExpected;
            break;

        case attrValueExpected:
            ss.getline(attrValue, maxNameSize, '\"');
            tok = rightSharpOrNextAttrNameExpected;
            break;

        case rightSharpOrNextAttrNameExpected:
            while(ss.peek() == '\n')
                ss.ignore();
            if(ss.peek() == '>')
                tok = rightSharpExpected;
            else if(ss.peek() == ' ') {
                tok = attrNameExpected;
                ss.ignore();
            }
            else {
                msg << "Syntax is incorrect: space or '>' is expected!\n";
                throw msg.str();
            }
            break;

        case rightSharpExpected:
            ss.get(c);
            if(c != '>') {
                msg << "Syntax is incorrect: '>' is expected!\n";
                throw msg.str();
            }
            tok = endOfTagOrNestedTagNameExpected;
            break;

        case endOfTagOrNestedTagNameExpected:
            while(ss.peek() == '\n')
                ss.ignore();
//            ss.get(c);
//            if(c != '\n') {
//                msg << "Syntax error: new line '\\n' sign is expected after '>'!";
//                throw msg.str();
//            }
            ss.get(c);
            if(c != '<') {
                msg << "Syntax is incorrect: '<' at the end of Tag is expected!\n";
                throw msg.str();
            }

            if(ss.peek() == '/') {
                //this is the end of Tag

                while(!stackOfTagNames.empty()) {
                    ss.ignore();
                    ss.getline(checkTagName, maxNameSize, '>');

                    if((stackOfTagNames.top()).compare(checkTagName)) {
                        //                    if(strcmp(checkTagName, stackOfTagNames.top())) {
                        stringstream msg;
                        msg << "Syntax is incorrect: </" << checkTagName << "> does not comply with </"
                            << stackOfTagNames.top() << ">!\n";
                        throw msg.str();
                    }
                    stackOfTagNames.pop();
                    if(ss.peek() == '\n')
                        ss.ignore();

                    if(ss.peek() == '<') {
                        ss.ignore();
                        if(ss.peek() != '/') {
                            msg << "Syntax is incorrect: there is lack of '/' sign in end of tag!\n";
                            throw msg.str();
                        }
                    }
                }

                if(isNestedTag)
                    putNewTag(tempMapOfTags, sAppendedTagName, attrName, attrValue);
                else
                    putNewTag(tempMapOfTags, tagName, attrName, attrValue);
                mapOfTags = tempMapOfTags;
                tok = endOfTag;
            } else {
                //there will be nested Tag
                isNestedTag = true;
                putNewTag(tempMapOfTags, tagName, attrName, attrValue);
                sPreviousTagName.assign(tagName);
                tok = tagNameExpected;
            }
            break;
        }
    }
    return true;
}

void Tags::printContent()
{
    cout << "============\n";
    cout << "  CONTENT   \n";
    cout << "============\n\n";

    for(auto& v : mapOfTags) {
        cout << v.first << ", " << v.second << "\n";
    }
}


