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
    Attribute() {}
    Attribute(std::string name, std::string value);
    Attribute(const Attribute& orig);

    bool isAttrName(std::string name);
    std::string getAttrValue(std::string attrName);

    void putAttribute(std::string name, std::string value);

    void insertAttribute(std::string name, std::string value);

    friend std::ostream& operator<< (std::ostream& os, Attribute& attr);
};

#endif // ATTRIBUTE_H
