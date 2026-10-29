#include "Food.h"
#include <string>
#include <vector>
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

//helper function to get difference of food item nutrient amount
float getDifference(Food food1, Food food2) {
    float difference = food1.getNutrientAmount() - food2.getNutrientAmount();
    //want difference to be positive, so checking if negative and converting
    if (difference < 0) {
        difference = difference * -1;
    }
    return difference;
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
    Food placeholder; //placeholder food object to exist at the root until root is read and inserted
    std::string dataNutrName = "Data." + nutrName; //makes nutrName be Data.[nutrName] to compare later on.
    std::vector<Food> foods = {placeholder}; //what will be returned
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


    //NOT FUNCTIONAL YET
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

        //checking if root, adding to first index!
        if (currFood.getCategory() == foodCat) {
            foods.front() = currFood;
        }
        //checking if vector ISN'T FULL, insert regularly
        else if (vectorCurrAmount < vectorTotalAmount) {
            foods.push_back(currFood);
        }
        //vector is full, replacing furthest items
        else {

        }


    }


    //close file
    foodFile.close();

    //return vector of food objects
    return foods;
}