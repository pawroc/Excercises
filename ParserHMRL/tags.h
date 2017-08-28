#ifndef TAGS_H
#define TAGS_H

#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <sstream>
#include <cstring>
#include <stack>

#include "attribute.h"

class Tags {
private:
    enum token {
        leftSharpExpected, tagNameExpected, attrNameExpected, equalitySignExpected,
        openingQuotationMarkExpected, attrValueExpected, endOfTagExpected, canBeFinishedTag,
        endOfTagOrNestedTagNameExpected, endOfTags, rightSharpOrNextAttrNameExpected, emptyTagToken,
        tagNameOrEndOfTagExpected
    };

    const int maxNameSize;

    // <tag_name, pair<atr_name, value> >
    std::unordered_map<std::string, Attribute> mapOfTags;

    //It is help function for getTag(...). It returns a pair for found tag
    Attribute getAtribute(const std::string &tagName);

    void putNewTag(std::unordered_map<std::string, Attribute>& map, std::string tagName,
                   Attribute atr) {

        std::pair<std::string, Attribute> newTag(tagName, atr);
        map.insert(newTag);
    }

    void ignoreExtraSigns(std::stringstream &ss) {
        while(ss.peek() == ' ' || ss.peek() == '\n')
            ss.ignore();
    }

    Attribute* clearActualData(Attribute* ptr) {
        delete ptr;
        return NULL;
    }

public:
    Tags();
    //Function returns "Not found!" when given tag does not exist or "value" if found
    std::string getTag(const std::string& cmd);

    /* Put a given stringstream to the memory. The function checks (parse) first whether
     * given text comply with the pattern. If so, and cmd was correctly proceeded - the function
     * returns true. Else, it returns false. */
    bool putData(std::stringstream &ss);

    void printContent();
    bool isEmpty() { return mapOfTags.empty(); }
};
#endif // TAGS_H
