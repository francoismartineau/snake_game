#include <vector>
#include <algorithm>
#include <random>
#include "util.h"

// template <typename T>
void shuffleVector(std::vector<Direction> &vec)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::shuffle(vec.begin(), vec.end(), gen);
}

void printVector(const std::vector<Direction>& vec)
{
    for (const Direction& element : vec) {
        std::cout << element << ' ';
    }
    std::cout << std::endl;
}