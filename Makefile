UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Darwin)
    CXX = clang++
else
    CXX = g++
endif

CXXFLAGS = -std=c++17 -Wall -Wextra -g

# Asume que Google Test está instalado en el sistema
# Ubuntu/Debian: sudo apt-get install libgtest-dev libgmock-dev
TEST_LIBS = -lgtest -lgtest_main -pthread

SRC = DatasetLoader.cpp tests.cpp
TARGET = run_tests

all: build

build: $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET) $(TEST_LIBS)

test: build
	./$(TARGET)

valgrind: build
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(TARGET)

clean:
	rm -f $(TARGET) dataset_test.csv subset_virtual.csv
