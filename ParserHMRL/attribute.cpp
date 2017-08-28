#include "attribute.h"

Attribute::Attribute(std::string name, std::string value) {
    insertAttribute(name, value);
}

Attribute::Attribute(const Attribute& orig) {
    attributes = orig.attributes;
}

bool Attribute::isAttrName(std::string name) {
    if(attributes.find(name) != attributes.end())
        return true;
    else return false;
}
std::string Attribute::getAttrValue(std::string attrName) {
    std::unordered_map<std::string, std::string>::iterator it = attributes.find(attrName);
    if(it == attributes.end())
        return "Not Found!";
    return it->second;
}

void Attribute::putAttribute(std::string name, std::string value) {
    for(auto &v : attributes) {
        std::cout << v.second << std::endl;
    }
}

void Attribute::insertAttribute(std::string name = "", std::string value = "") {
    attributes.insert(std::pair<std::string, std::string>(name, value));
}
