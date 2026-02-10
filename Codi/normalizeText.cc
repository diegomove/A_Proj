#include "normalizeText.hh"


using namespace std;

string normalize_Text(const string &text) {
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

