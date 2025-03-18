#include "normalizeText2.hh"
#include <cctype>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <unordered_set>

using namespace std;

// Mapa de reemplazo para caracteres con tilde y ñ
const unordered_map<unsigned char, char> TILDES = {
    {'á', 'a'}, {'é', 'e'}, {'í', 'i'}, {'ó', 'o'}, {'ú', 'u'},
    {'Á', 'A'}, {'É', 'E'}, {'Í', 'I'}, {'Ó', 'O'}, {'Ú', 'U'},
    {'ñ', 'n'}, {'Ñ', 'N'}
};

string detectarIdioma(ifstream &in) {
    int ca = 0, es = 0, en = 0;
    string word;
    char c;
    in.clear();
    in.seekg(0);
    
    while (in.get(c)) {
        unsigned char uc = static_cast<unsigned char>(c);
        
        // Normalizar tildes y ñ
        if (TILDES.count(uc)) {
            uc = TILDES.at(uc);
        }
        
        uc = tolower(uc);

        if (isalnum(uc)) {  // Permitir letras y números
            word += uc;
        } else if (!word.empty()) {
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
        unsigned char uc = static_cast<unsigned char>(c);

        // Normalizar caracteres especiales
        if (TILDES.count(uc)) {
            uc = TILDES.at(uc);
        }

        uc = tolower(uc);

        if (isalnum(uc)) {  // Evitar caracteres especiales
            word += uc;
        } else if (!word.empty()) {
            if (!stopwords->count(word)) {
                if (!result.empty()) result += " ";  // Evita espacios dobles
                result += word;
            }
            word.clear();
        }
    }

    // Agregar la última palabra si existe
    if (!word.empty() && !stopwords->count(word)) {
        if (!result.empty()) result += " ";
        result += word;
    }
    
    return result;
}


