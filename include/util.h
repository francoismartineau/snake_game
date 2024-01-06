#ifndef UTIL_H_
#define UTIL_H_

#include <vector>
#include "define.h"

void shuffleVector(std::vector<Direction> &vec);
void printVector(const std::vector<Direction>& vec);
std::ofstream createFile(const std::string &baseFileName, const std::string &fileExtension);
void waitForEnterKey();

#endif /* UTIL_H_ */
