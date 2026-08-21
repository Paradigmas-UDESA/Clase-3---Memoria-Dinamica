/* Tests version raw pointers */
#include <gtest/gtest.h>
#include <string>
#include <utility>
#include "sample.h"

std::pair<Sample**, int> loadDataset(const std::string& filename, int capacidad);
void destroyDataset(Sample** samples, int tam);
std::pair<Sample**, int> clonarDataset(std::pair<Sample**, int> original, int primeros);

TEST(DatasetTest, Carga) {
    int capacidadDeclarada = 5; // Despues de examinar el archivo CSV se arregla la cantidad de samples

    auto[dataset, total] = loadDataset("dataset.csv", capacidadDeclarada);
    
    ASSERT_NE(dataset, nullptr);
    EXPECT_EQ(total, 5);
    EXPECT_EQ(dataset[0]->id, 1);

    // Bug 3: No se liberaba la memoria.
    destroyDataset(dataset, 5);
}

TEST(DatasetTest, Clonacion) {
    auto [dataset, totalDataset] = loadDataset("dataset.csv", 5);
    auto [copia, totalCopia]  = clonarDataset({dataset,totalDataset}, 3);

    EXPECT_NE(copia, nullptr);
    EXPECT_EQ(totalCopia, 3);
    EXPECT_EQ(dataset[0]->feature1, copia[0]->feature1);

    destroyDataset(dataset, totalDataset);
    destroyDataset(copia, totalCopia);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}