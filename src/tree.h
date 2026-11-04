#ifndef DSA_P2_GROUP_25_TEST_H
#define DSA_P2_GROUP_25_TEST_H
#include "food.h"
#include <string>
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
    Node* root = nullptr;
    Node* insertHelper(Node* current, Food foodItem);
    void DFSHelper(Node* current);

public:
    Tree(string nutrient) {
        this->nutrient = nutrient;
    }
    ~Tree() {
        postorderDeletion(root);
        root = nullptr;
    }
    void insert(Food insertFood);
    void postorderDeletion(Node* current);
    void DFS();
    void BFS();
};


#endif //DSA_P2_GROUP_25_TEST_H