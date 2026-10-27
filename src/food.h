#ifndef DSA_P2_GROUP_25_FOOD_H
#define DSA_P2_GROUP_25_FOOD_H
#include <string>

//food class. if we feel like it, we could make it part of the tree file or keep it like this

class Food {
    std::string category;
    std::string description;
    std::string nutrientName;
    float nutrientAmount;

public:
    Food(std::string foodCat, std::string foodDesc, std::string foodNutrName, float foodNutrAmt);
};


#endif //DSA_P2_GROUP_25_FOOD_H