//cards.cpp
//Hechenjin Yu, Ruijie Tao
#include "cards.h"

using namespace std;

// Card comparison considering suit and value
bool Card::operator<(const Card& other) const {
    if (suit != other.suit) {
        static const std::string suitOrder = "cdsh";
        return suitOrder.find(suit) < suitOrder.find(other.suit);
    }

    if (value == other.value) return false;

    static const std::string valueOrder = "a234567891jqk";  // '1' represents '10'
    return valueOrder.find(value[0]) < valueOrder.find(other.value[0]);
}

bool Card::operator>(const Card& other) const {
    return other < *this;
}

bool Card::operator==(const Card& other) const {
    return suit == other.suit && value == other.value;
}

bool Card::operator!=(const Card& other) const {
    return suit != other.suit || value != other.value;
}

// CardBST Destructor
CardBST::~CardBST() {
    destroyTree(root);
}

// Insert a card
void CardBST::insert(const Card& card) {
    insertHelper(root, card);
}

void CardBST::insertHelper(Node*& node, const Card& card) {
    if (node == nullptr) {
        node = new Node(card);
    } else if (card < node->card) {
        insertHelper(node->left, card);
    } else if (card > node->card) {
        insertHelper(node->right, card);
    }
    // If the card is equal, no insertion (assuming no duplicates)
}

// Find a card
bool CardBST::find(const Card& card) const {
    Node* current = root;
    while (current != nullptr) {
        if (card == current->card) {
            return true;
        } else if (card < current->card) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    return false;
}

// Remove a card
void CardBST::remove(const Card& card) {
    root = removeHelper(root, card);
}

Node* CardBST::removeHelper(Node* node, const Card& card) {
    if (node == nullptr) return node;

    if (card < node->card) {
        node->left = removeHelper(node->left, card);
    } else if (card > node->card) {
        node->right = removeHelper(node->right, card);
    } else {
        if (node->left == nullptr) {
            Node* temp = node->right;
            delete node;
            return temp;
        } else if (node->right == nullptr) {
            Node* temp = node->left;
            delete node;
            return temp;
        }

        Node* temp = findMinHelper(node->right);
        node->card = temp->card;
        node->right = removeHelper(node->right, temp->card);
    }
    return node;
}

Card CardBST::findMin() const {
    Node* node = findMinHelper(root);
    if (node) {
        return node->card;
    }
    return Card(); // Return an empty card if the BST is empty
}

// Public interface to find the maximum card
Card CardBST::findMax() const {
    Node* node = findMaxHelper(root);
    if (node) {
        return node->card;
    }
    return Card(); // Return an empty card if the BST is empty
}

Node* CardBST::findMinHelper(Node* node) const {
    Node* current = node;
    while (current && current->left != nullptr) {
        current = current->left;
    }
    return current;
}

Node* CardBST::findMaxHelper(Node* node) const {
    Node* current = node;
    while (current && current->right != nullptr) {
        current = current->right;
    }
    return current;
}

Card CardBST::findSuccessor(const Card& card) const {
    Node* current = root;
    Node* successor = nullptr;

    // Step 1: Find the node (if it exists) in the BST
    while (current != nullptr && current->card != card) {
        if (card < current->card) {
            successor = current;
            current = current->left;
        } else {
            current = current->right;
        }
    }

    // If the node doesn't exist in the tree, return an empty card
    if (current == nullptr) {
        return Card();
    }

    // Step 2: If the node has a right child, find the minimum in the right subtree
    if (current->right != nullptr) {
        successor = findMinHelper(current->right);
    }

    // If there is no successor, return an empty card
    if (successor == nullptr) {
        return Card();
    }

    return successor->card;
}

Card CardBST::findPredecessor(const Card& card) const {
    Node* current = root;
    Node* predecessor = nullptr;

    // Step 1: Find the node (if it exists) in the BST
    while (current != nullptr && current->card != card) {
        if (card > current->card) {
            predecessor = current;
            current = current->right;
        } else {
            current = current->left;
        }
    }

    // If the node doesn't exist in the tree, return an empty card
    if (current == nullptr) {
        return Card();
    }

    // Step 2: If the node has a left child, find the maximum in the left subtree
    if (current->left != nullptr) {
        predecessor = findMaxHelper(current->left);
    }

    // If there is no predecessor, return an empty card
    if (predecessor == nullptr) {
        return Card();
    }

    return predecessor->card;
}

// Print in-order
void CardBST::printInOrder() const {
    printInOrderHelper(root);
}

void CardBST::printInOrderHelper(Node* node) const {
    if (node != nullptr) {
        printInOrderHelper(node->left);
        std::cout << node->card.suit << " " << node->card.value << std::endl;
        printInOrderHelper(node->right);
    }
}

// Destroy the tree
void CardBST::destroyTree(Node* node) {
    if (node != nullptr) {
        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }
}
