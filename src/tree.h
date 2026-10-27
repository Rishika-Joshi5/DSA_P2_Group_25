#ifndef DSA_P2_GROUP_25_TEST_H
#define DSA_P2_GROUP_25_TEST_H
#include "food.h"
#include <string>
#include <vector>
using namespace std;

struct Node {
    float nutrientValue;
    Node* left;
    Node* right;

    Node(float nutrientValue) {
        this->nutrientValue = nutrientValue;
        this->left = nullptr;
        this->right = nullptr;
    }
};

class Tree {
    string nutrient;
    Node* root;
    Node* insertHelper(Node* current, float nutrientVal);
    void buildTreeHelper(string nutrientName, vector<Food> foods);
public:
    Tree(string nutrient) {
        this->nutrient = nutrient;
        this->root = nullptr;
    }
    void insert(float nutrientVal);
};


#endif //DSA_P2_GROUP_25_TEST_H