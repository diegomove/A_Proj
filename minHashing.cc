#include "minHashing.hh"

int nextPrime(int n)
{
    int num = n+1;
    while (!isPrime(num))
    {
        ++num;
    }
    return num;
}

bool isPrime(int n)
{
    if (n<=1) return false;
    else if (n <= 3) return true;
    else if (n%2 == 0 || n%3 == 0) return false;
    else 
    {
        for (int i = 5; i*i <= n; i +=6)
        {
            if (n%i == 0 || n%(i+2) == 0) return false;
        }
        return true;
    }
}

int hashFunction(int i, const string& shingle, int mod)
{
    // falta funcio de hash, estoy en ello
}

float minHash(const set<string>& F1,const set<string>& F2, int n)
{
    vector<int> sig_F1 = computeMinSignature(F1, n);
    
    vector<int> sig_F2 = computeMinSignature(F2, n);

    return minHash_jaccard_similarity(sig_F1, sig_F2);
}

vector<int> computeMinSignature(const set<string>& shingles, int n) 
{
    int tamCols = shingles.begin()->length();
    vector<int> signature(tamCols, INT_MAX);

    int mod = nextPrime(tamCols);

    for (const string& shingle : shingles) 
    {
        vector<int> hashValues(n);
        for (int i = 0; i < n; ++i)
        {
            hashValues[i] = hashFunction(i, shingle, mod);
        }

        for (int c = 0; c < tamCols; ++c)
        {
            if (shingle[c] == '1') 
            {
                for (int i = 0; i < n; ++i) 
                {
                    signature[c] = min(signature[c], hashValues[i]);
                }
            }
        }
    }

    return signature;
}


float minHash_jaccard_similarity(const vector<int>& signatureF1, const vector<int>& signatureF2)
{
    int sum = 0;
    for (int i = 0; i < signatureF1.size(); ++i)
    {
        if (signatureF1[i] == signatureF2[i])
        {
            ++sum;
        }
    }

    return float(sum)/signatureF1.size();
}