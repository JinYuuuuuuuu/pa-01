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
    if (value == "1") { // Assuming '1' represents '10'
        char nextChar;
        iss >> nextChar; // To get the '0' character
        value += nextChar;
    }
    return Card(string(1, suit), value);
}

void playTurn(CardBST& playerBST, CardBST& opponentBST, Card& currAlice, Card& currBob, bool isAlice) {

    while (!currAlice.isEmpty() && !currBob.isEmpty()){
        Card tempAlice = Card();
        Card tempBob = Card();
        if (isAlice){
            if (opponentBST.find(currAlice)){
              cout << "Alice picked matching card " << currAlice.suit << " " << currAlice.value << endl;
              tempAlice = currAlice;
              currAlice = playerBST.findSuccessor(currAlice);
              playerBST.remove(tempAlice);
              opponentBST.remove(tempAlice);
              isAlice = false;
            }
            else{
              currAlice = playerBST.findSuccessor(currAlice);
            }
        }

        else{
            if (playerBST.find(currBob)){
                cout << "Bob picked matching card " << currBob.suit << " " << currBob.value << endl;
                tempBob = currBob;
                currBob = opponentBST.findPredecessor(currBob);
                playerBST.remove(tempBob);
                opponentBST.remove(tempBob);
                isAlice = true;
            }
            else{
              currBob = opponentBST.findPredecessor(currBob);
            }
        }
    }
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

    CardBST aliceBST;
    CardBST bobBST;

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
    Card currAlice = aliceBST.findMin();
    Card currBob = bobBST.findMax();

    bool aliceTurn = true;
    playTurn(aliceBST, bobBST, currAlice, currBob, aliceTurn);
    cout << endl;

    // Game over, print remaining cards


    
    cout << "Alice's cards:" << endl;
    aliceBST.printInOrder();
    cout << endl;
    cout << "Bob's cards:" << endl;
    bobBST.printInOrder();
    

    return 0;
}
