#pragma once
#include <string>
#include <memory>
#include <vector>
using namespace std;

// Una muestra del dataset
struct Sample {
    int id;
    double feature1;
    double feature2;
    int label;
};

// Declaracion de funciones
void crearCSVPrueba();
Sample** loadDataset(const std::string& filename, int capacidadMax, int& outCount);
Sample** clonarDataset(Sample** original, int count, int& outCount);
void destroyDataset(Sample** samples);