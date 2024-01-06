#include <conio.h>
#include <vector>
#include <algorithm>
#include <random>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
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

// -- File --
std::string	createFileName(const std::string &baseFileName, int number, const std::string &fileExtension)
{
    std::ostringstream oss;
    oss << baseFileName << std::setfill('0') << std::setw(2) << number << fileExtension;
    return oss.str();
}

bool fileExists(const std::string &baseFileName, int number, const std::string &fileExtension)
{
	std::string fileName = createFileName(baseFileName, number, fileExtension);
	std::ifstream fileCheck(fileName);
	if (!fileCheck.good())
		return true;
	return false;
}

std::ofstream createFile(const std::string &baseFileName, const std::string &fileExtension)
{
    int number = 0;
	while (fileExists(baseFileName, number, fileExtension))
		++number;
    std::string fileName = createFileName(baseFileName, number, fileExtension);
    std::ofstream outFile(fileName);

    if (outFile.is_open()) {
        outFile << "This is the content of " << fileName << std::endl;
        outFile.close();
        std::cout << "File " << fileName << " has been created for writing." << std::endl;
    } else {
        std::cerr << "Failed to open " << fileName << " for writing." << std::endl;
    }
	return outFile;
}


void waitForEnterKey()
{
    while (1)
    {
        char key = _getch();
        switch (key)
        {
        case ENTER_KEY:
            return;
        case keyQuit:
            std::exit(0);
        }
    }
}
