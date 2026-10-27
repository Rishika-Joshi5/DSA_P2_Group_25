#include "food.h"
using namespace std;

Food::Food() {
    category = "placeholder";
    description = "placeholder food item";
    nutrientName = "placeholder nutrient";
    nutrientAmount = 0.0;
}
Food::Food(string foodCat, string foodDesc, string foodNutrName, float foodNutrAmt) {
    category = foodCat;
    description = foodDesc;
    nutrientName = foodNutrName;
    nutrientAmount = foodNutrAmt;
}

float Food::getNutrientAmount() {
    return nutrientAmount;
}