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
    char ch, equalitySign;
    bool isNestedTag = false;   //token giving info if it is nested tag or not. If so, append tags until end of tag is met.
    unordered_map<std::string, Attribute> tempMapOfTags;
    stack<string> stackOfTagNames;
    stringstream msg;
    Attribute* pAttr = NULL;

    token tok = leftSharpExpected;

    //there should be a while loop working until end of token is met
    while(tok != endOfTag) {
        switch(tok) {

        case leftSharpExpected:
        {
            ignoreExtraSigns(ss);
            ss.get(ch);
            if(ch != '<') {
                msg << "Syntax is incorrect: '<' is expected!\n";
                throw msg.str();
            }
            tok = tagNameExpected;
            break;
        }

        case tagNameExpected:
        {
            ignoreExtraSigns(ss);
            ss.getline(tagName, maxNameSize, ' ');
            string sTagName(tagName);
            stackOfTagNames.push(sTagName);
            if(isNestedTag) {
                sAppendedTagName = sPreviousTagName;
                sAppendedTagName += ".";
                sAppendedTagName += tagName;
            }
            tok = attrNameExpected;
            break;
        }

        case attrNameExpected:
        {
            ignoreExtraSigns(ss);
            ss.getline(attrName, maxNameSize, ' ');
            tok = equalitySignExpected;
            break;
        }

        case equalitySignExpected:
        {
            ignoreExtraSigns(ss);
            ss.get(ch);
            if(ch != '=') {
                msg << "Syntax is incorrect: '=' is expected!\n";
                throw msg.str();
            }
            tok = openingQuotationMarkExpected;
            break;
        }

        case openingQuotationMarkExpected:
        {
            ignoreExtraSigns(ss);
            ss.get(ch);
            if(ch != '\"') {
                msg << "Syntax is incorrect: opening '\"' is expected!\n";
                throw msg.str();
            }
            tok = attrValueExpected;
            break;
        }

        case attrValueExpected:
        {
            ss.getline(attrValue, maxNameSize, '\"');
            tok = rightSharpOrNextAttrNameExpected;
            break;
        }

        case rightSharpOrNextAttrNameExpected:
        {
            ignoreExtraSigns(ss);
            if(ss.peek() == '>') {
                if(pAttr)
                    pAttr->insertAttribute(attrName, attrValue);
                    tok = endOfTagOrNestedTagNameExpected;
            }else if(ss.peek() == ' ') {
                ////////////////////////////////////////////////////////////////////////////////////////////
                pAttr = new Attribute(attrName, attrValue);
                tok = attrNameExpected;
            }else {
                msg << "Syntax is incorrect: space or '>' is expected!\n";
                throw msg.str();
            }
            ss.ignore();
            break;
        }

        case endOfTagOrNestedTagNameExpected:
        {
            ignoreExtraSigns(ss);
            ss.get(ch);
            if(ch != '<') {
                msg << "Syntax is incorrect: '<' at the end of Tag is expected!\n";
                throw msg.str();
            }

            if(ss.peek() == '/') {
                //this is the end of Tag
                if(!stackOfTagNames.empty()) {
                    ss.ignore();
                    ss.getline(checkTagName, maxNameSize, '>');

                    if((stackOfTagNames.top()).compare(checkTagName)) {
                        stringstream msg;
                        msg << "Syntax is incorrect: </" << checkTagName << "> does not comply with </"
                            << stackOfTagNames.top() << ">!\n";
                        throw msg.str();
                    }
                    stackOfTagNames.pop();
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
