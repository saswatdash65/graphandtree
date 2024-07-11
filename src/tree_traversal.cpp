#include "tree_traversal.h"
#include <queue>
#include <map>
#include <set>
#include <utility>

template <typename _node_>
void traversePreOrder(tree::BinTreeNode<_node_>* &tree_node, vector<_node_> &result) {
    if (tree_node) {
        result.push_back(tree_node->getValue());
        traversePreOrder(tree_node->getLeft(), result);
        traversePreOrder(tree_node->getRight(), result);
    }
}

template <typename _node_>
void traversePostOrder(tree::BinTreeNode<_node_>* &tree_node, vector<_node_> &result) {
    if (tree_node) {
        traversePostOrder(tree_node->getLeft(), result);
        traversePostOrder(tree_node->getRight(), result);
        result.push_back(tree_node->getValue());
    }
}

template <typename _node_>
void traversalInOrder(tree::BinTreeNode<_node_>* &tree_node, vector<_node_> &result) {
    if (tree_node) {
        traverseInOrder(tree_node->getLeft(), result);
        result.push_back(tree_node->getValue());
        traverseInOrder(tree_node->getRight(), result);
    }
}

namespace tree {
    template <typename _node_>
    vector<_node_> traversalPreOrder(BinTree<_node_>* &tree) {
        vector<_node_> result;
        if (tree) {
            result.push_back(tree->root->value);
            traversePreOrder(tree->root->left, result);
            traversePreOrder(tree->root->right, result);
        }
        return result;
    }

    template <typename _node_>
    vector<_node_> traversalPostOrder(BinTree<_node_>* &tree) {
        vector<_node_> result;
        if (tree) {
            traversePostOrder(tree->root->left, result);
            traversePostOrder(tree->root->right, result);
            result.push_back(tree->root->value);
        }
        return result;
    }

    template <typename _node_>
    vector<_node_> traversalInOrder(BinTree<_node_>* &tree) {
        vector<_node_> result;
        if (tree) {
            traverseInOrder(tree->root->left, result);
            result.push_back(tree->root->value);
            traverseInOrder(tree->root->right, result);
        }
        return result;
    }

    template <typename _node_>
    vector<_node_> traversalLevelOrder(BinTree<_node_>* &tree) {
        if (!tree) return new vector<_node_>();
        
        queue<BinTreeNode<_node_>*> q;
        vector<vector<_node_>> result;
        q.push(tree->root);
        
        while (!q.empty()) {
            int levelSize = q.size();
            vector<_node_> levelResult;
            for (int i = 0; i < levelSize; i++) {
                BinTreeNode<_node_>* node = q.front();
                q.pop();
                levelResult.push_back(node->value);
                if (node->left) q.push(node->left);
                if (node->right) q.push(node->right);
            }
            result.push_back(levelResult);
        }
        return result;
    }

    template <typename _node_>
    vector<vector<_node_>> traversalVerticalOrder(BinTree<_node_>* &tree) {
        map<int, map<int, multiset<_node_>>> ver_data;
        queue<pair<BinTreeNode<_node_>*, int>> node;

        node.push({tree->root, tree->root->getValue()});

        while (!node.empty()) {
            auto [my_node, ver_level] = node.front();
            node.pop();
            BinTreeNode<_node_>* temp = my_node;

            int x = ver_level;
            int y = my_node->level;

            ver_data[x][y] = temp->getValue();
            
            BinTreeNode<_node_>* left = temp->getLeft(), right = temp->getRight();
            if (left) 
                node.push({left, x-1});
            if (right)
                node.push({right, x+1});
        }

        vector<vector<_node_>> result;
        for (auto p: ver_data) {
            vector<_node_> col;
            for (auto val: p.second) {
                col.reserve(col.size() + val.second.size());
                col.insert(col.end(), val.second.begin(), val.second.end());
            }
            
            result.push_back(col);
        }
    }
}