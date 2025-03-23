#include <iostream>
#include <unordered_set>
#include <vector>
#include <functional>
#include <random>
#include <algorithm>
#include <limits.h>


using namespace std;

vector<int> generateRandomCoefficients(int num, int maxVal) {
    unordered_set<int> uniqueNumbers;
    vector<int> coefficients;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(1, maxVal);

    while (uniqueNumbers.size() < num) {
        int randNum = distrib(gen);
        //cout << "randomNum = " << randNum << endl;
        if (uniqueNumbers.find(randNum) == uniqueNumbers.end()) {
            uniqueNumbers.insert(randNum);
            coefficients.push_back(randNum);
        }
    }
    return coefficients;
}

bool isPrime(int n) {
    if (n < 2) return false;
    if (n == 2 || n == 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    
    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }
    return true;
}

int nextPrime(int n) {
    if (n < 2) return 2;
    int candidate = n + 1;
    while (!isPrime(candidate)) {
        candidate++;
    }
    return candidate;
}


vector<int> computeMinHash(const unordered_set<string>& shingles, int numHashFunctions, vector<int> a, vector<int> b) {
    int prime = nextPrime(2 * numHashFunctions);
    //cout << "prime " << prime << endl;
    vector<int> minHashValues(numHashFunctions, prime);
    const int interval = prime; // Un numero primo que sirve para limitar el intervalo de la funcion hash


    hash<string> hashFunction;
    for (const auto& shingle : shingles) {
        int originalHash = hashFunction(shingle) % interval;
        if (originalHash < 0) originalHash*= -1;
        for (int i = 0; i < numHashFunctions; i++) {
            int hashValue = (a[i] * originalHash + b[i]) % interval;
            //cout << hashValue << endl;
            minHashValues[i] = min(minHashValues[i], hashValue);
        }
    }
    //for (int it = 0; it<minHashValues.size(); ++it) cout << minHashValues[it] << endl;
    return minHashValues;
}


double minHashJaccard(const vector<int>& sig1, const vector<int>& sig2) {
    int matchCount = 0;
    for (size_t i = 0; i < sig1.size(); i++) {
        if (sig1[i] == sig2[i]) {
            matchCount++;
        }
    }
    return static_cast<double>(matchCount) / sig1.size();
}
