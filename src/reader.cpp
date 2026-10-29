#include "Food.h"
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

//helper function to help with indexing
//pass the read line and transforms it into an array
vector<std::string> parseLine(const string& line) {
    vector<std::string> fields;
    string specificField;
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
std::vector<Food> readFile(std::string foodCat, std::string nutrName) {
    //make placeholder food object to exist at the root until root is read and inserted
    //make a new variable that makes nutrName be Data.[nutrName] to compare later on.
    //DO NOT CHANGE NUTRNAME, YOU WILL NEED IT FOR LATER
    //also make food vector
    Food placeholder;
    Food lowestVal;
    Food highestVal;
    std::string dataNutrName = "Data." + nutrName;
    std::vector<Food> foods = {placeholder};
    int categoryIndex = 0;
    int descriptionIndex = 1;
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
        //go line by line, getting the category and description first
        //if the new object category is the same as the foodCat passed to the funct, make food obj index 0
        //if there is a root already and the categories are the same, skip
        //if the category is the same as the object most recently pushed into the vector, do not add to vector
        //else, create a new food object with category, description, nutrName, and the actual data of that nutrient


    }


    //close file
    foodFile.close();

    //return vector of food objects
    return foods;
}