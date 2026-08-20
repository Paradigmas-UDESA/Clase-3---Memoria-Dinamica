#include <iostream>
#include <vector>
#include <memory>
#include "DatasetLoader.h"
using namespace std;

/* Se puede ignorar esta funcion, es para ver si se cargaron todos los datos en el ultimo test*/
pair<double,double> calcularPromedioFeatures(const std::vector<std::unique_ptr<Sample>>& dataset) {
    if (dataset.empty()) {
        return {0,0};
    }
    
    double suma1 = 0.0;
    double suma2 = 0.0;
    for (size_t i=0; i < dataset.size(); i++) {
        suma1 += dataset[i]->feature1;
        suma2 += dataset[i]->feature2;
    }
    double promedio1 = suma1 / dataset.size();
    double promedio2 = suma2 / dataset.size();

    return {promedio1, promedio2};
}