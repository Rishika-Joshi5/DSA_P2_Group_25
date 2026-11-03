#include "tree.h"
#include <string>
#include <iostream>
using namespace std;

void Tree::insert(Food insertFood) {
    //insert Node into tree when Node constructor takes in a food item
    this->root = insertHelper(root, insertFood);
}

Node* Tree::insertHelper(Node* current, Food insertFood) {
    if (current == nullptr) {
        return new Node (insertFood);
    }
    if (insertFood.getNutrientAmount() < current->foodItem.getNutrientAmount()) {
        current->left = insertHelper(current->left, insertFood);
    }
    else if (insertFood.getNutrientAmount() > current->foodItem.getNutrientAmount()) {
        current->right = insertHelper(current->right, insertFood);
    }
    else {
        cout << "could not insert node into tree" << endl;
    }
}

void Tree::buildTreeHelper(string nutrientName, vector<Food> foods) {
    //may not need to take in nutrientName
    for (Food f : foods) {
        insert(f);
    }
}

Node* Tree::removeNode(Node* current) {
    current->left = nullptr;
    current->right = nullptr;
    delete current;
    current = nullptr;
}

void Tree::postorderDeletion(Node* current) {
    if (current == nullptr) {
        return;
    }
    postorderDeletion(current->left);
    postorderDeletion(current->right);
    removeNode(current);
}

void Node::printNode() {
    cout << "Food Type: " << foodItem.getCategory() << endl;
    cout << "Food Name: " << foodItem.getDescription() << endl;
    cout << "Nutrient Amount: " << foodItem.getNutrientAmount();
    //need units for each nutrient amount in each food
    cout << " units" << " of " << foodItem.getNutrientName() << endl;
}

//inorder traversal, printing on the go
void Tree::DFSHelper(Node* current) {
    if (current == nullptr) {
        return;
    }
    DFSHelper(current->left);
    current->printNode();
    DFSHelper(current->right);
}

void Tree::DFS() {
    DFSHelper(root);
}