#include "Food.h"
#include <string>
#include <vector>
//function that reads the file and creates food items based on whatever nutrient is chosen
//also includes the food that will be at the root of the tree
//have not started yet

std::vector<Food> readFile(std::string foodName,std::string nutrName) {
    //make a new variable that makes nutrName be Data.[nutrName] to compare later on.
    //DO NOT CHANGE NUTRNAME, YOU WILL NEED IT FOR LATER

    //open file

    //read line with all the keys
    //get the index of category, description, and the nutrient type based on Data.[nutrName]
    //make nutrientName of all food items the same as nutrName passed to function

    //first, find the specific food item in order to add it as the root (first value of vector)

    //go line by line, getting the category and description first
    //if the category is the same as the item most recently pushed into the vector, do not add to vector
    //else, create a new food item with category, description, nutrName, and the actual data of that nutrient


    //close file

    //return vector of food items
    return {};
}