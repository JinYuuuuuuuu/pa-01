#include "cards.h"

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

        Node* temp = findMin(node->right);
        node->card = temp->card;
        node->right = removeHelper(node->right, temp->card);
    }
    return node;
}

Node* CardBST::findMin(Node* node) const {
    Node* current = node;
    while (current && current->left != nullptr) {
        current = current->left;
    }
    return current;
}

// Print in-order
void CardBST::printInOrder() const {
    printInOrderHelper(root);
}

void CardBST::printInOrderHelper(Node* node) const {
    if (node != nullptr) {
