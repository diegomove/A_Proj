#include <iostream>
#include <string>
#include <vector>
#include <set>
#include "lsh.hh"
#include <unordered_set>
#include <fstream>
#include <limits.h>
#include "k-shingles.hh"
#include "normalizeText.hh"
#include "jaccard.hh"
#include "normalizeText2.hh"
#include "minhash.hh"
#include "permutacions.hh"
#include "similitud.hh"



using namespace std;

string readAndNormalizeText2(const string& filePath) {
    ifstream inputFile("./input_texts/" + filePath);
    if (!inputFile) {
        cerr << "Error: No se pudo abrir el archivo " << filePath << endl;
        exit(1);
    }
    return normalizeText2(inputFile);  
}

unordered_set<string> extraerShinglesAleatorios(const unordered_set<string>& shinglesBase, int porcentajeShingles) {
    unordered_set<string> shinglesAleatorios;
    vector<string> shinglesVector(shinglesBase.begin(), shinglesBase.end());

    // Barrejem el vector per obtenir shingles aleatoris
    random_shuffle(shinglesVector.begin(), shinglesVector.end());

    // Seleccionem els primers 'numShingles' shingles
    for (int i = 0;  i < (shinglesVector.size() * porcentajeShingles/100); ++i) {
        shinglesAleatorios.insert(shinglesVector[i]);
    }

    return shinglesAleatorios;
}

double calcularSimilitudTeorica(int n_i, int n_j, int n) {
    double p_i = static_cast<double>(n_i) / n;
    double p_j = static_cast<double>(n_j) / n;
    return (p_i * p_j) / (p_i + p_j - p_i * p_j);
}

int main() {
    cout << "¿Con qué quieres trabajar? Dos documentos (d), un conjunto de documentos (c) o un subconjunto de documentos virtuales(v)? " << endl;
    string choice1;
    cin >> choice1;

    if (choice1 == "d") { // DOS DOCUMENTOS
        cout << "¿Qué quieres realizar? Jaccard (j) o MinHash (m)? " << endl;
        string choice2;
        cin >> choice2;

        cout << "Introduce los nombres de los dos ficheros tal que: f1.txt f2.txt " << endl;
        vector<string> paths(2);
        cin >> paths[0] >> paths[1];

        cout << "¿Qué número de k-shingles quieres usar?" << endl;
        int k;
        cin >> k;

        // Abrir archivos con ifstream
        ifstream file1("./input_texts/" + paths[0]);
        ifstream file2("./input_texts/" + paths[1]);

        if (!file1 || !file2) {
            cerr << "Error: No se pudieron abrir los archivos." << endl;
            return 1;
        }

        // Normalizar los archivos
        string text1 = normalizeText2(file1);
        string text2 = normalizeText2(file2); //en normalizetext2 solo se eliminan los stopwords
        string text_definitivo1 = normalize_Text(text1); //normalizetext se eliminan espacios, signos de puntuacion, se pasa a minusculas
        string text_definitivo2 = normalize_Text(text2);
        // Generar k-shingles
        unordered_set<string> F1 = k_shingles(k, text_definitivo1); 
        unordered_set<string> F2 = k_shingles(k, text_definitivo2);

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

            // Convertir sets a unordered_set
            unordered_set<string> F1_unordered(F1.begin(), F1.end());
            unordered_set<string> F2_unordered(F2.begin(), F2.end());

            // Calcular firmas MinHash
            vector<int> m1 = computeMinHash(F1_unordered, n, a, b);
            vector<int> m2 = computeMinHash(F2_unordered, n, a, b);

            // Calcular similitud con MinHash
            double sim_minHash = minHashJaccard(m1, m2);
            cout << "La similitud de Jaccard con MinHash entre " << paths[0] << " y " << paths[1] << " es " << sim_minHash << endl;
        }
        else {
            cout << "Opción no válida." << endl;
        }
    }
    else if (choice1 == "c") { // CONJUNTO DE DOCUMENTOS
        cout << "Introduce el nombre del documento base  (por ejemplo, texto_prueba.txt): ";
        string rutaDocumentoBase;
        cin >> rutaDocumentoBase;

        int numeroPermutaciones;
        cout << "Introduce el número de documentos permutados que deseas generar: ";
        cin >> numeroPermutaciones;

        // Validar el número de permutaciones
        if (numeroPermutaciones <= 0) {
            cerr << "Error: El número de permutaciones debe ser mayor que 0." << endl;
            return 1;
        }

        cout << "¿Qué número de k-shingles quieres usar?" << endl;
        int k;
        cin >> k;

        cout << "¿Qué enfoque deseas utilizar?" << endl;
        cout << "   1. Calcular la similitud de Jaccard entre todas las combinaciones posibles de documentos." << endl;
        cout << "   2. Aproximar la similitud de Jaccard con MinHash." << endl;
        cout << "   3. Aproximar la similitud de Jaccard con MinHash y un algoritmo sensible a la localidad (LSH)." << endl;
        int enfoque;
        cin >> enfoque;
        try {
            // Abrir y normalizar el archivo base
            ifstream archivoBase("./input_texts/" + rutaDocumentoBase);
            if (!archivoBase) {
                cerr << "Error: No se pudo abrir el archivo base." << endl;
                return 1;
            }

            string documentoBase = normalizeText2(archivoBase);

            // Generar documentos permutados
            vector<string> documentos = generarDocumentos(documentoBase, numeroPermutaciones);

            cout << "Se generaron " << numeroPermutaciones << " documentos permutados." << endl;

            vector<unordered_set<string>> shinglesPorDocumento;

            for (size_t i = 0; i < documentos.size(); ++i) {
                string textoNormalizado = normalize_Text(documentos[i]); // Normalizar documento
                unordered_set<string> shingles = k_shingles(k, textoNormalizado); // Generar k-shingles

                shinglesPorDocumento.push_back(shingles);

                cout << "K-Shingles del documento " << i + 1 << ": ";
                for (const string& shingle : shingles) {
                    cout << shingle << " ";
                }
                cout << endl;
            }

        vector<vector<double>> simDocs(documentos.size(), vector<double>(documentos.size())); // Creamos matriz donde guardaremos las respectivas similitudes entre cada par de documentos

        if(enfoque == 1){
            for (size_t i = 0; i < documentos.size(); ++i) {
                for (size_t j = i+1; j < documentos.size(); ++j) {
                    double jaccardSim = jaccard_similarity(shinglesPorDocumento[i], shinglesPorDocumento[j]);
                    simBetweenDocs(simDocs, i, j, jaccardSim);
                    simBetweenDocs(simDocs, j, i, jaccardSim); // Almacenamos la similitud en ambas posiciones
                    //cout << "Similitud de Jaccard entre documento " << i + 1 << " y documento " << j + 1 << ": " << jaccardSim << endl;
                }
            simBetweenDocs(simDocs, i, i, -1.0); // Asignamos -1.0 para la diagonal ya que comparamos un documento consigo mismo
            }
            int numDoc = 0; // número del documento que queremos comprobar las máximas/mínimas similitudes 
            int numDocsSim = 10; // número de documentos con el máximo/mínimo de similitud respecto al documento numDoc(saldrá el top 10 por decirlo de alguna manera)
            vector<pair<double, int>> maximasSim = consultarMaxSim(numDoc, numDocsSim, simDocs); 
            vector<pair<double, int>> minimasSim = consultarMinSim(numDoc, numDocsSim, simDocs);
        }else if(enfoque == 2){
            cout << "¿Cuántas funciones de hash quieres usar?" << endl;
            int numHashes;
            cin >> numHashes;

            vector<int> a = generateRandomCoefficients(numHashes, 20000);
            vector<int> b = generateRandomCoefficients(numHashes, 20000);

            vector<vector<int>> minHashesPorDocumento;

            for (size_t i = 0; i < shinglesPorDocumento.size(); ++i) {
                vector<int> minHash = computeMinHash(shinglesPorDocumento[i], numHashes, a, b);
                minHashesPorDocumento.push_back(minHash);
            }

            for (size_t i = 0; i < minHashesPorDocumento.size(); ++i) {
                for (size_t j = i+1; j < minHashesPorDocumento.size(); ++j) {
                        double minHashJaccardSim = minHashJaccard(minHashesPorDocumento[i], minHashesPorDocumento[j]);
                        simBetweenDocs(simDocs, i, j, minHashJaccardSim);
                        simBetweenDocs(simDocs, j, i, minHashJaccardSim); // Almacenamos la similitud en ambas posiciones
                        //cout << "Similitud aproximada entre documento " << i + 1 << " y documento " << j + 1 << ": " << minHashJaccardSim << endl;
                    
                    
                }
                simBetweenDocs(simDocs, i, i, -1.0); // Asignamos -1.0 para la diagonal ya que comparamos un documento consigo mismo
            }

            int numDoc = 0; // número del documento que queremos comprobar las máximas/mínimas similitudes 
            int numDocsSim = 10; // número de documentos con el máximo/mínimo de similitud respecto al documento numDoc(saldrá el top 10 por decirlo de alguna manera)
            vector<pair<double, int>> maximasSim = consultarMaxSim(numDoc, numDocsSim, simDocs); 
            vector<pair<double, int>> minimasSim = consultarMinSim(numDoc, numDocsSim, simDocs);

            //Mostrar similitudes entre documentos
            /*
            for (size_t i = 0; i < simDocs.size(); ++i) {
                for (size_t j = 0; j < simDocs.size(); ++j) {
                    cout << "Similitud entre documento " << i+1 << " y documento " << j+1 << " : " << simDocs[i][j] << endl;
                }
                cout << endl;
            }
            */

        }else if(enfoque == 3){
            cout << "¿Cuántas funciones de hash quieres usar?" << endl;
            int numHashes;
            cin >> numHashes;

            cout << "¿En cuántas bandas deseas dividir las firmas?" << endl;
            int numBands;
            cin >> numBands;

            vector<int> a = generateRandomCoefficients(numHashes, 20000);
            vector<int> b = generateRandomCoefficients(numHashes, 20000);

            vector<vector<int>> minHashesPorDocumento;

            for (size_t i = 0; i < shinglesPorDocumento.size(); ++i) {
                vector<int> minHash = computeMinHash(shinglesPorDocumento[i], numHashes, a, b);
                minHashesPorDocumento.push_back(minHash);
            }

            set<pair<int, int>> candidatePairs = lsh(minHashesPorDocumento, numBands);

            // Calcular similitud de Jaccard para los candidatos y mostrar resultados
            cout << "Candidatos encontrados por LSH:" << endl;
            for (const auto& pair : candidatePairs) {
                int doc1 = pair.first;
                int doc2 = pair.second;
                //double jaccardSim = minHashJaccard(minHashesPorDocumento[doc1], minHashesPorDocumento[doc2]);
                double jaccardSim = jaccard_similarity(shinglesPorDocumento[doc1], shinglesPorDocumento[doc2]);
                cout << "Similitud aproximada entre documento " << doc1 + 1 << " y documento " << doc2 + 1 << ": " << jaccardSim << endl;
            }
        }

        } catch (const runtime_error &error) {
            cerr << error.what() << endl;
            return 1;
        }

        
    }
    else if (choice1 == "v") {
        cout << "Introduce el nombre del documento base (por ejemplo, texto_prueba.txt): ";
        string rutaDocumentoBase;
        cin >> rutaDocumentoBase;

        cout << "¿Qué número de k-shingles quieres usar?" << endl;
        int k;
        cin >> k;

        cout << "¿Cuántos documentos virtuales deseas generar?" << endl;
        int numDocumentosVirtuales;
        cin >> numDocumentosVirtuales;

        cout << "¿Que porcentaje de shingles deseas extraer para cada documento virtual?" << endl;
        int porcentajeShingles;
        cin >> porcentajeShingles;

        // Abrir y normalizar el archivo base
        ifstream archivoBase("./input_texts/" + rutaDocumentoBase);
        if (!archivoBase) {
            cerr << "Error: No se pudo abrir el archivo base." << endl;
            return 0;
        }

        string documentoBase = normalizeText2(archivoBase);
        string textoNormalizado = normalize_Text(documentoBase);
        unordered_set<string> shinglesBase = k_shingles(k, textoNormalizado);

        // Generar documentos virtuales
        vector<unordered_set<string>> documentosVirtuales;
        for (int i = 0; i < numDocumentosVirtuales; ++i) {
            unordered_set<string> shinglesDocumento = extraerShinglesAleatorios(shinglesBase, porcentajeShingles);
            documentosVirtuales.push_back(shinglesDocumento);
        }

        cout << "¿Qué enfoque deseas utilizar para calcular la similitud?" << endl;
        cout << "   1. Jaccard" << endl;
        cout << "   2. MinHash" << endl;
        cout << "   3. MinHash con LSH" << endl;
        int enfoque;
        cin >> enfoque;

        if (enfoque == 1) {
            for (size_t i = 0; i < documentosVirtuales.size(); ++i) {
                for (size_t j = i + 1; j < documentosVirtuales.size(); ++j) {
                    double similitudCalculada = jaccard_similarity(documentosVirtuales[i], documentosVirtuales[j]);
                    double similitudTeorica = calcularSimilitudTeorica(documentosVirtuales[i].size(), documentosVirtuales[j].size(), shinglesBase.size());
                    cout << "Similitud calculada entre documento " << i + 1 << " y documento " << j + 1 << ": " << similitudCalculada << endl;
                    cout << "Similitud teórica entre documento " << i + 1 << " y documento " << j + 1 << ": " << similitudTeorica << endl;
                    cout << "Diferencia: " << abs(similitudCalculada - similitudTeorica) << endl;
                }
            }
        } else if (enfoque == 2) {
            cout << "¿Cuántas funciones de hash quieres usar?" << endl;
            int numHashes;
            cin >> numHashes;

            vector<int> a = generateRandomCoefficients(numHashes, 20000);
            vector<int> b = generateRandomCoefficients(numHashes, 20000);

            vector<vector<int>> minHashesPorDocumento;
            for (const auto& shingles : documentosVirtuales) {
                vector<int> minHash = computeMinHash(shingles, numHashes, a, b);
                minHashesPorDocumento.push_back(minHash);
            }

            for (size_t i = 0; i < minHashesPorDocumento.size(); ++i) {
                for (size_t j = i + 1; j < minHashesPorDocumento.size(); ++j) {
                    double similitudCalculada = minHashJaccard(minHashesPorDocumento[i], minHashesPorDocumento[j]);
                    double similitudTeorica = calcularSimilitudTeorica(documentosVirtuales[i].size(), documentosVirtuales[j].size(), shinglesBase.size());
                    cout << "Similitud calculada entre documento " << i + 1 << " y documento " << j + 1 << ": " << similitudCalculada << endl;
                    cout << "Similitud teórica entre documento " << i + 1 << " y documento " << j + 1 << ": " << similitudTeorica << endl;
                    cout << "Diferencia: " << abs(similitudCalculada - similitudTeorica) << endl;
                }
            }
        } else if (enfoque == 3) {
            cout << "¿Cuántas funciones de hash quieres usar?" << endl;
            int numHashes;
            cin >> numHashes;

            cout << "¿En cuántas bandas deseas dividir las firmas?" << endl;
            int numBands;
            cin >> numBands;

            vector<int> a = generateRandomCoefficients(numHashes, 20000);
            vector<int> b = generateRandomCoefficients(numHashes, 20000);

            vector<vector<int>> minHashesPorDocumento;
            for (const auto& shingles : documentosVirtuales) {
                vector<int> minHash = computeMinHash(shingles, numHashes, a, b);
                minHashesPorDocumento.push_back(minHash);
            }

            set<pair<int, int>> candidatePairs = lsh(minHashesPorDocumento, numBands);

            for (const auto& pair : candidatePairs) {
                int doc1 = pair.first;
                int doc2 = pair.second;
                double similitudCalculada = jaccard_similarity(documentosVirtuales[doc1], documentosVirtuales[doc2]);
                double similitudTeorica = calcularSimilitudTeorica(documentosVirtuales[doc1].size(), documentosVirtuales[doc2].size(), shinglesBase.size());
                cout << "Similitud calculada entre documento " << doc1 + 1 << " y documento " << doc2 + 1 << ": " << similitudCalculada << endl;
                cout << "Similitud teórica entre documento " << doc1 + 1 << " y documento " << doc2 + 1 << ": " << similitudTeorica << endl;
                cout << "Diferencia: " << abs(similitudCalculada - similitudTeorica) << endl;
            }
        } else {
            cout << "Opción no válida." << endl;
        }
    }

    return 0;
}
