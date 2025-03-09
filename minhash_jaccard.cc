#include "minhash_jaccard.hh"


double calcularSimilitudMinHash(const vector<int>& firma1, const vector<int>& firma2) {
  
    if (firma1.size() != firma2.size()) {
        cerr << "Error: Las firmas deben tener el mismo tamaño." << endl;
        return -1; 
    }

    int coincidencias = 0; 
    int t = firma1.size();

    for (int i = 0; i < t; ++i) {
        if (firma1[i] == firma2[i]) {
            ++coincidencias;
        }
    }

    return coincidencias/ (double)t;
}