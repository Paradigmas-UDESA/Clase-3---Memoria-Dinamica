#include <gtest/gtest.h>
#include <memory>
#include <string>
#include <vector>
#include <utility>
#include "sample.h"
using namespace std;

// Por un tema de compilacion, se declaran las funciones que estan en DatasetLoaderSmart.cpp
std::vector<std::unique_ptr<Sample>> loadDataset(const std::string& filename);
void destroyDataset(std::vector<std::unique_ptr<Sample>> samples);
std::vector<std::unique_ptr<Sample>> clonarDataset(std::vector<std::unique_ptr<Sample>>& original, int count);

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

TEST(DatasetTest, Carga) {
    int total = 0;
    int capacidadDeclarada = 5;

    vector<unique_ptr<Sample>> dataset = loadDataset("dataset.csv");
    
    vector<unique_ptr<Sample>> vacio;
    
    ASSERT_NE(dataset, vacio);
    EXPECT_EQ(dataset[0]->id, 1);

    // Al salir del scope el vector se libera solo y cada unique_ptr tambien.
}

TEST(DatasetTest, Clonacion) {

    vector<unique_ptr<Sample>> dataset = loadDataset("dataset.csv");    
    vector<unique_ptr<Sample>> copia = clonarDataset(dataset, 3);
    
    vector<unique_ptr<Sample>> vacio;
    EXPECT_NE(copia, vacio);
    EXPECT_EQ(copia.size(), 3);
    EXPECT_EQ(dataset[0]->feature1, copia[0]->feature1);
}


// Test final. Descomentar despues de la refactorizacion con smart pointers.
TEST(DatasetTest, VerificacionDeDatosCargados) {
    vector<unique_ptr<Sample>> dataset = loadDataset("dataset.csv");
    auto [promedio1, promedio2] = calcularPromedioFeatures(dataset);

    EXPECT_DOUBLE_EQ(promedio1, 0.5);
    EXPECT_DOUBLE_EQ(promedio2, 1.0);
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}