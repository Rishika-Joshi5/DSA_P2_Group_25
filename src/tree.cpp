#include "tree.h"
#include <string>
#include <iostream>
#include <queue>
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
    return current;
}

void Tree::postorderDeletion(Node* current) {
    if (current == nullptr) {
        return;
    }
    postorderDeletion(current->left);
    postorderDeletion(current->right);
    delete current;
}

void Node::printNode() {
    cout << "Food Type: " << foodItem.getCategory() << endl;
    cout << "Food Name: " << foodItem.getDescription() << endl;
    cout << foodItem.getNutrientAmount() << foodItem.getNutrientUnits() << " of " << foodItem.getNutrientName() << endl;
    cout << endl;
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

//breadth first traversal, printing on the go
void Tree::BFS() {
    if (this->root == nullptr) {
        return;
    }
    queue<Node*> foods;
    foods.push(this->root);
    while (!foods.empty()) {
        Node* current = foods.front();
        foods.pop();
        current->printNode();
        if (current->left != nullptr) {
            foods.push(current->left);
        }
        if (current->right != nullptr) {
            foods.push(current->right);
        }
    }
}

