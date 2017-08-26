#ifndef ATTRIBUTE_H
#define ATTRIBUTE_H

#include <iostream>
#include <unordered_map>

class Attribute {
private:
    std::unordered_map<std::string, std::string> attributes;
    std::string attrName;
    std::string attrValue;

public:
    Attribute(std::string name = "Unknown", std::string value = "Unknown") {
        insertAttribute(name, value);
    }
    Attribute(const Attribute& orig) {
        attributes = orig.attributes;
        this->attrName = orig.attrName;
        this->attrValue = orig.attrValue;
    }

    std::string getAttrName() { return attrName; }
    std::string getAttrValue() { return attrValue; }
    std::string getAttrValue(std::string attrName) {
        std::unordered_map<std::string, std::string>::iterator it = attributes.find(attrName);
        if(it == attributes.end())
            return "Not Found!";
        return it->second;
    }

    void putAttribute(std::string name, std::string value) { attrName = name; attrValue = value; }

    void insertAttribute(std::string name, std::string value) {
        attributes.insert(std::pair<std::string, std::string>(name, value));
    }

    friend std::ostream& operator<< (std::ostream& os, Attribute& attr);
};

#endif // ATTRIBUTE_H
