#ifndef CARDS_H
#define CARDS_H

#include <iostream>
#include <string>

// Card struct
struct Card {
    std::string suit;
    std::string value;

    Card(std::string s, std::string v) : suit(s), value(v) {}

    bool operator<(const Card& other) const;
    bool operator>(const Card& other) const;
    bool operator==(const Card& other) const;
};

// Node struct for BST
struct Node {
    Card card;
    Node* left;
    Node* right;

    Node(Card c) : card(c), left(nullptr), right(nullptr) {}
};

// Binary Search Tree for Cards
class CardBST {
public:
    CardBST() : root(nullptr) {}
    ~CardBST();

    void insert(const Card& card);
    bool find(const Card& card) const;
    void remove(const Card& card);
    void printInOrder() const;

private:
    Node* root;

    void insertHelper(Node*& node, const Card& card);
    Node* removeHelper(Node* node, const Card& card);
    Node* findMin(Node* node) const;
    void printInOrderHelper(Node* node) const;
    void destroyTree(Node* node);
};

#endif // CARDS_H
