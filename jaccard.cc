#include "jaccard.hh"




double calcula_interseccio(const unordered_set<string>& F1, const unordered_set<string>& F2){
    int elements_comuns = 0;
	unordered_set<string>::const_iterator it = F1.begin();
    unordered_set<string>::const_iterator it2 = F2.begin();

	while(it!= F1.end() && it2 != F2.end()){
		if((*it) > (*it2)){
			++it;
            ++it2;
		}
		else if(*it < *it2 ){
			++it;
		}
		else {
			++it;
			++it2;
			++elements_comuns;
		}
	}
	return elements_comuns;
}

double jaccard_similarity(const unordered_set<string>& A, const unordered_set<string>& B) {

    double elements_comuns = calcula_interseccio(A,B);
	return elements_comuns / (A.size() + B.size() - elements_comuns);
}