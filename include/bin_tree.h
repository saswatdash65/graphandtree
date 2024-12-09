#pragma once
#ifndef _BINARY_TREE_
#define _BINARY_TREE_
#include <vector>
#include <iostream>
#include <queue>
#include <stdlib.h>
#include <cmath>
#include <string>

namespace {
    template <typename T> void printTree(tree::BinTreeNode<T>* node, std::string& padding, tree::ChildType type) {
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
    };

    template <typename T> void deleteFarthest(tree::BinTree<T>*& tree, tree::BinTreeNode<T>* de_node) {
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
                }
                else
                    q.push(temp->getRight());
            }

            if (temp->getLeft()) {
                if (temp->getLeft() == de_node) {
                    *temp << nullptr;
                    delete de_node;
                    return;
                }
                else
                    q.push(temp->getLeft());
            }
        }
    };
};

/**
 *  Namespace for binary tree classes
 *  Contains: class BinTreeNode, class BinTree
 */
namespace tree {
    
    enum ChildType {
        _LEFT, _RIGHT
    };

    template <class T> class BinTreeNode {
        const T value;
        BinTreeNode<T> *left;
        BinTreeNode<T> *right;

        unsigned int color: 24;

        public:
            // Unique identifier
            int id;
            int level;

            /** Constructor */
            BinTreeNode(T value):
                value(value), left(nullptr), right(nullptr), id(__COUNTER__), level(0) { }

            BinTreeNode(T value, BinTreeNode<T> *left, BinTreeNode<T> *right):
                value(value), left(left), right(right), id(__COUNTER__),
                level(std::max(left->level, right->level) + 1) { }

            virtual ~BinTreeNode() {
                delete this->left;
                delete this->right;
                delete this;
            }

            T getValue() {
                return this->value;
            }

            BinTreeNode<T>* getLeft() {
                if (this->left != nullptr) {
                    return this->left;
                }
                else return nullptr;
            }

            BinTreeNode<T>* getRight() {
                if (this->right != nullptr) {
                    return this->right;
                }
                else return nullptr;
            }

            BinTreeNode<T> **getChildren() {
                BinTreeNode<T>** children = new BinTreeNode<T>*[2];
                children[0] = this->left;
                children[1] = this->right;
                return children;
            }

            bool isLeaf() {
                return this->left == nullptr && this->right == nullptr;
            }

            BinTreeNode<T>& operator <<(BinTreeNode<T> &my_node) {
                this->left = &my_node;
                my_node.level = this->level + 1;
                return *this;
            }

            BinTreeNode<T>& operator >>(BinTreeNode<T> &my_node) {
                this->right = &my_node;
                my_node.level = this->level + 1;
                return *this;
            }
    };

    template <class T> class BinTree {
        BinTreeNode<T> *root;

    public:
        int height;
        int size;

        BinTree(BinTreeNode<T> *root) :
            root(root), height(root->level + 1), size(1) { }

        virtual ~BinTree() {
            delete this->root;
        }

        BinTreeNode<T>* insert(T value) {
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

        void print() {
            std::cout << "\n-----The given binary tree-----\n";
            std::cout << this->root->getValue() << "\n";
            printTree(this->root, "", _LEFT);
            printTree(this->root, "", _RIGHT);
        }

        int remove(T value) {
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

                BinTreeNode<T>* left = temp->getLeft(), * right = temp->getRight();
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

        BinTreeNode<T>* search(T value) {
            std::queue<BinTreeNode<T>*> q;
            q.push(this->root);

            while (!q.empty()) {
                BinTreeNode<T>* temp = q.front();
                q.pop();

                if (temp->getValue() == value)
                    return temp;

                BinTreeNode<T>* left = temp->getLeft(), * right = temp->getRight();
                if (left)
                    q.push(left);
                if (right)
                    q.push(right);
            }

            return nullptr;
        }
        

        template <typename _node_> friend std::vector<_node_> traversalInOrder(BinTree<T>* &root);
        template <typename _node_> friend std::vector<_node_> traversalPostOrder(BinTree<T>* &root);
        template <typename _node_> friend std::vector<_node_> traversalPreOrder(BinTree<T>* &root);
        template <typename _node_> friend std::vector<std::vector<_node_>> traversalLevelOrder(BinTree<T>* &root);
        template <typename _node_> friend std::vector<std::vector<_node_>> traversalVerticalOrder(BinTree<T>* &root);
    };
}

#endif