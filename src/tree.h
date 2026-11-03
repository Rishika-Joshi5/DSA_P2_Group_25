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
        left = nullptr;
        right = nullptr;
    }
    void printNode();
};

class Tree {
    //may not need nutrient variable
    string nutrient;
    Node* root;
    Node* insertHelper(Node* current, Food foodItem);
    Node* removeNode(Node* current);
    void DFSHelper(Node* current);

public:
    Tree(string nutrient) {
        this->nutrient = nutrient;
        this->root = nullptr;
    }
    ~Tree() {
        postorderDeletion(root);
        //might not be necessary, but just to be safe
        root->left = nullptr;
        root->right = nullptr;
        delete root;
    }
    void insert(Food insertFood);
    void buildTreeHelper(string nutrientName, vector<Food> foods);
    void postorderDeletion(Node* current);
    void DFS();
};


#endif //DSA_P2_GROUP_25_TEST_H