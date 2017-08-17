/*
 * The project is about founding the anagrams. Two strings are anagrams of each other
 * if the first string's letters can be rearranged to form the second string.
 * In other words, both strings must contain the same exact letters in the same exact frequency.
 * For example, "bacdc" and "dcbac" are anagrams, but "bacdc" and "dcbad" are not.
 *
 * Function number_needed(const string& a, const string& b) counts how many letters are needed to be erased
 * in purpose to make those two strings anagrams of each other.
 */

#include "anagram.h"
#include <vector>
#include <iostream>

using namespace std;

int main(){
    string a("abacc");
    cout << "string a -> " << a << endl;
//    //    cin >> a;
    string b("cdacb");
    cout << "string b -> " << b << endl;
//    //    cin >> b;
    cout << Anagram::numberNeeded(a, b) << endl;
//    if(Anagram::isAnagram(a,b)) cout << "Yes" << endl;
//    else cout << "NO" << endl;
    Anagram::makeAnagrams(a,b);
    cout << "String a: " << a << '\n'
         << "String b: " << b << endl;

    return 0;
}
