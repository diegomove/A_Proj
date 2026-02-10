#include "jaccard.hh"




double calcula_interseccio(const unordered_set<string>& F1, const unordered_set<string>& F2) {
    int elements_comuns = 0;
    for (const auto& elem : F1) {
        if (F2.find(elem) != F2.end()) { 
            ++elements_comuns;
        }
    }
    return elements_comuns;
}

double jaccard_similarity(const unordered_set<string>& A, const unordered_set<string>& B) {
    double elements_comuns = calcula_interseccio(A, B);
    double union_size = A.size() + B.size() - elements_comuns; 
    return union_size > 0 ? elements_comuns / union_size : 0.0; 
}