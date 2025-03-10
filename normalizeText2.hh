#include <string>
#include <cctype> 
#include <fstream>
#include <unordered_set>
#include "stopwords.hh"


using namespace std;


string detectarIdioma(ifstream &in);
string normalizeText2(ifstream& in);