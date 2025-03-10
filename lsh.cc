#include "lsh.hh"


set<pair<int, int>> lsh (const vector<vector<int>>& minHashes, int numBands) {
    int rowsPerBand = minHashes[0].size() / numBands;
    unordered_map<string, vector<int>> buckets;

    for (int docIdx = 0; docIdx < minHashes.size(); ++docIdx) {
        for (int band = 0; band < numBands; ++band) {
            string bandSignature = "";
            for (int row = 0; row < rowsPerBand; ++row) {
                bandSignature += to_string(minHashes[docIdx][band * rowsPerBand + row]) + "-";
            }
            buckets[bandSignature].push_back(docIdx);
        }
    }

    // Filtrar pares de documentos similares
    set<pair<int, int>> candidatePairs;
    for (const auto& bucket : buckets) {
        const vector<int>& docsInBucket = bucket.second;
        if (docsInBucket.size() > 1) {
            for (size_t i = 0; i < docsInBucket.size(); ++i) {
                for (size_t j = i + 1; j < docsInBucket.size(); ++j) {
                    candidatePairs.insert(make_pair(docsInBucket[i], docsInBucket[j]));
                }
            }
        }
    }
    return candidatePairs;
}