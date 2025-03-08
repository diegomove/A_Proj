#include "normalizeText.hh"
#include <fstream>
#include <string>
#include <cctype>

using namespace std;

string normalizeText(ifstream &in) {
    string result;
    bool lastWasSpace = false; 
    char c;

    while (in.get(c)) {  
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
