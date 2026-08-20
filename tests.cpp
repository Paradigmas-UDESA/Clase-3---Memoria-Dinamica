#include <gtest/gtest.h>
#include "DatasetLoader.h"
#include "util.cpp"


TEST(DatasetTest, Carga) {
    int total = 0;
    int capacidadDeclarada = 3;

    Sample** dataset = loadDataset("dataset.csv", capacidadDeclarada, total);
    
    EXPECT_EQ(total, 3);
    
    ASSERT_NE(dataset, nullptr);
    EXPECT_EQ(total, 5);
    EXPECT_EQ(dataset[0]->id, 1);

    // Termina el scope del test.... que pasa con el dataset?
    // destroyDataset(dataset);
}

TEST(DatasetTest, Clonacion) {
    int total = 0;
    Sample** dataset = loadDataset("dataset.csv", 5, total);
    
    int totalCopia = 0;
    Sample** copia = clonarDataset(dataset, 3, totalCopia);

    EXPECT_NE(copia, nullptr);
    EXPECT_EQ(totalCopia, 3);
    EXPECT_EQ(dataset[0]->feature1, copia[0]->feature1);

    destroyDataset(dataset);
    destroyDataset(copia);
}


// Test final. Descomentar despues de la refactorizacion con smart pointers.
// TEST(DatasetTest, VerificacionDeDatosCargados) {
//     vector<unique_ptr<Sample>> dataset = loadDataset("dataset.csv");
//     auto [promedio1, promedio2] = calcularPromedioFeatures(dataset);

//     EXPECT_DOUBLE_EQ(promedio1, 0.5);
//     EXPECT_DOUBLE_EQ(promedio2, 1.0);
// }


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}