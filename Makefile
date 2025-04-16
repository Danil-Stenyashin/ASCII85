CXX = g++
CXXFLAGS = -Wall -Wextra -pedantic -std=c++17 -O3
GTEST_FLAGS = -pthread -lgtest -lgtest_main

SRC = main.cpp encoder.cpp decoder.cpp
OBJ = $(SRC:.cpp=.o)
EXEC = ascii85

TEST_SRC = tests.cpp encoder.cpp decoder.cpp
TEST_OBJ = $(TEST_SRC:.cpp=.o)
TEST_EXEC = test_cpp

HEADERS = encoder.h decoder.h

.PHONY: all clean test run

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(EXEC)
	./$(EXEC)

test: $(TEST_EXEC)
	@echo "Running tests"
	./$(TEST_EXEC)

$(TEST_EXEC): $(TEST_OBJ)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(GTEST_FLAGS)

clean:
	rm -f *.o $(EXEC) $(TEST_EXEC)

