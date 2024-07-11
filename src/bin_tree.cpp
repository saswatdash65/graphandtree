#include "bin_tree.h"
#include <iostream>
#include <queue>
#include <stdlib.h>
#include <cmath>
#include <string>

namespace tree {

    template <class T>
    BinTreeNode<T>& BinTreeNode<T>::operator<<(const BinTreeNode<T> &my_node) {
        this->left = my_node;
        my_node.level = this->level + 1;
        return *this;
    }

    template <class T>
    BinTreeNode<T>& BinTreeNode<T>::operator>>(const BinTreeNode<T> &my_node) {
        this->right = my_node;
        my_node.level = this->level + 1;
        return *this;
    }
}

template <typename T> void printTree(tree::BinTreeNode<T>* node, std::string &padding, tree::ChildType type) {
    if (node == nullptr) {
        std::cout << padding << "└──\n";
        padding = padding.substr(0, padding.length() - 3);
        return;
    }

    if (type == tree::_LEFT) 
        std::cout << padding << "├──" << node->getValue() << "\n";
    else 
        std::cout << padding << "└──" << node->getValue() << "\n";

    if (!node->isLeaf() && type == tree::_LEFT) 
        padding.append("|  ");
    else if (!node->isLeaf() && type == tree::_RIGHT)
        padding.append("   ");
    else return;

    printTree(node->getLeft(), padding, tree::_LEFT);
    if (node->getRight != nullptr)
        printTree(node->getRight(), padding, tree::_RIGHT);
    else 
        padding = padding.substr(0, padding.length() - 3);
}

template <typename T> void deleteFarthest(tree::BinTree<T>* &tree, tree::BinTreeNode<T>* de_node) {
    std::queue<tree::BinTreeNode<T>*> q;
    q.push(tree->root);

    while (!q.empty()) {
        tree::BinTreeNode<T>* temp = q.front();
        q.pop();

        if (temp == de_node) {
            delete de_node;
            return;
        }

        if (temp->getRight()) {
            if (temp->getRight() == de_node) {
                *temp >> nullptr;
                delete de_node;
                return;
            } else 
                q.push(temp->getRight());
        }

        if (temp->getLeft()) {
            if (temp->getLeft() == de_node) {
                *temp << nullptr;
                delete de_node;
                return;
            } else 
                q.push(temp->getLeft());
        }
    }
}

namespace tree {

    template <class T> BinTreeNode<T>::BinTreeNode(T value): 
    value(value), left(nullptr), right(nullptr), id(__COUNTER__), level(0) {}

    template <class T> BinTreeNode<T>::BinTreeNode(T value, BinTreeNode<T> *left, BinTreeNode<T> *right):
    value(value), left(left), right(right), id(__COUNTER__), 
    level(std::max(left->level, right->level) + 1) {}

    template <class T> BinTreeNode<T>::~BinTreeNode() {
        delete this->left;
        delete this->right;
    }

    template <class T> T BinTreeNode<T>::getValue() {
        return this->value;
    }

    template <class T> BinTreeNode<T>** BinTreeNode<T>::getChildren() {
        BinTreeNode<T>** children = new BinTreeNode<T>*[2];
        children[0] = this->left;
        children[1] = this->right;
        return children;
    }

    template <class T> BinTreeNode<T>* BinTreeNode<T>::getLeft() {
        if (this->left != nullptr) {
            return this->left;
        } else return nullptr;
    }

    template <class T> BinTreeNode<T>* BinTreeNode<T>::getRight() {
        if (this->right!= nullptr) {
            return this->right;
        } else return nullptr;
    }

    template <class T> bool BinTreeNode<T>::isLeaf() {
        return this->left == nullptr && this->right == nullptr;
    }
    
    template <class T> BinTree<T>::BinTree(BinTreeNode<T>* root):
    root(root), height(root->level + 1), size(1) {}

    template <class T> BinTree<T>::~BinTree() {
        delete this->root;
    }

    template <class T> BinTreeNode<T>* BinTree<T>::insert(T value) {
        std::queue<BinTreeNode<T>*> q;
        q.push(this->root);
        BinTreeNode<T>* parent, child;

        while (!q.empty()) {
            BinTreeNode<T>* temp = q.front();
            q.pop();

            if (temp->getLeft() == nullptr) {
                child = new BinTreeNode<T>(value);
                parent = temp;
                *parent << *child;
                q = {};
            }

            if (temp->getRight() == nullptr) {
                child = new BinTreeNode<T>(value);
                parent = temp;
                *parent >> *child;
                q = {};
            }

            q.push(temp->getLeft());
            q.push(temp->getRight());
        }

        return child;
    }

    template <class T> void BinTree<T>::print() {
        std::cout << "\n-----The given binary tree-----\n";
        std::cout << this->root->getValue() << "\n";
        printTree(this->root, "", _LEFT);
        printTree(this->root, "", _RIGHT);
    }

    template <class T> int BinTree<T>::remove(T value) {
        if (this->root->getLeft() == nullptr && this->root->getRight() == nullptr) {
            if (this->root->getValue() == value) {
                int id = this->root->id;
                delete this->root;
                this->root = nullptr;
                return id;
            }
            else return -1;
        }
        
        std::queue<BinTreeNode<T>*> q;
        q.push(this->root);
        BinTreeNode<T>* temp;
        BinTreeNode<T>* de_node = nullptr;

        while (!q.empty()) {
            temp = q.front();
            q.pop();

            if (temp->getValue() == value) 
                de_node = temp;

            BinTreeNode<T>* left = temp->getLeft(), *right = temp->getRight();
            if (left)
                q.push(left);

            if (right)
                q.push(right);
        }

        if (de_node != nullptr) {
            T x = temp->getValue();
            de_node->value = x;
            int id = temp->id;
            deleteFarthest(this, temp);
            return id;
        }

        return -1;
    }

    template <class T> BinTreeNode<T>* BinTree<T>::search(T value) {
        std::queue<BinTreeNode<T>*> q;
        q.push(this->root);

        while (!q.empty()) {
            BinTreeNode<T>* temp = q.front();
            q.pop();

            if (temp->getValue() == value) 
                return temp;
            
            BinTreeNode<T>* left = temp->getLeft(), *right = temp->getRight();
            if (left) 
                q.push(left);
            if (right) 
                q.push(right);
        }

        return nullptr;
    }
}