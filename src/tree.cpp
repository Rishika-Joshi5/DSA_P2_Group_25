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

//inorder traversal, printing on the go
void Tree::DFS(Node* current) {
    if (current == nullptr) {
        return;
    }
    DFS(current->left);
    cout << current->foodItem.getNutrientAmount() << endl;
    DFS(current->right);
}