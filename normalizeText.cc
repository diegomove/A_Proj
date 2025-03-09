#include "normalizeText.hh"
#include <fstream>
#include <string>
#include <cctype>

using namespace std;

string normalizeText(const string &text) {
    string result;
    bool lastWasSpace = false; 

    for (char c : text) {  
        if (ispunct(c)) {
            continue;  
        }
        if (isspace(c)) {
            if (!lastWasSpace) {
                result.push_back(' ');  
                lastWasSpace = true;
            }
        } else {
            result.push_back(tolower(c));  
            lastWasSpace = false;
        }
    }

    return result;
}

