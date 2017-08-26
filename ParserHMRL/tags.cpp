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

    if(!(it->second).isAttrName(searchedAttrName))
        return "Not Found!";

    return (it->second).getAttrValue(searchedAttrName);
}

bool Tags::putData(stringstream& ss) {
    char actualTagName[maxNameSize];
    char actualAttrName[maxNameSize];
    char actualAttrValue[maxNameSize];
    char actualCheckTagName[maxNameSize];
    string sFinalTagName;// sActualTagName;
    char ch;

    //token giving info if it is nested tag or not. If so, append tags until end of tag is met.
    bool isNestedTag = false;

    Attribute* pAttr = NULL;
    unordered_map<std::string, Attribute> tempMapOfTags;
    stack<string> stackOfTagNames;

    stringstream msg;
    token tok = leftSharpExpected;

    //there should be a while loop working until end of token is met
    while(tok != endOfTag) {
        switch(tok) {

        case leftSharpExpected:
        {
            ignoreExtraSigns(ss);
            ss.get(ch);
            if(ch == '<') {
                if(ss.peek() == '/'){
                    ss.ignore();
                    tok = endOfTagExpected;
                } else {
                    tok = tagNameExpected;
                    if(!stackOfTagNames.empty())
                        isNestedTag = true;
                }
            } else {
                msg << "Syntax is incorrect: '<' is expected!\n";
                throw msg.str();
            }
            break;
        }

        case tagNameExpected:
        {
            ignoreExtraSigns(ss);
            ss.get(ch);
            string sActualTagName;
            sActualTagName += ch;
            while(ch != ' ' && ch != '>') {
                ss.get(ch);
                if(ch == '>') {
                    if(!pAttr) {
                        pAttr = new Attribute("", "");
                    }else {
                        pAttr->insertAttribute("", "");
                    }

                    //SAVE TAG
                    putNewTag(tempMapOfTags, sActualTagName, *pAttr);
                    pAttr = clearActualData(pAttr);
                    stackOfTagNames.push(sActualTagName);
                    tok = emptyTagToken;
                    break;
                }
                if (ch != ' ')
                    sActualTagName += ch;
            }
            if(tok == emptyTagToken) {
                sActualTagName.clear();
                tok = leftSharpExpected;
                break;
            }

//            ss.getline(actualTagName, maxNameSize, ' ');
//            string sActualTagName(actualTagName);
            stackOfTagNames.push(sActualTagName);
            if(isNestedTag) {
                //                sFinalTagName = sPreviousTagName;
                sFinalTagName += ".";
                sFinalTagName += sActualTagName;
            } else {
                sFinalTagName = sActualTagName;
            }
            tok = attrNameExpected;
            break;
        }

        case attrNameExpected:
        {
            ignoreExtraSigns(ss);
            ss.getline(actualAttrName, maxNameSize, ' ');
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
            ss.getline(actualAttrValue, maxNameSize, '\"');
            tok = rightSharpOrNextAttrNameExpected;
            break;
        }

        case rightSharpOrNextAttrNameExpected:
        {
            ignoreExtraSigns(ss);
            if(ss.peek() == '>') {
                if(!pAttr) {
                    pAttr = new Attribute(actualAttrName, actualAttrValue);
                }else {
                    pAttr->insertAttribute(actualAttrName, actualAttrValue);
                }

                //SAVE TAG
                putNewTag(tempMapOfTags, sFinalTagName, *pAttr);
                pAttr = clearActualData(pAttr);
                ss.ignore();
                tok = leftSharpExpected;
            }else {
                if(!pAttr) {
                    pAttr = new Attribute(actualAttrName, actualAttrValue);
                }else {
                    pAttr->insertAttribute(actualAttrName, actualAttrValue);
                }
                tok = attrNameExpected;
            }
            break;
        }

        case endOfTagExpected:
        {
            if(!stackOfTagNames.empty()) {
                ignoreExtraSigns(ss);
                ss.getline(actualCheckTagName, maxNameSize, '>');

                if((stackOfTagNames.top()).compare(actualCheckTagName)) {
                    stringstream msg;
                    msg << "Syntax is incorrect: </" << actualCheckTagName << "> does not comply with </"
                        << stackOfTagNames.top() << ">!\n";
                    throw msg.str();
                }
                stackOfTagNames.pop();

                //Actualize actualTagName! If it was a.b.c, make it -> a.b (because c was just erased)
                size_t pos = sFinalTagName.rfind('.');
                if(pos != string::npos)
                    sFinalTagName.erase(pos);
                else {
                    sFinalTagName.clear();
                    mapOfTags = tempMapOfTags;
                    tok = canBeFinishedTag;
                    break;
                }
                tok = leftSharpExpected;
            } else {
                isNestedTag = false;
            }
        }

        case canBeFinishedTag:
        {
            ignoreExtraSigns(ss);
            if(ss.eof())
                tok = endOfTag;
            else
                tok = leftSharpExpected;
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
