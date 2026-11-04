#include "food.h"
#include "tree.h"
#include "reader.h"
#include <ctime>
#include <iostream>
using namespace std;




void timingTest() {
    vector<Food> foods = readFile("Milk", "Protein", 100000);
    if (foods.empty()) {
        cerr << "readFile has gave no foods, can't run test." << endl;
        return;
    }

    Tree tree("protein");
    for (int i = 0; i < foods.size(); i++) {
        tree.insert(foods[i]);
    }

    //time DFS
    clock_t dfsStart = clock();
    tree.DFS();
    clock_t dfsEnd = clock();

    //calculate time
    double dfsMs = (dfsEnd - dfsStart) * 1000.0 / CLOCKS_PER_SEC;

    //time BSF
    clock_t bsfStart = clock();
    tree.BFS();
    clock_t bsfEnd = clock();
    double bfsMs = (bsfEnd - bsfStart) * 1000.0 / CLOCKS_PER_SEC;

    cout << "DFS time: " << dfsMs << " ms" << endl;
    cout << "BFS time: " << bfsMs << " ms" << endl;
}

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

    // Food milk("milk", "milk by itself", "protein", 2.50, "g");
    // Food tofu("tofu", "tofu with beans", "protein", 3.00, "g");
    // Food beans("beans", "pinto beans", "protein", 1.0, "g");
    // Food iceCream("ice cream", "vanilla ice cream", "protein", 7.0, "mcg");
    // Tree myTree("protein");
    // myTree.insert(milk);
    // myTree.insert(tofu);
    // myTree.insert(beans);
    // myTree.insert(iceCream);
    // myTree.DFS();

    timingTest();
    return 0;
}