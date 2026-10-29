#include "food.h"
#include "tree.h"
#include "reader.h"
#include <iostream>
using namespace std;

int main() {
    //DEBUGGING READER.CPP!!!!

    //cat: Milk, nutr: Protein, amt: 10
    vector<Food> testVec1 = readFile("Milk", "Protein", 10);
    for (Food curr : testVec1) {
        cout << curr.getCategory() << " " << curr.getDescription() << " " << curr.getNutrientAmount() << endl;
    }


    return 0;
}