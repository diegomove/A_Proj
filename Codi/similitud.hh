#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void simBetweenDocs(vector<vector<double>>& simDocs, int doc1, int doc2, double sim);

vector<pair<double,int>> consultarMaxSim(int doc, int numDocsSim, const vector<vector<double>>& simDocs);

vector<pair<double,int>> consultarMinSim(int doc, int numDocsSim, const vector<vector<double>>& simDocs);

double consultarSimEntreDocs(int doc1, int doc2, const vector<vector<double>>& simDocs);

