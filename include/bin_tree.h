#ifndef _BINARY_TREE_
#define _BINARY_TREE_
#include <vector>

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

        #ifdef COLOR
        int color;
        #endif

        public:
            // Unique identifier
            int id;
            int level;

            /** Constructor */
            BinTreeNode(T value);
            BinTreeNode(T value, BinTreeNode<T> *left, BinTreeNode<T> *right);

            virtual ~BinTreeNode();

            T getValue();
            BinTreeNode<T>* getLeft();
            BinTreeNode<T>* getRight();
            BinTreeNode<T> **getChildren();
            bool isLeaf();

            BinTreeNode<T>& operator <<(const BinTreeNode<T>&);
            BinTreeNode<T>& operator >>(const BinTreeNode<T>&);
    };

    template <class T> class BinTree {
        BinTreeNode<T> *root;

    public:
        int height;
        int size;

        BinTree(BinTreeNode<T> *root);
        virtual ~BinTree();

        BinTreeNode<T>* insert(T value);
        void print();
        int remove(T value);
        BinTreeNode<T>* search(T value);
        

        template <typename _node_> friend std::vector<_node_> traversalInOrder(BinTree<T>* &root);
        template <typename _node_> friend std::vector<_node_> traversalPostOrder(BinTree<T>* &root);
        template <typename _node_> friend std::vector<_node_> traversalPreOrder(BinTree<T>* &root);
        template <typename _node_> friend std::vector<std::vector<_node_>> traversalLevelOrder(BinTree<T>* &root);
        template <typename _node_> friend std::vector<std::vector<_node_>> traversalVerticalOrder(BinTree<T>* &root);
    };
}

#endif