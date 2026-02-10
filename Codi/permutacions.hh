#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <set>
#include <random>
#include <stdexcept>


using namespace std;

vector<string> dividirEnPalabras(const string &texto);
string permutarDocumento(const vector<string> &palabras);
vector<string> generarDocumentos(const string &documentoBase, int numeroDocumentos);