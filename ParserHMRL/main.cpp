#include <iostream>
#include "tags.h"
#include <sstream>

using namespace std;

ostream& operator<< (ostream& os, const Attribute& attr);

int main()
{

    unordered_map<string,string> m;
    m.insert(pair<string,string>("abc","aaa"));
    m.insert(pair<string,string>("abd","bbb"));
    m.insert(pair<string,string>("abc","ccc"));

   string s;
   for(auto& a : m) {
        s = a.second;
        cout << s << endl;
    }
//    stringstream ss("<a value = \"GoodVal\">\n<b value = \"BadVal\" size = \"10\">\n</b>\n<c height = \"auto\">\n<d size = \"3\">\n<e strength = \"2\">\n</e>\n</d>\n</c>\n</a>");

//    Tags tags;
//    try {
//        tags.putData(ss);
//    } catch(string msg) {
//        cout << "EXCEPTION\n\n";
//        cout << msg << endl;
//    }

//    tags.printContent();

//    cout << "========================\n\n";

//    string s = tags.getTag("tag_name.tag_name2~attr_name2");

//    cout << "Attribute found: " << s << endl;

    return 0;
}

ostream& operator<< (ostream& os, Attribute& attr) {
    os << attr.getAttrName() << ", " << attr.getAttrValue();
    return os;
}
