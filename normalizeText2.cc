#include "normalizeText.hh"
#include "stopwords.hh"
#include <fstream>
#include <string>
#include <unordered_set>
#include <cctype>

using namespace std;

string detectarIdioma(ifstream &in) {
    int ca = 0, es = 0, en = 0;
    string word;
    char c;
    in.clear();
    in.seekg(0);
    
    while (in.get(c)) {
        c = tolower(c);
        if (isalpha(c)) word += c;
        else if (!word.empty()) {
            if (stopwords_ca.count(word)) ca++;
            if (stopwords_es.count(word)) es++;
            if (stopwords_en.count(word)) en++;
            word.clear();
        }
    }
    
    if (ca > es && ca > en) return "ca";
    if (es > en) return "es";
    return "en";
}

string normalizeText2(ifstream &in) {
    string idioma = detectarIdioma(in);
    const unordered_set<string> *stopwords;
    
    if (idioma == "ca") stopwords = &stopwords_ca;
    else if (idioma == "es") stopwords = &stopwords_es;
    else stopwords = &stopwords_en;
    
    string result, word;
    char c;
    in.clear();
    in.seekg(0);
    
    while (in.get(c)) {
        c = tolower(c);
        if (isalpha(c)) word += c;
        else if (!word.empty()) {
            if (!stopwords->count(word)) result += word + " ";
            word.clear();
        }
    }
    return result;
}