#include "k-shingles.hh"



unordered_set<string> k_shingles(int k, string text){

	unordered_set<string> s;

	for(int i = 0; i < text.length()-k+1; i++){
		string piece;
		for(int j = 0; j < k; j++){
			piece.push_back(text[i+j]);	
		}
		s.insert(piece);
	}

	return s;
}