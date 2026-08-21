/* Version con manejo de memoria manual */
#include <fstream> // Librerias
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include "sample.h"

using namespace std; // Elimina la necesidad de usar "std::" Es una mala practica en un entorno de produccion.

vector<unique_ptr<Sample>> loadDataset(const string& filename) {
    // Abrir archivo y comprobar apertura
    ifstream file(filename);
    if (!file.is_open()) {
        throw runtime_error("No se pudo abrir el archivo CSV.");
    }

    vector<unique_ptr<Sample>> dataset;
    string line;
    getline(file, line); // Ignorar primer linea

    while (getline(file, line)) {
        // Extraccion de los valores de la linea actual hacia el Sample
        stringstream ss(line);
        string val;

        Sample* s = new Sample();
        if (getline(ss, val, ',')) s->id = stoi(val); // stoi: String TO Integer.
        if (getline(ss, val, ',')) s->feature1 = stod(val);
        if (getline(ss, val, ',')) s->feature2 = stod(val);
        if (getline(ss, val, ',')) s->label = stoi(val);

        dataset.push_back(unique_ptr<Sample>(s));
    }

    return dataset;
}

// Con smart pointers ya no hace falta tener esta funcion
void destroyDataset(vector<unique_ptr<Sample>> samples) {
    samples.clear();
}

vector<unique_ptr<Sample>> clonarDataset(vector<unique_ptr<Sample>>& original, int count) {
    if (original.size() == 0 || count <= 0) {
        return {}; // Vector vacio
    }
    
    vector<unique_ptr<Sample>> clone;
    
    for (int i = 0; i < count; i++) {
        // Deep copy.
        Sample * e = new Sample (*original[i]);
        clone.push_back(unique_ptr<Sample>(e));
    }

    return clone;
}