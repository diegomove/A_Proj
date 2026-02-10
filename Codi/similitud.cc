#include "similitud.hh"

void simBetweenDocs(vector<vector<double>>& simDocs, int doc1, int doc2, double sim)
{
    simDocs[doc1][doc2] = sim;
    simDocs[doc2][doc1] = sim;
}

vector<pair<double, int>> consultarMaxSim(int doc, int numDocsSim, const vector<vector<double>>& simDocs)
{
    vector<pair<double, int>> similitudes;
    vector<double> simDocsCopia = simDocs[doc];

    for (int i = 0; i < static_cast<int>(simDocs.size()); ++i) {
        if (i != doc) {  // Excluimos el documento actual
            similitudes.push_back({simDocsCopia[i], i});
        }
    }

    nth_element(similitudes.begin(), similitudes.begin() + numDocsSim, similitudes.end(), greater<>());

    sort(similitudes.begin(), similitudes.end(), greater<>());

    /*
    cout << "Top " << numDocsSim << " documentos más similares al documento " << doc << ":\n";
    for (int i = 0; i < numDocsSim; ++i) {
        cout << "Índice: " << similitudes[i].second 
             << " - Similitud: " << similitudes[i].first << "\n";
    }
    */
    return similitudes;
}

vector<pair<double, int>> consultarMinSim(int doc, int numDocsSim, const vector<vector<double>>& simDocs)
{
    vector<pair<double, int>> similitudes;
    vector<double> simDocsCopia = simDocs[doc];

    for (int i = 0; i < static_cast<int>(simDocs.size()); ++i) {
        if (i != doc) {  // Excluimos el documento actual
            similitudes.push_back({simDocsCopia[i], i});
        }
    }

    nth_element(similitudes.begin(), similitudes.begin() + numDocsSim, similitudes.end(), less<>());

    sort(similitudes.begin(), similitudes.end(), less<>());

    /*
    cout << "Top " << numDocsSim << " documentos menos similares al documento " << doc << ":\n";
    for (int i = 0; i < numDocsSim; ++i) {
        cout << "Índice: " << similitudes[i].second 
             << " - Similitud: " << similitudes[i].first << "\n";
    }
    */
    return similitudes;
}

double consultarSimEntreDocs(int doc1, int doc2, const vector<vector<double>>& simDocs)
{
    return simDocs[doc1][doc2];
}