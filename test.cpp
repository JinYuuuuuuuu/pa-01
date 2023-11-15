#include "cards.h"
#include <cassert>

void testInsertAndFind() {
    CardBST bst;
    bst.insert(Card("h", "3"));
    assert(bst.find(Card("h", "3")) == true);
    assert(bst.find(Card("h", "4")) == false);
    cout << "testInsertAndFind passed." << endl;
}

void testRemove() {
    CardBST bst;
    bst.insert(Card("h", "3"));
    bst.remove(Card("h", "3"));
    assert(bst.find(Card("h", "3")) == false);
    cout << "testRemove passed." << endl;
}

// Add more tests for each function...

int main() {
    testInsertAndFind();
    testRemove();
    // Call more test functions...
    cout << "All tests passed." << endl;
    return 0;
}
