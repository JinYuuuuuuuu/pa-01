//cards.h
//Hechenjin Yu, Ruijie Tao
#ifndef CARDS_H
#define CARDS_H

#include <iostream>
#include <string>

using namespace std;

// Card struct
struct Card {
    string suit;
    string value;

    Card(string s = "", string v = "") : suit(s), value(v) {}

    bool operator<(const Card& other) const;
    bool operator>(const Card& other) const;
    bool operator==(const Card& other) const;
    bool operator!=(const Card& other) const;

    bool isEmpty() const {
        return suit.empty() && value.empty();
    }
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
        Card findSuccessor(const Card& card) const;
        Card findPredecessor(const Card& card) const;
        void printInOrder() const;
        Card findMin() const;
        Card findMax() const;

    private:
        Node* root;
        void insertHelper(Node*& node, const Card& card);
        Node* removeHelper(Node* node, const Card& card);
        void printInOrderHelper(Node* node) const;
        Node* findMinHelper(Node* node) const;
        Node* findMaxHelper(Node* node) const;
        void destroyTree(Node* node);
};

#endif // CARDS_H
