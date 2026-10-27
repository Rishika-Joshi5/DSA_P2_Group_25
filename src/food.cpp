#include "food.h"
using namespace std;

Food::Food(string foodCat, string foodDesc, string foodNutrName, float foodNutrAmt) {
    category = foodCat;
    description = foodDesc;
    nutrientName = foodNutrName;
    nutrientAmount = foodNutrAmt;
}