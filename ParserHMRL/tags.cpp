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
    string sActualTagName, sActualAttrName, sActualAttrValue;
    char actualAttrName[maxNameSize];
    char actualAttrValue[maxNameSize];
    char actualCheckTagName[maxNameSize];
    string sFinalTagName;// sActualTagName;
    char ch;
    int counter;

    //token giving info if it is nested tag or not. If so, append tags until end of tag is met.
    bool isNestedTag = false;

    Attribute* pAttr = NULL;
    unordered_map<std::string, Attribute> tempMapOfTags;
    stack<string> stackOfTagNames;

    stringstream msg;
    token tok = leftSharpExpected;

    //there should be a while loop working until end of token is met
    while(tok != endOfTags) {
        switch(tok) {

        case leftSharpExpected:
        {
            ignoreExtraSigns(ss);
            ss.get(ch);
            if(ch != '<') {
                msg << "Syntax error! There should be '<' sign!\n";
                throw msg;
            }
            tok = tagNameOrEndOfTagExpected;
            break;
        }

        case tagNameOrEndOfTagExpected:
        {
            pAttr = new Attribute();    //create a new empty attribute

            ignoreExtraSigns(ss);
            ss.get(ch);
            if(ch == '/') {
                tok = endOfTagExpected;
                break;
            }
            sActualTagName += ch;
            counter = 0;
            while(counter++ < maxNameSize) {
                //Get characters until space or '>'
                ss.get(ch);
                if(ch == '>') {                                         //the end of tag
                    putNewTag(tempMapOfTags, sActualTagName, *pAttr);   //insert attribute to the temp memory...
                    stackOfTagNames.push(sActualTagName);
                    if(!stackOfTagNames.empty()) {
                        //it is nested tag
                        sFinalTagName += "." + sActualTagName;
                    }else {
                        //it is not nested tag
                        sFinalTagName = sActualTagName;
                    }
                    sActualTagName.clear();                             //...clear the actual tag name string...
                    break;                                              //...and leave the same token, because now '<' is again expected.
                } else if(ch == ' ') {                                  //space -> attrName expected
                    tok = attrNameExpected;
                    break;
                }
                sActualTagName += ch;
            }
            break;
        }

        case attrNameExpected:
        {
            ignoreExtraSigns(ss);
            ss.get(ch);
            if(ch == '=') { //check if there is any attribute name. If no, throw exception
                msg << "Syntax error! There should be attribute name!\n";
                throw msg;
            }
            //There is any attribute name -> continue
            sActualAttrName += ch;
            counter = 0;
            while(counter++ < maxNameSize) {
                ss.get(ch);
                if(ch == ' ') {
                    tok = equalitySignExpected;
                    break;
                }else if(ch == '=') {
                    tok = openingQuotationMarkExpected;
                    break;
                }
                sActualAttrName += ch;
            }
            break;
        }

        case equalitySignExpected:
        {
            ignoreExtraSigns(ss);
            ss.get(ch);
            if(ch != '=') {
                msg << "Syntax error! There should be '=' sign!\n";
                throw msg;
            }
            tok = openingQuotationMarkExpected;
            break;
        }

        case openingQuotationMarkExpected:
        {
            ignoreExtraSigns(ss);
            ss.get(ch);
            if(ch != '\"') {
                msg << "Syntax error! There should be opening '\"' sign!\n";
                throw msg;
            }
            tok = attrValueExpected;
            break;
        }

        case attrValueExpected:
        {
            ignoreExtraSigns(ss);
            counter = 0;
            while(counter++ < maxNameSize) {
                ss.get(ch);
                if(ch == '\"') {
                    tok = rightSharpOrNextAttrNameExpected;
                    break;
                }
                sActualAttrValue += ch;
            }
            break;
        }

        case rightSharpOrNextAttrNameExpected:
        {
            ignoreExtraSigns(ss);
            if(ss.peek() == '>') {
                //SAVE TAG and delete pAttr
                ss.ignore();
                if(pAttr) { //if pAttr does not exist, create new and insert it
//                    pAttr = new Attribute();
                    if(!stackOfTagNames.empty()) {
                        //it is nested tag
                        sFinalTagName += "." + sActualTagName;
                    }else {
                        //it is not nested tag
                        sFinalTagName = sActualTagName;
                    }
                    pAttr->insertAttribute(sActualAttrName, sActualAttrValue);
                    putNewTag(tempMapOfTags,sFinalTagName, *pAttr);
                    stackOfTagNames.push(sActualTagName);
                    clearActualData(pAttr);
                    sActualTagName.clear();
                }else { //else just insert next attribut value to the existing attribute
                    pAttr->insertAttribute(sActualAttrName, sActualAttrValue);
                }
                sActualAttrName.clear();
                sActualAttrValue.clear();
                tok = leftSharpExpected;
            }else {
                //INSERT new attribute name and value to the existing attribute
                pAttr->insertAttribute(sActualAttrName, sActualAttrValue);
                sActualAttrName.clear();
                sActualAttrValue.clear();
                tok = attrNameExpected;
            }
            break;
        }

        case endOfTagExpected:
        {
            counter = 0;
            string endTagName;
            while(counter++ < maxNameSize) {
                ss.get(ch);
                if(ch == '>') {
                    break;
                }
                endTagName += ch;
            }
            if(!endTagName.compare(stackOfTagNames.top())) {
                //Comparing tag names are the same
                stackOfTagNames.pop();  //erase tag name from stack

                //Actualize actualTagName! If it was a.b.c, make it -> a.b (because c was just erased)
                size_t pos = sFinalTagName.rfind('.');
                if(pos != string::npos)
                    sFinalTagName.erase(pos);
                else {
                    sFinalTagName.clear();
                    //check whether it is end of file (commands) or not
                    ignoreExtraSigns(ss);
                    if(ss.eof()) {
                        mapOfTags = tempMapOfTags;
                        tok = endOfTags;
                    }
                    else
                        tok = leftSharpExpected;

                    break;
                }

                ignoreExtraSigns(ss);
                if(ss.peek() == '<') {
                    //there will be next command
                    tok = leftSharpExpected;
                }else {
                    //it is end of file, but to be certain - check it before finishing
                    tok = endOfTags;
                }
            }else {
                //Comparing names are not the same
                msg << "Syntax error! " << endTagName << " is not the same as " << stackOfTagNames.top() << "!\n";
                throw msg;
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
