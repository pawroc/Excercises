#include <iostream>
#include "tags.h"
#include <sstream>

using namespace std;

ostream& operator<< (ostream& os, const Attribute& attr);
void test1();
void test2();

int main()
{
 //   test1();
    test2();

    return 0;
}

ostream& operator<< (ostream& os, Attribute& attr) {
//    os << attr.getAttrName() << ", " << attr.getAttrValue();
    return os;
}

void test1() {
    stringstream ss("<a value = \"GoodVal\">\n<b value = \"BadVal\" size = \"10\">\n</b>\n<c height = \"auto\">\n<d size = \"3\">\n<e strength = \"2\">\n</e>\n</d>\n</c>\n</a>");

    Tags tags;
    try {
        tags.putData(ss);
    } catch(string msg) {
        cout << "EXCEPTION\n\n";
        cout << msg << endl;
    }

    tags.printContent();

    cout << "========================\n\n";

    string s = tags.getTag("a~value");
    cout << "Attribute found: " << s << endl;

    s = tags.getTag("b~value");
    cout << "Attribute found: " << s << endl;

    s = tags.getTag("a.b~size");
    cout << "Attribute found: " << s << endl;

    s = tags.getTag("a.b~value");
    cout << "Attribute found: " << s << endl;

    s = tags.getTag("a.b.c~height");
    cout << "Attribute found: " << s << endl;

    s = tags.getTag("a.c~height");
    cout << "Attribute found: " << s << endl;

    s = tags.getTag("a.d.e~strength");
    cout << "Attribute found: " << s << endl;

    s = tags.getTag("a.c.d.e~strength");
    cout << "Attribute found: " << s << endl;

    s = tags.getTag("d~sze");
    cout << "Attribute found: " << s << endl;

    s = tags.getTag("a.c.d~size");
    cout << "Attribute found: " << s << endl;
}

void test2() {

    stringstream ss("<tag1 v1 = \"123\" v2 = \"43.4\" v3 = \"hello\"></tag1><tag2 v4 = \"v2\" name = \"Tag2\"><tag3 v1 = \"Hello\" v2 = \"World!\"></tag3><tag4 v1 = \"Hello\" v2 = \"Universe!\"></tag4></tag2><tag5><tag7 new_val = \"New\"></tag7></tag5><tag6><tag8 intval = \"34\" floatval = \"9.845\"></tag8></tag6>");

//    stringstream ss("<tag5><tag7 new_val = \"New\"></tag7></tag5>");
    Tags tags;
    try {
        tags.putData(ss);
    } catch(string msg) {
        cout << "EXCEPTION\n\n";
        cout << msg << endl;
    }

    tags.printContent();

    cout << "========================\n\n";

    string s = tags.getTag("tag1~v1");
    cout << "Attribute found: " << s << endl;

    s = tags.getTag("tag1~v2");
    cout << "Attribute found: " << s << endl;

    s = tags.getTag("tag1~v3");
    cout << "Attribute found: " << s << endl;

    s = tags.getTag("tag4~v2");
    cout << "Attribute found: " << s << endl;

    s = tags.getTag("tag2.tag4~v1");
    cout << "Attribute found: " << s << endl;

    s = tags.getTag("tag2.tag4~v2");
    cout << "Attribute found: " << s << endl;

    s = tags.getTag("tag2.tag3~v2");
    cout << "Attribute found: " << s << endl;

    s = tags.getTag("tag5.tag7~new_val");
    cout << "Attribute found: " << s << endl;

    s = tags.getTag("tag5~new_val");
    cout << "Attribute found: " << s << endl;

    s = tags.getTag("tag7~new_val");
    cout << "Attribute found: " << s << endl;

    s = tags.getTag("tag6.tag8~intval");
    cout << "Attribute found: " << s << endl;

    s = tags.getTag("tag6.tag8~floatval");
    cout << "Attribute found: " << s << endl;

    s = tags.getTag("tag6.tag8~val");
    cout << "Attribute found: " << s << endl;

    s = tags.getTag("tag8~intval");
    cout << "Attribute found: " << s << endl;
}
