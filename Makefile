UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Darwin)
    CXX = clang++
    GTEST_PREFIX := $(shell brew --prefix googletest 2>/dev/null)
    CXXFLAGS = -std=c++17 -Wall -Wextra -g -I$(GTEST_PREFIX)/include
    TEST_LIBS = -L$(GTEST_PREFIX)/lib -lgtest -lgtest_main -pthread
else
    CXX = g++
    CXXFLAGS = -std=c++17 -Wall -Wextra -g
    TEST_LIBS = -lgtest -lgtest_main -pthread
endif

# Seleccionar: Base, RawPtr o Smart
TYPE ?= Base

SRC = DatasetLoader$(TYPE).cpp tests$(TYPE).cpp

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