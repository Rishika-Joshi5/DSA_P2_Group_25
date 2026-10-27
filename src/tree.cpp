#include "tree.h"
#include <string>
#include <iostream>
using namespace std;

void Tree::insert(float nutrientVal) {
    this->root = insertHelper(root, nutrientVal);
}

Node* Tree::insertHelper(Node* current, float nutrientVal) {
    if (current == nullptr) {
        return new Node (nutrientVal);
    }
    else if (nutrientVal < current->nutrientValue) {
        current->left = insertHelper(current->left, nutrientVal);
    }
    else if (nutrientVal > current->nutrientValue) {
        current->right = insertHelper(current->right, nutrientVal);
    }
    else {
        cout << "could not insert" << endl;
    }
}

void Tree::buildTreeHelper(string nutrientName, vector<Food> foods) {
    for (Food f : foods) {
        insert(f.getNutrientAmount());
    }
}