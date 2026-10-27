#include "tree.h"
#include <string>
#include <iostream>
using namespace std;

void Tree::insert(int nutrientVal) {
    this->root = insertHelper(root, nutrientVal);
}

Node* Tree::insertHelper(Node* current, int nutrientVal) {
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
