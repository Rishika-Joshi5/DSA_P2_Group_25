#ifndef DSA_P2_GROUP_25_TEST_H
#define DSA_P2_GROUP_25_TEST_H
#include <string>
using namespace std;

struct Node {
    int nutrientValue;
    Node* left;
    Node* right;

    Node(int nutrientValue) {
        this->nutrientValue = nutrientValue;
        this->left = nullptr;
        this->right = nullptr;
    }
};

class Tree {
    string nutrient;
    Node* root;
    Node* insertHelper(Node* current, int nutrientVal);
public:
    Tree(string nutrient) {
        this->nutrient = nutrient;
        this->root = nullptr;
    }
    void insert(int nutrientVal);
};


#endif //DSA_P2_GROUP_25_TEST_H