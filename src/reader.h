#ifndef DSA_P2_GROUP_25_READER_H
#define DSA_P2_GROUP_25_READER_H
#include "food.h"
#include <string>
#include <vector>

Food findNutrientMax(std::vector<Food>& foods);
Food findNutrientMin(std::vector<Food>& foods);
float findDifference(Food food1, Food food2);
int findIndex(std::vector<Food>& foods, Food target);
std::vector<std::string> parseLine(const std::string& line);
std::vector<Food> readFile(std::string foodCat, std::string nutrName, int altAmount);

#endif //DSA_P2_GROUP_25_READER_H