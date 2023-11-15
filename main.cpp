//main.cpp
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
    return Card(string(1, suit), value);
}

int main(int argc, char** argv) {
    if (argc < 3) {
        cout << "Please provide 2 file names" << endl;
        return 1;
    }

    ifstream cardFile1(argv[1]);
    ifstream cardFile2(argv[2]);
    string line;

    if (cardFile1.fail() || cardFile2.fail()) {
        cout << "Could not open file " << argv[2];
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
    bool aliceTurn = true; // Alice starts the game
    bool cardFound;
    
    do {
        cardFound = false; // Reset flag for each iteration

        if (aliceTurn) {
            // Alice's turn: iterate from smallest to largest card
            for (const auto& card : aliceBST) {
                if (bobBST.find(card)) {
                    cout << "Alice picked matching card " << card << endl;
                    aliceBST.remove(card);
                    bobBST.remove(card);
                    cardFound = true;
                    break; // Only one card per turn
                }
            }
        } else {
            // Bob's turn: iterate from largest to smallest card
            for (auto it = bobBST.rbegin(); it != bobBST.rend(); ++it) {
                if (aliceBST.find(*it)) {
                    cout << "Bob picked matching card " << *it << endl;
                    aliceBST.remove(*it);
                    bobBST.remove(*it);
                    cardFound = true;
                    break; // Only one card per turn
                }
            }
        }

        aliceTurn = !aliceTurn; // Switch turns
    } while (cardFound); // Continue while matches are found

    // Game over, print remaining cards
    cout << "Alice's cards:" << endl;
    aliceBST.printInOrder();
    cout << "Bob's cards:" << endl;
    bobBST.printInOrder();

    return 0;
}
