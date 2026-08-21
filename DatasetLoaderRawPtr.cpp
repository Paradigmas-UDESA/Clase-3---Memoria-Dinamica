/* Version con manejo de memoria manual 
Se refactorizo el codigo para usar pares <arreglo, tamano>.
*/
#include <string>
#include <fstream> // Librerias
#include <sstream>
#include <stdexcept>
#include "sample.h"
using namespace std; // Elimina la necesidad de usar "std::" Es una mala practica en un entorno de produccion.

// Una muestra del dataset

/* Funcion encargada de cargar el archivo csv. 
Recibe el nombre, la capacidad del arreglo
Devuelve un arreglo de punteros a samples y cuantos samples conto.
*/
pair<Sample**,int> loadDataset(const string& filename, int capacidad) {
    /*
    Reserva de espacio para los punteros a sample.
    */
    Sample** dataset = new Sample*[capacidad];
    
    // Abrir archivo y comprobar apertura
    ifstream file(filename);
    if (!file.is_open()) {
        throw runtime_error("No se pudo abrir el archivo CSV.");
    }
    string line;
    getline(file, line); // Ignorar primer linea

    int i=0;
    // Bug 1: No se fija si se alcanzo la capacidad maxima del arreglo.
    while (getline(file, line) and i < capacidad) { 
        // Extraccion de los valores de la linea actual hacia el Sample
        stringstream ss(line);
        string val;

        // Se reserva memoria para un sample
        Sample* s = new Sample();
        if (getline(ss, val, ',')) s->id = stoi(val); // stoi: String TO Integer.
        if (getline(ss, val, ',')) s->feature1 = stod(val);
        if (getline(ss, val, ',')) s->feature2 = stod(val);
        if (getline(ss, val, ',')) s->label = stoi(val);

        // Se almacena el puntero al sample en el arreglo
        dataset[i] = s; // Si no se verifica que 'i' sea menor a la capacidad del arreglo esto se indefine. Es una operacion ilegal.
        i++;
    }

    // Se devuelve el arreglo con los punteros y su tamano.
    // Estos samples no se liberan al terminar la funcion porque se reservaron con new.
    return {dataset, i};
}

/* Funcion encargada de liberar la memoria de un dataset */
void destroyDataset(Sample** samples, int tam) {
    // Bug 2: La version original intenta: delete samples. 
    // Es incorrecto porque no libera la memoria de los samples individuales y "delete" solo elimina punteros de objetos que no son arreglos.
    for (int i=0; i < tam; i++) {
        delete samples[i];
    }
    delete[] samples; // Puede borrar arrays.
}

/* Funcion que clona los primeros elementos de un dataset*/
pair<Sample**, int> clonarDataset(pair<Sample**,int> original, int primeros) {
    auto [arrOriginal, tamOriginal] = original; // extraigo variables del par.

    if (arrOriginal == nullptr || primeros <= 0) {
        return {nullptr, 0};
    }

    Sample** clone = new Sample*[primeros];

    int i = 0;
    while ( i < primeros and i < tamOriginal) {
        // Bug 4: Se hacia solo una copia del puntero, se debe copiar el objeto original.
        // Porque disparara doble free si se intenta liberar la memoria desde el dataset original y este.

        Sample s = *arrOriginal[i]; // Copia
        clone[i] = new Sample(s);   // Reserva de espacio para el sample y asignacion del puntero en el arreglo.
        i++;
    }

    // Nuevo clon con su tamano
    return {clone, i};
} 