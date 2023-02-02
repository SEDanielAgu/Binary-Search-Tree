//
// Created by Daniel Agu on 11/18/2020.
//

#ifndef BSTBASE_BINARYSEARCHTREE_H
#define BSTBASE_BINARYSEARCHTREE_H
#include <iostream>
#include "TreeNode.h"
#include <vector>
#include <algorithm>

using namespace std;

template <typename T>
class BinarySearchTree {
public:
    BinarySearchTree(TreeNode<T>* newRoot) {
        rootNode = newRoot;
    }

    void addNode(TreeNode<T>* newNode){
        if (rootNode == nullptr) {  // sets the new node to the root if the tree is empty
            rootNode = newNode;
        }
        else {
            TreeNode<T>* newParent = findLeaf(newNode, rootNode); // finds the leaf that will become the new parent of the new node
            if (newNode->getValue() <= newParent->getValue()) { // makes the new node a left leaf
                newParent->setLeftChild(newNode); // creates a branch between the new node and new parent
                newNode->setParentNode(newParent);
            }
            else { // makes the new node a right leaf
                newParent->setRightChild(newNode); // creates a branch between the new node and new parent
                newNode->setParentNode(newParent);
            }
        }
    }

    void traverse(vector<T>& tree) const {
        recursiveTraverse(tree, rootNode); // calls the recursive helper method to traverse the tree
    }

    void clearContents() {
        rescursiveClear(rootNode); // calls the recursive helper method to clear the tree
        rootNode = nullptr; // makes the tree fully empty by removing the root
    }

    TreeNode<T>* find(T value) {
        return recursiveFind(value, rootNode); // calls the recursive helper method to find the node with the corresponding value
    }

    TreeNode<T>* remove(T value) {
        TreeNode<T>* removedNode = find(value); // finds and captures the node we want removed
        if (removedNode->isLeaf()) { // if the removed node is a a leaf it gets removed based on whether its a right or left child
            if (removedNode->getValue() <= removedNode->getParentNode()->getValue()) { // determines if it is a left child
                removedNode->getParentNode()->setLeftChild(nullptr); // creates a link between the previous parent and the corresponding child
                removedNode->setParentNode(nullptr); // breaks the branch between the old parent and child
            }
            else {
                removedNode->getParentNode()->setRightChild(nullptr); // if it is not a left child it must be a right child
                removedNode->setParentNode(nullptr);
            }
        }
        else if (removedNode->getRightChild() != nullptr && removedNode->getLeftChild() == nullptr) { // determines if the node with one child is a right child
            if (removedNode->getParentNode() != nullptr) { // makes sure the removed node is not a one child root
                if (removedNode->getRightChild()->getValue() <= removedNode->getParentNode()->getValue()) { // determines whether the new child is a left child
                    removedNode->getParentNode()->setRightChild(removedNode->getRightChild()); //  a new branch between the previous parent and the new child
                    removedNode->getRightChild()->setParentNode(removedNode->getParentNode());
                }
                else { // if the new child is not a left child it must be a right child
                    removedNode->getParentNode()->setLeftChild(removedNode->getRightChild());
                    removedNode->getRightChild()->setParentNode(removedNode->getParentNode());
                }
                removedNode->setParentNode(nullptr); // breaks old branch between old parent and removed node
                removedNode->setRightChild(nullptr); // breaks old branch between old child and removed node
            }
            else { // the removed node is a one root function
                rootNode = removedNode->getRightChild(); // sets the new root to the previous child of the removed node
                removedNode->getRightChild()->setParentNode(nullptr);

                removedNode->setParentNode(nullptr); // creates new branch between the new root and child
                removedNode->setRightChild(nullptr);
            }
        }
        else if (removedNode->getLeftChild() != nullptr && removedNode->getRightChild() == nullptr) { // determines if the node with one child is a left child
            if (removedNode->getParentNode() != nullptr) { // makes sure the removed node is not a one child root
                if (removedNode->getLeftChild()->getValue() <= removedNode->getParentNode()->getValue()) { // determines whether the new child is a left child
                    removedNode->getParentNode()->setLeftChild(removedNode->getLeftChild()); // creates a new branch between the previous parent and the new child
                    removedNode->getLeftChild()->setParentNode(removedNode->getParentNode());
                }
                else { // if the new child is not a left child it must be a right child
                    removedNode->getParentNode()->setRightChild(removedNode->getLeftChild());
                    removedNode->getLeftChild()->setParentNode(removedNode->getParentNode());
                }
                removedNode->setParentNode(nullptr); // breaks old branch between old parent and removed node
                removedNode->setLeftChild(nullptr); // breaks old branch between old child and removed node
            }
            else { // the removed node is a one root function
                rootNode = removedNode->getLeftChild(); // sets the new root to the previous child of the removed node
                removedNode->getLeftChild()->setParentNode(nullptr);

                removedNode->setParentNode(nullptr); // creates new branch between the new root and child
                removedNode->setLeftChild(nullptr);
            }
        }
        else if (removedNode == rootNode) { // the removed node is a 2 branch node
            removedNode->getLeftChild()->setParentNode(removedNode->getRightChild());  // creates a branch between the previous left child and the new root
            removedNode->getRightChild()->setLeftChild(removedNode->getLeftChild());
            removedNode->getRightChild()->setParentNode(nullptr); // removes the right child's previous parent

            rootNode = removedNode->getRightChild(); // sets the previous right child to the new root

            removedNode->setRightChild(nullptr); // removes the branches of the removed node
            removedNode->setLeftChild(nullptr);
        }
        else if (removedNode->getLeftChild() != nullptr && removedNode->getRightChild() != nullptr) { // checks to see if the node has two children
            TreeNode<T>* nextSmallestNode = traverseLeft(removedNode->getRightChild()); // captures the next smallest node that's bigger than the removed node
            if (removedNode->getRightChild()->isLeaf() == false) { // checks to see if the child of the removed node is a leaf
                nextSmallestNode->getParentNode()->setLeftChild(nullptr); // replaces the the parent position of the removed node with next smallest position
                removedNode->getLeftChild()->setParentNode(nextSmallestNode); // creates two branches connecting the next smallest node to it's new children
                removedNode->getRightChild()->setParentNode(nextSmallestNode);

                nextSmallestNode->setLeftChild(removedNode->getLeftChild());
                nextSmallestNode->setRightChild(removedNode->getRightChild());
            }
            else { // the child of the removed is not a leaf
                removedNode->getLeftChild()->setParentNode(nextSmallestNode); // replaces the the parent position of the removed node with next smallest position
                removedNode->getRightChild()->setParentNode(removedNode->getParentNode());

                nextSmallestNode->setLeftChild(removedNode->getLeftChild()); // creates a branch with the next smallest and the new child
                nextSmallestNode->setRightChild(nullptr);
            }
            removedNode->getParentNode()->setLeftChild(nextSmallestNode); // always sets the next smallest to the left child
            removedNode->setParentNode(nullptr); // removes branch between removed node and previous parent
        }
        return removedNode;
    }

    TreeNode<T>* getRoot() {
        return rootNode;
    }

    void rebalance() {
        vector<T> nodeList;
        traverse(nodeList); // puts all nodes into a list
        clearContents(); // clears the current binary search tree
        int mid = nodeList.size()/2;
        TreeNode<T>* currNode = new TreeNode<T>(nodeList.at(mid)); // adds the first node
        addNode(currNode);
        (recursiveRebalance(nodeList, 0, mid-1)); // recursively adds the left and right nodes in the correct order
        (recursiveRebalance(nodeList, mid+1, (nodeList.size())-1));
    }

private:
    TreeNode<T>* rootNode;

    void recursiveRebalance(vector<T> nodeList, int start, int end) {
        if (start <= end) { // base case to makes sure the lists dont cross over
            int mid = (start+end)/2;
            TreeNode<T>* currNode = new TreeNode<T>(nodeList.at(mid));
            addNode(currNode);
            (recursiveRebalance(nodeList, start, mid-1)); // adds left and right children in the correct order
            (recursiveRebalance(nodeList, mid+1, end));
        }
    }

    void recursiveTraverse(vector<T>& nodeList, TreeNode<T>* treeNode) const{
        if (treeNode->getLeftChild() != nullptr) { // makes sure the left leaf is node
            recursiveTraverse(nodeList, treeNode->getLeftChild()); // travels down and adds the left side of the tree first
        }
        nodeList.push_back(treeNode->getValue()); // adds the values in the correct order
        if (treeNode->getRightChild() != nullptr) {
            recursiveTraverse(nodeList, treeNode->getRightChild()); // travels down and adds the right side of the tree last
        }
    }

    TreeNode<T>* traverseLeft(TreeNode<T>* givenNode) {
        TreeNode<T>* smallestNode = givenNode; // captures the smallest node
        if (smallestNode->isLeaf() == false && smallestNode->getLeftChild() != nullptr) { // goes down the left side of the list always capturing the smaller value till it is the smallest in the tree
            traverseLeft(smallestNode->getLeftChild());
        }
        else {
            return smallestNode;
        }
    }

    TreeNode<T>* recursiveFind(T value, TreeNode<T>* currentNode) {
        if (currentNode->getValue() == value) { // returns the correct node if the corresponding value is found
            return currentNode;
        }
        else if (value < currentNode->getValue()) { // goes searching down the left side of the tree if the value is less than the root's value
            if (currentNode->getLeftChild() != nullptr) {
                recursiveFind(value, currentNode->getLeftChild());
            }
        }
        else if (value > currentNode->getValue()) { //goes searching down the right side of the tree if the value is greater than the root's value
            if (currentNode->getRightChild() != nullptr) {
                recursiveFind(value, currentNode->getRightChild());
            }
        }
        else {
            return nullptr; // returns a nullptr if the value is not found
        }
    }

    void rescursiveClear(TreeNode<T>* currentNode) {
        if (currentNode->getLeftChild() != nullptr) { // travels down the left side of the tree first
            rescursiveClear(currentNode->getLeftChild());
        }
        if (currentNode->getRightChild() != nullptr) { // breaks branches with right children if they are not null
            currentNode->getRightChild()->setParentNode(nullptr);
            currentNode->setRightChild(nullptr);
        }
        if (currentNode->getLeftChild() != nullptr) { // breaks branches with left children if they are not null
            currentNode->getLeftChild()->setParentNode(nullptr);
            currentNode->setLeftChild(nullptr);
        }
        if (currentNode->getRightChild() != nullptr) { // travels down the right side of the tree last
            rescursiveClear(currentNode->getRightChild());
        }
    }

    TreeNode<T>* findLeaf(TreeNode<T>* node, TreeNode<T>* treeNode) {
        if (node->getValue() <= treeNode->getValue()) {  // searches for the leaf on the left side of the tree
            if (treeNode->getLeftChild() != nullptr) {
                findLeaf(node, treeNode->getLeftChild());
            }
            else {
                return treeNode; // returns the correct node
            }
        }
        else { // searches for the leaf on the right side of the tree
            if (treeNode->getRightChild() != nullptr) {
                findLeaf(node, treeNode->getRightChild());
            }
            else {
                return treeNode; // returns the correct node
            }
        }
    }
};

#endif //BSTBASE_BINARYSEARCHTREE_H
