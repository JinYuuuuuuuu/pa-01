// intbst.cpp
// Implements class IntBST
// Hechenjin Yu
// Wed Oct 25

#include "intbst.h"

#include <iostream>
using std::cout;

// constructor sets up empty tree
IntBST::IntBST() { 
    //info = 0;
    //left = right = parent = nullptr;
    root = nullptr;
}

// destructor deletes all nodes
IntBST::~IntBST() {
    clear(root);
}

// recursive helper for destructor
void IntBST::clear(Node *n) {
    if (n == nullptr){
        return;
    }
    clear(n->left);
    clear(n->right);
    delete n;
}

// insert value in tree; return false if duplicate
bool IntBST::insert(int value) {
    if (!root){
        root = new Node(value);
        return true;
    }
    return insert(value, root);
}

// recursive helper for insert (assumes n is never 0)
bool IntBST::insert(int value, Node *n) {
    if (n->info == value){
            return false;
    }
    else if (n->info > value) {
        if (n->left == nullptr) {
            n->left = new Node(value);
            n->left->parent = n;
            return true;
        }
        return insert(value, n->left);
    }
    else {
        if (n->right == nullptr) {
            n->right = new Node(value);
            n->right->parent = n;
            return true;
        }
        return insert(value, n->right);
    }
}

// print tree data pre-order
void IntBST::printPreOrder() const {
    printPreOrder(root);
}

// recursive helper for printPreOrder()
void IntBST::printPreOrder(Node *n) const {
    if (n == nullptr){
        return;
    }
    cout << n->info << " ";
    printPreOrder(n->left);
    printPreOrder(n->right);
}

// print tree data in-order, with helper
void IntBST::printInOrder() const {
    printInOrder(root);
}
void IntBST::printInOrder(Node *n) const {
    if (n == nullptr){
        return;
    }
    printInOrder(n->left);
    cout << n->info << " ";
    printInOrder(n->right);
}

// prints tree data post-order, with helper
void IntBST::printPostOrder() const {
    printPostOrder(root);
}

void IntBST::printPostOrder(Node *n) const {
    if (n == nullptr){
        return;
    }
    printPostOrder(n -> left);
    printPostOrder(n->right);
    cout << n->info << " ";
}

// return sum of values in tree
int IntBST::sum() const {
    return sum(root);
}

// recursive helper for sum
int IntBST::sum(Node *n) const {
    if (n == nullptr){
        return 0;
    }
    return n->info + sum(n->left) + sum(n->right);
}

// return count of values
int IntBST::count() const {
    return count(root);
}

// recursive helper for count
int IntBST::count(Node *n) const {
    if (n==nullptr){
        return 0;
    }
    return 1 + count(n->left) + count(n->right);
}

// IMPLEMENT THIS FIRST: returns the node for a given value or NULL if none exists
// Parameters:
// int value: the value to be found
// Node* n: the node to start with (for a recursive call)
// Whenever you call this method from somewhere else, pass it
// the root node as "n"
IntBST::Node* IntBST::getNodeFor(int value, Node* n) const{
    if (n == nullptr){
        return NULL;
    }
    if (n->info == value){
        return n;
    }
    else if (n->info < value){
        return getNodeFor(value, n->right);
    }
    else{
        return getNodeFor(value, n->left);
    }
}

// returns true if value is in the tree; false if not
bool IntBST::contains(int value) const {
    return getNodeFor(value, root) != nullptr;
}

// returns the Node containing the predecessor of the given value
IntBST::Node* IntBST::getPredecessorNode(int value) const{
    Node* target = getNodeFor(value, root);
    if (target == NULL){
        return NULL;
    }

    if (target->left){
        target = target->left;
        while (target->right){
            target = target->right;
        }
        return target;
    }

    while(target->parent && target->parent->left == target){
        target = target->parent;
    }
    return target->parent;
}

// returns the predecessor value of the given value or 0 if there is none
int IntBST::getPredecessor(int value) const{
    Node* target = getPredecessorNode(value);
    if (target == NULL){
        return 0;
    }
    return target->info;
}

// returns the Node containing the successor of the given value
IntBST::Node* IntBST::getSuccessorNode(int value) const{
    Node* target = getNodeFor(value, root);
    if (!target) {
        return NULL;
    }

    if (target->right) {
        target = target->right;
        while (target->left) {
            target = target->left;
        }
        return target;
    }

    while (target->parent && target->parent->right == target) {
        target = target->parent;
    }
    return target->parent;
}

// returns the successor value of the given value or 0 if there is none
int IntBST::getSuccessor(int value) const{
    Node* succNode = getSuccessorNode(value);
    return succNode ? succNode->info : 0;
}

/*
// deletes the Node containing the given value from the tree
// returns true if the node exist and was deleted or false if the node does not exist
bool IntBST::remove(int value){
    Node* target = getNodeFor(value, root);
    if (!target) return false;

    // Node with only one child or no child 
    if (!target->left) {
        Node* temp = target->right;
        *target = *temp;
        delete temp;
    }
    else if (!target->right) {
        Node* temp = target->left;
        *target = *temp;
        delete temp;
    }

    // Node with two children:
    else {
        Node* temp = getSuccessorNode(value);
        target->info = temp->info;
        Node* tempChild = temp->right;
        if (temp->parent->left == temp) temp->parent->left = tempChild;
        else temp->parent->right = tempChild;
        if (tempChild) tempChild->parent = temp->parent;
        delete temp;
    }

    return true;
}
*/
bool IntBST::remove(int value) {
    Node* target = getNodeFor(value, root);
    if (!target) return false;

    // Node with only one child or no child
    if (!target->left || !target->right) {
        Node* child = target->left ? target->left : target->right;

        // If target is the root
        if (!target->parent) {
            root = child;
        } else {
            if (target == target->parent->left) {
                target->parent->left = child;
            } else {
                target->parent->right = child;
            }
        }

        if (child) {
            child->parent = target->parent;
        }
        delete target;
    } 
    // Node with two children
    else {
        Node* temp = getSuccessorNode(value);
        target->info = temp->info;

        // Remove the successor (note that the successor will always have at most one child)
        Node* tempChild = temp->right;

        if (temp->parent->left == temp) {
            temp->parent->left = tempChild;
        } else {
            temp->parent->right = tempChild;
        }

        if (tempChild) {
            tempChild->parent = temp->parent;
        }
        delete temp;
    }

    return true;
}
