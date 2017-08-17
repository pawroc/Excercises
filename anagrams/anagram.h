#ifndef ANAGRAM_H
#define ANAGRAM_H

#include<string>
#include<iostream>
#include<vector>

//#define DESCRIPTIONS

class Anagram
{
private:
    static std::vector<bool> str1MapVect;
    static std::vector<bool> str2MapVect;

public:
    static bool isAnagram(const std::string& str1, const std::string& str2);
    static int numberNeeded(const std::string& str1, const std::string& str2);
    static void makeAnagrams(std::string& str1, std::string& str2);

private:
    static bool markTheStrMaps(int i, size_t charPos);
    static void prepareAnagrams(std::string& str1, std::string &str2);
};

#endif // ANAGRAM_H
