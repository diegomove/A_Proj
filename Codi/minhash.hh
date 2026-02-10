#include <string>
#include <vector>
#include <unordered_set>
using namespace std;

vector<int> generateRandomCoefficients(int num, int maxVal);

vector<int> computeMinHash(const unordered_set<string>& shingles, int numHashFunctions, vector<int> a, vector<int> b);

double minHashJaccard(const vector<int>& sig1, const vector<int>& sig2);

int nextPrime(int n);

bool isPrime(int n);

