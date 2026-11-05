#include "reader.h"
#include "tree.h"
#include <iostream>
using namespace std;
//prints as text so ui.py and read

int main(int argc, char*, argv[]){
    //checks to make sure there are no missing arguments
    if (argc < 4) {
        cout << "usage: ui <category> <nutrient> <count>" << endl;
        return 1;
    }

    string category = argv[1];
    string nutrient = argv[2];
    int count = stoi(argv[3]);

    vector<Food> foods = readFile(category, nutrient, count);

    if (foods.empty()){
        count << "readFile returns no foods" << endl;
        return 1;
    }

    //food[0] is the food the user picks
    cout<<"ROOT|" << foods[0].getCategory() << "|" << foods[0].getDescription() << "|"
        << foods[0].getNutrientAmount() << "|" << foods[0].getNutrientUnits() << endl;

    Tree tree(nutrient);
    for (int i = 0; i < foods.size(); i++) {
        tree.insert(foods[i]);
    }
}