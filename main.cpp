#include <iostream>

#include "BinarySearchTree.h"
#include <cassert>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

void checkTreeContents(const BinarySearchTree<int>& tree, const string& expectedContents) {
    vector<int> traversalVector;
    ostringstream contents;
    tree.traverse(traversalVector);
    for ( int value : traversalVector) {
        contents << value << " ";
    }
    assert(contents.str() == expectedContents);
}

void testInsertions() {
    cout << "Testing insertions " << endl;
    TreeNode<int>* root = new TreeNode<int>(50);
    BinarySearchTree<int> tree(root);
    checkTreeContents(tree, "50 ");

    TreeNode<int>* leftChild = new TreeNode<int>(30);
    tree.addNode(leftChild);
    checkTreeContents(tree, "30 50 ");

    TreeNode<int>* rightChild = new TreeNode<int>(70);
    tree.addNode(rightChild);
    checkTreeContents(tree, "30 50 70 ");

    TreeNode<int>* leftRightChild = new TreeNode<int>(40);
    tree.addNode(leftRightChild);
    checkTreeContents(tree, "30 40 50 70 ");

    TreeNode<int>* leftLeftChild = new TreeNode<int>(20);
    tree.addNode(leftLeftChild);
    checkTreeContents(tree, "20 30 40 50 70 ");

    // Checks to see that the pointers are right
    // (pointer address checks are good here)
    assert(root->getLeftChild() == leftChild);
    assert(root->getRightChild() == rightChild);
    assert(root->getParentNode() == nullptr);

    assert(leftChild->getLeftChild() == leftLeftChild);
    assert(leftChild->getRightChild() == leftRightChild);
    assert(leftChild->getParentNode() == root);

    assert(rightChild->getLeftChild() == nullptr);
    assert(rightChild->getRightChild() == nullptr);
    assert(rightChild->getParentNode() == root);

    assert(leftLeftChild->getLeftChild() == nullptr);
    assert(leftLeftChild->getRightChild() == nullptr);
    assert(leftLeftChild->getParentNode() == leftChild);

    assert(leftRightChild->getLeftChild() == nullptr);
    assert(leftRightChild->getRightChild() == nullptr);
    assert(leftRightChild->getParentNode() == leftChild);

    tree.clearContents();
    assert(root->getLeftChild() == nullptr);
    assert(root->getRightChild() == nullptr);
    assert(leftLeftChild->getParentNode() == nullptr);
    assert(rightChild->getParentNode() == nullptr);

    // Y'all asked me to delete stuff ;)
    delete root;
    delete leftChild;
    delete rightChild;
    delete leftLeftChild;
    delete leftRightChild;

    cout << "Insertion: success!" << endl;
}

void testSearches() {
    cout << "Testing searches " << endl;
    TreeNode<int>* root = new TreeNode<int>(50);
    BinarySearchTree<int> tree(root);
    checkTreeContents(tree, "50 ");

    TreeNode<int>* leftChild = new TreeNode<int>(30);
    tree.addNode(leftChild);
    checkTreeContents(tree, "30 50 ");

    TreeNode<int>* rightChild = new TreeNode<int>(70);
    tree.addNode(rightChild);
    checkTreeContents(tree, "30 50 70 ");

    TreeNode<int>* leftRightChild = new TreeNode<int>(40);
    tree.addNode(leftRightChild);
    checkTreeContents(tree, "30 40 50 70 ");

    TreeNode<int>* leftLeftChild = new TreeNode<int>(20);
    tree.addNode(leftLeftChild);
    checkTreeContents(tree, "20 30 40 50 70 ");

    assert(tree.find(50) == root);
    assert(tree.find(40) == leftRightChild);
    assert(tree.find(70) == rightChild);
    assert(tree.find(100) == nullptr);

    tree.clearContents();

    // Y'all asked me to delete stuff ;)
    delete root;
    delete leftChild;
    delete rightChild;
    delete leftLeftChild;
    delete leftRightChild;

    cout << "Searching: success!" << endl;
}

void testRemovals() {
    cout << "Testing removals " << endl;
    TreeNode<int>* root = new TreeNode<int>(50);
    BinarySearchTree<int> tree(root);
    checkTreeContents(tree, "50 ");

    TreeNode<int>* willBeRoot = new TreeNode<int>(51);
    tree.addNode(willBeRoot);
    checkTreeContents(tree, "50 51 ");

    TreeNode<int>* leftChild = new TreeNode<int>(30);
    tree.addNode(leftChild);
    checkTreeContents(tree, "30 50 51 ");

    TreeNode<int>* rightChild = new TreeNode<int>(70);
    tree.addNode(rightChild);
    checkTreeContents(tree, "30 50 51 70 ");

    TreeNode<int>* leftRightChild = new TreeNode<int>(40);
    tree.addNode(leftRightChild);
    checkTreeContents(tree, "30 40 50 51 70 ");

    TreeNode<int>* leftLeftChild = new TreeNode<int>(20);
    tree.addNode(leftLeftChild);
    checkTreeContents(tree, "20 30 40 50 51 70 ");

    TreeNode<int>* rightLeftChild = new TreeNode<int>(60);
    tree.addNode(rightLeftChild);
    checkTreeContents(tree, "20 30 40 50 51 60 70 ");

    TreeNode<int>* rightRightChild = new TreeNode<int>(80);
    tree.addNode(rightRightChild);
    checkTreeContents(tree, "20 30 40 50 51 60 70 80 ");

    // Easy removal: a leaf
    TreeNode<int>* removedRightRight = tree.remove(80);
    assert(removedRightRight == rightRightChild);
    assert(removedRightRight->getParentNode() == nullptr);
    assert(rightChild->getRightChild() == nullptr);
    checkTreeContents(tree, "20 30 40 50 51 60 70 ");

    // Still easy: a node with one child
    TreeNode<int>* removedRight = tree.remove(70);
    assert(removedRight == rightChild);
    assert(removedRight->getParentNode() == nullptr);
    assert(willBeRoot->getRightChild() == rightLeftChild);
    assert(rightLeftChild->getParentNode() == willBeRoot);
    checkTreeContents(tree, "20 30 40 50 51 60 ");

    // Hard: a node with two children (root)
    TreeNode<int>* removedRoot = tree.remove(50);
    assert(root == removedRoot);
    assert(tree.getRoot() == willBeRoot);
    assert(willBeRoot->getRightChild() == rightLeftChild);
    assert(rightLeftChild->getParentNode() == willBeRoot);
    checkTreeContents(tree, "20 30 40 51 60 ");

    // Hard: a node with two children
    TreeNode<int>* removedLeft = tree.remove(30);
    assert(leftChild == removedLeft);
    assert(willBeRoot->getLeftChild() == leftRightChild);
    assert(leftRightChild->getParentNode() == willBeRoot);
    checkTreeContents(tree, "20 40 51 60 ");

    tree.clearContents();
    delete root;
    delete willBeRoot;
    delete leftChild;
    delete leftLeftChild;
    delete leftRightChild;
    delete rightChild;
    delete rightLeftChild;
    delete rightRightChild;

    cout << "Removals: success!" << endl;
}

void testRebalance() {
    cout << "Testing rebalance " << endl;
    TreeNode<int>* root = new TreeNode<int>(50);
    BinarySearchTree<int> tree(root);
    checkTreeContents(tree, "50 ");

    tree.rebalance();
    checkTreeContents(tree, "50 ");

    // Set up an imbalanced tree
    TreeNode<int>* oneLess = new TreeNode<int>(49);
    tree.addNode(oneLess);

    TreeNode<int>* twoLess = new TreeNode<int>(48);
    tree.addNode(twoLess);

    TreeNode<int>* threeLess = new TreeNode<int>(47);
    tree.addNode(threeLess);

    TreeNode<int>* fourLess = new TreeNode<int>(46);
    tree.addNode(fourLess);

    TreeNode<int>* fiveLess = new TreeNode<int>(45);
    tree.addNode(fiveLess);

    checkTreeContents(tree, "45 46 47 48 49 50 ");
    assert(root->getRightChild() == nullptr);
    assert(oneLess->getRightChild() == nullptr);


    tree.rebalance();
    assert(tree.getRoot()->getValue() == twoLess->getValue());
    assert(tree.getRoot()->getLeftChild()->getValue() == fourLess->getValue());
    assert(tree.getRoot()->getLeftChild()->getLeftChild()->getValue() == fiveLess->getValue());
    assert(tree.getRoot()->getLeftChild()->getRightChild()->getValue() == threeLess->getValue());
    assert(tree.getRoot()->getRightChild()->getValue() == oneLess->getValue());
    assert(tree.getRoot()->getRightChild()->getRightChild()->getValue() == root->getValue());

    tree.clearContents();
    delete root;
    delete oneLess;
    delete twoLess;
    delete threeLess;
    delete fourLess;
    delete fiveLess;

    cout << "Rebalance: success!" << endl;
}

int main(int argc, char** argv) {
    int testToRun = 99;
    if ( argc > 1) {
        testToRun = atoi(argv[1]);
    }
    switch(testToRun) {
        case 1:
            testInsertions();
            break;
        case 2:
            testSearches();
            break;
        case 3:
            testRemovals();
            break;
        case 4:
            testRebalance();
            break;
        default:
            // Run it all
            testInsertions();
            testSearches();
            testRemovals();
            testRebalance();
            break;
    }
}
