#include "reader.h"
#include <fstream>
#include <iostream>

//helper function to get max food object in certain nutrient amount
Food findNutrientMax(std::vector<Food>& foods) {
    int index = -1;
    float maxAmount = -1;
    for (int i=0; i<foods.size(); i++) {
        if (foods[i].getNutrientAmount() > maxAmount) {
            index = i;
            maxAmount = foods[i].getNutrientAmount();
        }
    }
    return foods[index];
}

//helper function to get min food object in certain nutrient amount
Food findNutrientMin(std::vector<Food>& foods) {
    int index = -1;
    float minAmount = 100000.0; //placeholder value
    for (int i=0; i<foods.size(); i++) {
        if (foods[i].getNutrientAmount() < minAmount) {
            index = i;
            minAmount = foods[i].getNutrientAmount();
        }
    }
    return foods[index];
}

//helper function to get difference of food item nutrient amounts
float findDifference(Food food1, Food food2) {
    float difference = food1.getNutrientAmount() - food2.getNutrientAmount();
    //want difference to be positive, so checking if negative and converting
    if (difference < 0) {
        difference = difference * -1;
    }
    return difference;
}

//helper function to find where specific food item is in food vector
int findIndex(std::vector<Food>& foods, Food target) {
    for (int i=0; i<foods.size(); i++) {
        if (foods[i].getDescription() == target.getDescription()) {
            return i;
        }
    }
    return -1;
}


//helper function to help with indexing
//pass the read line and transforms it into an array
std::vector<std::string> parseLine(const std::string& line) {
    std::vector<std::string> fields;
    std::string specificField;
    bool inQuotes = false;
    for (size_t i=0; i<line.length(); i++) {
        char c = line[i];

        //quotes
        if (c == '"') {
            //incase there's double quotes
            if (inQuotes && i+1<line.size() && line[i+1] == '"') {
               specificField += '"';
                i++;
            }
            else {
                inQuotes = !inQuotes;
            }
        }
        //comma not inside quotes
        else if (c == ',' && !inQuotes) {
            fields.push_back(specificField);
            specificField.clear();
        }
        //regular character
        else {
            specificField += c;
        }
    }
    fields.push_back(specificField);
    return fields;
}


//function that reads the file and creates food objects based on whatever nutrient is chosen
//also includes the food that will be at the root of the tree

//should return at least one value, the root.
//if returns an empty array, error has occured.

//THIS IS FAR FROM DONE BTW
std::vector<Food> readFile(std::string foodCat, std::string nutrName, int altAmount) {
    std::string dataNutrName = "Data." + nutrName; //makes nutrName be Data.[nutrName] to compare later on.
    std::vector<Food> foods = {}; //what will be returned
    int vectorTotalAmount = altAmount + 1;
    int vectorCurrAmount = 1;
    int nutrientIndex = -1;

    //open file
    std::ifstream foodFile("../resources/food.csv");

    //check if file is open
    if (!foodFile.is_open()) {
        std::cerr << "Error opening food.csv" << std::endl;
        return {};
    }

    std::string line;

    //read line with all the keys
    //get the index of category, description, and the nutrient type based on Data.[nutrName]
    //make nutrientName of all food objects the same as nutrName passed to function
    std::getline(foodFile, line);
    std::vector<std::string> headers = parseLine(line);
    for (int i=0; i<headers.size(); i++) {
        if (headers[i] == dataNutrName) {
            nutrientIndex = i;
            break;
        }
    }

    //check if data.nutr exists
    if (nutrientIndex == -1) {
        std::cerr << "Error finding nutrient" << std::endl;
        return {};
    }

    //FIRST we NEED to get the root.
    //we need it there so that we can compare it to future items incase it's very far down
    while (std::getline(foodFile, line)) {
        std::vector<std::string> currFoodStats = parseLine(line);
        if (currFoodStats[0] == foodCat) {
            Food root(currFoodStats[0], currFoodStats[1], nutrName, std::stof(currFoodStats[nutrientIndex]));
            foods.push_back(root);
            break;
        }
    }

    //resetting reader pointer
    foodFile.clear();
    foodFile.seekg(0, std::ios::beg);

    std::string dummy;
    std::getline(foodFile, dummy); //to skip headers

    //reading over to make list for tree implementation
    while (std::getline(foodFile, line)) {
        //go line by line, getting stats for current food item
        std::vector<std::string> currFoodStats = parseLine(line);
        Food currFood(currFoodStats[0], currFoodStats[1], nutrName, std::stof(currFoodStats[nutrientIndex]));

        //check if categories are the same. if is, move to next line
        for (int i=0; i<foods.size(); i++) {
            if (currFood.getCategory() == foods[i].getCategory()) {
                continue;
            }
        }

        //adding to foods vector

        //checking if root, ignore
        if (currFood.getCategory() == foodCat) {
            continue;
        }
        //checking if vector ISN'T FULL, insert regularly and increment vectorCurrAmount
        else if (vectorCurrAmount < vectorTotalAmount) {
            foods.push_back(currFood);
            vectorCurrAmount++;
        }
        //vector is full, replacing furthest items from root
        else {
            //first check if same/higher than root (MAX SCENARIO)
            if (currFood.getNutrientAmount() >= foods[0].getNutrientAmount()) {
                //if curr is closer to root than max, replace
                int maxIndex = findIndex(foods, findNutrientMax(foods));
                if (findDifference(foods[0], currFood) < findDifference(foods[0], foods[maxIndex])) {
                    foods.erase(foods.begin() + maxIndex);
                    foods.push_back(currFood);
                }
            }
            //less than root amount (MIN SCENARIO)
            else {
                //if curr is closer to root than min, replace
                int minIndex = findIndex(foods, findNutrientMin(foods));
                if (findDifference(foods[0], currFood) < findDifference(foods[0], foods[minIndex])) {
                    foods.erase(foods.begin() + minIndex);
                    foods.push_back(currFood);
                }
            }

        }
    }


    //close file
    foodFile.close();

    //return vector of food objects with nutrName nutrients, of altAmount amount
    return foods;
}