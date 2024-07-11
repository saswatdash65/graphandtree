#ifndef _TREE_TRAVERSAL_
#define _TREE_TRAVERSAL

#include "bin_tree.h"
#include <vector>
using namespace std;

namespace tree {
    
    template <typename _node_> 
    vector<_node_> traversalInOrder(BinTree<_node_>* &tree);

    template <typename _node_> 
    vector<_node_> traversalPreOrder(BinTree<_node_>* &tree);

    template <typename _node_> 
    vector<_node_> traversalPostOrder(BinTree<_node_>* &tree);

    template <typename _node_> 
    vector<vector<_node_>> traversalLevelOrder(BinTree<_node_>* &tree);

    template <typename _node_> 
    vector<vector<_node_>> traversalVerticalOrder(BinTree<_node_>* &tree);
}
    

#endif