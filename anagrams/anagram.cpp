#include "anagram.h"

using namespace std;

vector<bool> Anagram::str1MapVect;
vector<bool> Anagram::str2MapVect;

bool Anagram::isAnagram(const std::string &str1, const std::string &str2)
{
    if(numberNeeded(str1, str2))
        return false;
    return true;
}

/*
 * Function numberNeeded(const string& a, const string& b) usues algorithm of mapping the alphabet.
 * There is a vector of 26 places which stands for each letter of alphabet (e.g. freq[0]
 * stands for 'a', freq[1] stands for 'b', etc.). The first for loop counts the occurances
 * of letters in the first string in ascending mode. The occurances in the second string
 * are counts in descending mode. Such algorithm allows to count which letters are
 * duplicated in two strings.
 */
int Anagram::numberNeeded(const std::string &str1, const std::string &str2)
{
    auto count = 0;
    vector<int> freq(26, 0);

    for (auto& c : str1) {
        ++freq[c - 'a'];
#ifdef DESCRIPTIONS
        cout << c << ", ++freq[" << c - 'a' << "] = " << freq[c - 'a'] << endl << endl;
#endif
    }
#ifdef DESCRIPTIONS
    cout << "======================\n";
    cout << "The map of letters is:\n";
    for(auto& c : freq) {
        cout << c << ", ";
    }
    cout << endl;
    cout << "======================\n";
#endif
    for (auto& c : str2) {
        --freq[c - 'a'];
#ifdef DESCRIPTIONS
        cout << c << ", --freq[" << c - 'a' << "] = " << freq[c - 'a'] << endl << endl;
#endif
    }
#ifdef DESCRIPTIONS
    cout << "======================\n";
    cout << "The map of letters is:\n";
    for(auto& c : freq) {
        cout << c << ", ";
    }
    cout << endl;
    cout << "======================\n";
#endif

    for (auto& val : freq) {
        count += abs(val);
    }
    return count;
}

void Anagram::makeAnagrams(std::string &str1, std::string &str2)
{
    str1MapVect.resize(str1.length(), false);
    str2MapVect.resize(str2.length(), false);

    size_t charPos;
    int i = 0;
    for(char c : str1) {
        charPos = str2.find_first_of(c);
        if(charPos != string::npos) {
            //character is found
            while(!markTheStrMaps(i, charPos)) {
                //Keep searching until meet npos or the character is found
                charPos = str2.find_first_of(c, charPos + 1);
                if(charPos == string::npos)
                    break;
            }
        }
        i++;
    }
    prepareAnagrams(str1, str2);
}

bool Anagram::markTheStrMaps(int i, size_t charPos)
{
    try {
        if(!str2MapVect.at(charPos)) {
            //The character was not checked so far in the str2MapVect.
            //Mark it as 'true' in the both string maps.
            str1MapVect[i] = true;
            str2MapVect[charPos] = true;
            return true;
        } else {
            //The charPos is already checked.
            //It is needed to continue searching in the str2 from next position (charPos + 1).
            return false;
        }
    } catch(out_of_range) {
        cout << "Out of range exception catched." <<endl;
        return false;
    }
}

void Anagram::prepareAnagrams(string &str1, string &str2)
{
    //String 1
    int i = 0;
    for(bool b : str1MapVect) {
        if(!b) {
            //Erase this character
            str1.erase(i,1);
        }
        i++;
    }

    //String 2
    i = 0;
    for(bool b : str2MapVect) {
        if(!b) {
            //Erase this character
            str2.erase(i,1);
        }
        i++;
    }
}
