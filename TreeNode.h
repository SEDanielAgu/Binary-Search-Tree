//
// Created by Daniel Agu on 11/18/2020.
//

#ifndef BSTBASE_TREENODE_H
#define BSTBASE_TREENODE_H
#include <iostream>
using namespace std;

template <typename T>
class TreeNode {
public:
    TreeNode(T newValue){
        value = newValue;
        leftChild = nullptr;
        rightChild = nullptr;
        parentNode = nullptr;
    }

    void setLeftChild(TreeNode<T>* newLeft) {
        leftChild = newLeft;
    }

    void setRightChild(TreeNode<T>* newRight) {
        rightChild = newRight;
    }

    void setParentNode(TreeNode<T>* newParent) {
        parentNode = newParent;
    }

    T getValue() {
        return value;
    }

    TreeNode<T>* getLeftChild() {
        return leftChild;
    }

    TreeNode<T>* getRightChild() {
        return rightChild;
    }

    TreeNode<T>* getParentNode() {
        return parentNode;
    }

    bool isLeaf() {
        if (leftChild == nullptr && rightChild == nullptr) {
            return true;
        }
        else {
            return false;
        }
    }

private:
    T value;
    TreeNode<T>* leftChild;
    TreeNode<T>* rightChild;
    TreeNode<T>* parentNode;
};

#endif //BSTBASE_TREENODE_H
