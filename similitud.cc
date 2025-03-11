#include "similitud.hh"

void simBetweenDocs(vector<vector<double>>& simDocs, int doc1, int doc2, double sim)
{
    simDocs[doc1][doc2] = sim;
    simDocs[doc2][doc1] = sim;
}