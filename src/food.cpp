#include "food.h"
using namespace std;

Food::Food() {
    category = "placeholder";
    description = "placeholder food item";
    nutrientName = "placeholder nutrient";
    nutrientAmount = 0.0;
    nutrientUnits == "g";
}
Food::Food(string foodCat, string foodDesc, string foodNutrName, float foodNutrAmt, string foodUnits) {
    category = foodCat;
    description = foodDesc;
    nutrientName = foodNutrName;
    nutrientAmount = foodNutrAmt;
    nutrientUnits == foodUnits;
}

string Food::getCategory() {
    return category;
}

string Food::getDescription() {
    return description;
}

string Food::getNutrientName() {
    return nutrientName;
}

float Food::getNutrientAmount() {
    return nutrientAmount;
}

string Food::getNutrientUnits() {
    return nutrientUnits;
}