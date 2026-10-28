#ifndef DSA_P2_GROUP_25_TEST_H
#define DSA_P2_GROUP_25_TEST_H
#include "food.h"
#include <string>
#include <vector>
using namespace std;

struct Node {
    Food foodItem;
    Node* left;
    Node* right;

    //Node constructor now takes in a Food object
    Node(Food foodItem) {
        this->foodItem = foodItem;
        this->left = nullptr;
        this->right = nullptr;
    }
};

class Tree {
    string nutrient;
    Node* root;
    Node* insertHelper(Node* current, Food foodItem);

public:
    Tree(string nutrient) {
        this->nutrient = nutrient;
        this->root = nullptr;
    }
    void insert(Food insertFood);
    void buildTreeHelper(string nutrientName, vector<Food> foods);
};


#endif //DSA_P2_GROUP_25_TEST_H