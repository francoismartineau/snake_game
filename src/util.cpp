#include <vector>
#include <algorithm>
#include <random>
#include "util.h"

void shuffleVector(std::vector<std::pair<size_t, size_t>> nodes)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::shuffle(nodes.begin(), nodes.end(), gen);
}