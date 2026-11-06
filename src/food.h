#ifndef DSA_P2_GROUP_25_FOOD_H
#define DSA_P2_GROUP_25_FOOD_H
#include <string>

class Food {
    std::string category;
    std::string description;
    std::string nutrientName;
    float nutrientAmount;
    std::string nutrientUnits;

public:
    Food();
    Food(std::string foodCat, std::string foodDesc, std::string foodNutrName, float foodNutrAmt, std::string foodUnits);
    std::string getCategory();
    std::string getDescription();
    std::string getNutrientName();
    float getNutrientAmount();
    std::string getNutrientUnits();
};


#endif //DSA_P2_GROUP_25_FOOD_H
