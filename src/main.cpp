#include "food.h"
#include "tree.h"
#include "reader.h"
#include <iostream>
using namespace std;

int main() {
    //DEBUGGING READER.CPP!!!!
    //run DSA_P2_Group_25 instead of main.cpp for this
    //
    // //cat: Milk, nutr: Protein, amt: 10
    // vector<Food> testVec1 = readFile("Milk", "Protein", 10);
    // for (Food curr : testVec1) {
    //     cout << curr.getNutrientUnits() << endl;
    //     cout << curr.getCategory() << " " << curr.getDescription() << " " << curr.getNutrientAmount() << curr.getNutrientUnits() << endl;
    // }

    //are you guys also getting a SIGILL
    //debugging insertion: the tree looks correct, but then I get an illegal instruction signal
    Food milk("milk", "milk by itself", "protein", 2.50, "g");
    Food tofu("tofu", "tofu with beans", "protein", 3.00, "g");
    Tree myTree("protein");
    myTree.insert(milk);
    myTree.insert(tofu);
    //myTree.DFS();

    return 0;
}