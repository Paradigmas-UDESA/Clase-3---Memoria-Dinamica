#include <fstream> // Librerias
#include <sstream>
#include <stdexcept>
#include "sample.h"

using namespace std; // Elimina la necesidad de usar "std::" Es una mala practica en un entorno de produccion.

/* Funcion encargada de cargar el archivo csv. 
Recibe el nombre, la capacidad del arreglo y tiene una referencia donde establecera cuantos samples conto.
*/
Sample** loadDataset(const string& filename, int capacidadMax, int& outCount) {
    Sample** dataset = new Sample*[capacidadMax];
    
    // Abrir archivo y comprobar apertura
    ifstream file(filename);
    if (!file.is_open()) {
        throw runtime_error("No se pudo abrir el archivo CSV.");
    }
    string line;
    getline(file, line); // Ignorar primer linea

    int i = 0;
    while (getline(file, line)) {
        // Extraccion de los valores de la linea actual hacia el Sample
        stringstream ss(line);
        string val;

        Sample* s = new Sample();
        if (getline(ss, val, ',')) s->id = stoi(val); // stoi: String TO Integer.
        if (getline(ss, val, ',')) s->feature1 = stod(val);
        if (getline(ss, val, ',')) s->feature2 = stod(val);
        if (getline(ss, val, ',')) s->label = stoi(val);

        dataset[i] = s;
        i++;
    }

    outCount = i;
    return dataset;
}

/* Funcion encargada de liberar la memoria de un dataset */
void destroyDataset(Sample** samples) {
    delete samples;
}

/* Funcion que clona los primeros elementos de un dataset*/
Sample** clonarDataset(Sample** original, int count, int& outCount) {
    if (original == nullptr || count <= 0) {
        outCount = 0;
        return nullptr;
    }

    Sample** clone = new Sample*[count];
    
    for (int i = 0; i < count; i++) {
        clone[i] = original[i];
    }

    return clone;
}