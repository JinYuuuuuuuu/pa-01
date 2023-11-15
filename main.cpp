#include <iostream>
#include <fstream>
#include <sstream>
#include "cards.h"

using namespace std;

// Helper function to parse a card from a string
Card parseCard(const string& line) {
    istringstream iss(line);
    char suit;
    string value;
    iss >> suit >> value;
    // Handling for '10' which is represented by two characters
    if (value == "1") {
        char nextChar;
        iss >> nextChar;
        value += nextChar;
    }
    return Card(string(1, suit), value);
}

bool playTurn(CardBST& playerBST, CardBST& opponentBST, bool isAlice) {
    if (isAlice) {
        // Alice's turn: find and remove the smallest card from her BST that matches one in Bob's BST
        Card card = playerBST.findMin();
        if (!card.suit.empty() && opponentBST.find(card)) {
            cout << "Alice picked matching card " << card.suit << " " << card.value << endl;
            playerBST.remove(card);
            opponentBST.remove(card);
            return true;
        }
    } else {
        // Bob's turn: find and remove the largest card from his BST that matches one in Alice's BST
        Card card = playerBST.findMax();
        if (!card.suit.empty() && opponentBST.find(card)) {
            cout << "Bob picked matching card " << card.suit << " " << card.value << endl;
            playerBST.remove(card);
            opponentBST.remove(card);
            return true;
        }
    }
    return false;
}

int main(int argc, char** argv) {
    if (argc != 3) {
        cout << "Please provide 2 file names" << endl;
        return 1;
    }

    ifstream cardFile1(argv[1]);
    ifstream cardFile2(argv[2]);
    string line;

    if (cardFile1.fail()) {
        cout << "Could not open file " << argv[1] << endl;
        return 1;
    }
    if (cardFile2.fail()) {
        cout << "Could not open file " << argv[2] << endl;
        return 1;
    }

    CardBST aliceBST, bobBST;

    // Read cards for Alice
    while (getline(cardFile1, line) && !line.empty()) {
        aliceBST.insert(parseCard(line));
    }
    cardFile1.close();

    // Read cards for Bob
    while (getline(cardFile2, line) && !line.empty()) {
        bobBST.insert(parseCard(line));
    }
    cardFile2.close();

    // The game begins
    bool aliceTurn = true;
    bool cardFound;
    do {
        cardFound = playTurn(aliceBST, bobBST, aliceTurn);
        aliceTurn = !aliceTurn; // Switch turns
    } while (cardFound);

    // Game over, print remaining cards
    cout << "Alice's cards:" << endl;
    aliceBST.printInOrder();
    cout << "Bob's cards:" << endl;
    bobBST.printInOrder();

    return 0;
}
