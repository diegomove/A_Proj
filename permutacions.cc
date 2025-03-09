#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <set>
#include <random>
#include <stdexcept>

using namespace std;

vector<string> dividirEnPalabras(const string &texto) {
    vector<string> palabras;
    stringstream flujo(texto);
    string palabra;
    while (flujo >> palabra) {
        palabras.push_back(palabra);
    }
    return palabras;
}

// Función para generar una permutación aleatoria de las palabras del documento
    string permutarDocumento(const vector<string> &palabras) {
        vector<string> palabrasMezcladas = palabras;
        random_device dispositivo;
        mt19937 generador(dispositivo());
        shuffle(palabrasMezcladas.begin(), palabrasMezcladas.end(), generador);

        stringstream documentoPermutado;
        for (const auto &palabra : palabrasMezcladas) {
            documentoPermutado << palabra << " ";
        }
        return documentoPermutado.str();
    }

// Función para generar un conjunto de documentos permutados
vector<string> generarDocumentos(const string &documentoBase, int numeroDocumentos) {
    // Dividir el documento base en palabras
    vector<string> palabras = dividirEnPalabras(documentoBase);

    // Validar que el documento base tenga al menos 50 palabras únicas
    set<string> palabrasUnicas(palabras.begin(), palabras.end());
    if (palabrasUnicas.size() < 50) {
        throw runtime_error("Error: El documento base debe contener al menos 50 palabras únicas.");
    }

    // Generar los documentos permutados y almacenarlos en un vector
    vector<string> documentosGenerados;
    for (int i = 0; i < numeroDocumentos; ++i) {
        documentosGenerados.push_back(permutarDocumento(palabras));
    }

    return documentosGenerados;
}



