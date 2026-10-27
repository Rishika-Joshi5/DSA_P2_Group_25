#include "Food.h"
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
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
    std::string dataNutrName = "Data." + nutrName;
    std::vector<Food> foods = {placeholder};

    //open file
    std::ifstream foodFile("../resources/food.csv");

    //check if file is open
    if (!foodFile.is_open()) {
        std::cerr << "Error opening food.csv" << std::endl;
        return {};
    }

    //read line with all the keys
    //get the index of category, description, and the nutrient type based on Data.[nutrName]
    //make nutrientName of all food objects the same as nutrName passed to function

    //NOT FUNCTIONAL YET
    while (false) {
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