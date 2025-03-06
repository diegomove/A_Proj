#include <iostream>
#include <vector>
#include <string>
#include <climits>
#include <set>
#include <algorithm>
#include <functional>

int nextPrime(int n);

bool isPrime(int n);

int hashFunction(int i, const string& shingle, int mod);

float minHash(const set<string>& F1, const set<string>& F2, int n);

vector<int> computeMinSignature(const set<string>& shingle, int n);

float minHash_jaccard_similarity(const vector<int>& signatureF1, const vector<int>& signatureF2);