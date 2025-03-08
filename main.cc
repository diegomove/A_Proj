#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <unordered_set>
#include <fstream>
#include "k-shingles.hh"
#include "normalizeText.hh"
#include "jaccard.hh"
#include "minhash.hh"
#include <limits.h>

using namespace std;


string readAndNormalizeText(const string& filePath) {
    ifstream inputFile("./input_texts/" + filePath);
    if (!inputFile) {
        cerr << "Error: No se pudo abrir el archivo " << filePath << endl;
        exit(1);
    }
    return normalizeText(inputFile);  
}

int main() {
    cout << "¿Con qué quieres trabajar? Dos documentos (d) o un conjunto de documentos (c)? " << endl;
    string choice1;
    cin >> choice1;

    if (choice1 == "d") { // DOS DOCUMENTOS
        cout << "¿Qué quieres realizar? Jaccard (j) o MinHash (m)? " << endl;
        string choice2;
        cin >> choice2;

        cout << "Introduce los nombres de los dos ficheros tal que: f1.txt f2.txt " << endl;
        vector<string> paths(2);
        //cin >> paths[0] >> paths[1];
        paths[0] = "test.txt";
        paths[1] = "test2.txt";

        cout << "¿Qué número de k-shingles quieres usar?" << endl;
        int k;
        cin >> k;

        // lee y normaliza los archivos
        string text1 = readAndNormalizeText(paths[0]);
        string text2 = readAndNormalizeText(paths[1]);

        // generar k-shingles
        set<string> F1 = k_shingles(k, text1);
        set<string> F2 = k_shingles(k, text2);

        if (choice2 == "j") { // JACCARD
            float sim_jacc = jaccard_similarity(F1, F2);
            cout << "La similitud de Jaccard entre " << paths[0] << " y " << paths[1] << " es " << sim_jacc << endl;
        }
        else if (choice2 == "m") { // MINHASH
            cout << "¿Cuántas funciones de hash quieres usar?" << endl;
            int n;
            cin >> n;

            vector<int> a = generateRandomCoefficients(n, 20000);
            vector<int> b = generateRandomCoefficients(n, 20000);

            // set<string> a unordered_set<string> antes de pasar a computeMinHash()
            unordered_set<string> F1_unordered(F1.begin(), F1.end());
            unordered_set<string> F2_unordered(F2.begin(), F2.end());

            // calcula firmas MinHash
            vector<int> m1 = computeMinHash(F1_unordered, n, a, b);
            vector<int> m2 = computeMinHash(F2_unordered, n, a, b);


            // calcula similitud con MinHash
            double sim_minHash = minHashJaccard(m1, m2);
            cout << "La similitud de Jaccard con MinHash entre " << paths[0] << " y " << paths[1] << " es " << sim_minHash << endl;
        }
        else {
            cout << "Opción no válida." << endl;
        }
    }
    else if (choice1 == "c") { // CONJUNTO DE DOCUMENTOS
        cout << "Funcionalidad aún no implementada." << endl;
    }
    else {
        cout << "Opción no válida." << endl;
    }

    return 0;
}
