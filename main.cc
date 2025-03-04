#include <iostream>
#include <string>
#include <vector>
#include "k-shingles.hh"
#include "normalizeText.hh"
#include "jaccard.hh"
using namespace std;


int main(){
    ifstream inputFile;
    
    cout << "Con que quieres trabajar: Dos documentos (d), o un conjunto de documentos (c)? " << endl;
    string choice1;
    cin >> choice1;

    if(choice1 == "d"){ //DOS DOCUMENTOS
    
        cout << "Que quieres realizae Jaccard (j) o MinHash (m) ?" << endl;
        string choice2;
        cin >> choice2;

        if(choice2 == "j"){ //JACCARD
            cout << "Que numero de k shingles quieres usar?" << endl;
            int k;
            cin >> k;
            vector<string> paths;

            paths = vector<string>(2);
            cout << "Introduce los nombres de los dos ficheros tal que: f1.txt f2.txt " << endl;
            string file1, file2;
            cin >> paths[0] >> paths[1];

            ifstream inputFile("./input_texts/" + paths[0]);
            string text1 = normalizeText(&inputFile);
            set<string> F1 = k_shingles(k,text1);
            
            
            ifstream inputFile("./input_texts/" + paths[1]);
            string text2 = normalizeText(&inputFile);
            set<string> F2 = k_shingles(k,text2);
            

            float sim_jacc =jaccard_similarity(F1, F2);
            cout << "La similitud de Jaccard entre " << paths[0] << " y " << paths[1] << " es " << sim_jacc << endl;
        }
        else if(choice2 == "m"){ //MINHASH
            
            cout << "Que numero de k shingles quieres usar?" << endl;
            int k;
            cin >> k;

            cout << "Quin numero de funcions vols?" << endl;
            int n;
            cin >> n;

            vector<string> paths;

            paths = vector<string>(2);
            cout << "Introduce los nombres de los dos ficheros tal que: f1.txt f2.txt " << endl;
            string file1, file2;
            cin >> paths[0] >> paths[1];

            ifstream inFile("./input_texts/" + paths[0]);
            set<string> F1 = k_shingles(&inFile, k);
        
            ifstream inFile("./input_texts/" + paths[1]);
            set<string> F2 = k_shingles(&inFile, k);
            

            float sim_minHash = MinHash(F1, F2, n);
            cout << "La similitud de Jaccard amb minHash entre " << paths[0] << " y " << paths[1] << " es " << sim_minHash << endl;
        }
    }

    else if(choice1 == "c"){ //CONJUNTO DE DOCUMENTOS

    }
}