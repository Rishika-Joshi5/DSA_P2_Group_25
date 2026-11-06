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
    timingTest();
    return 0;
}
