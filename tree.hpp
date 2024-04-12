#ifndef TREE_H
#define TREE_H

enum TreeType {
    RadixTree,
    CompressedRadixTree
};

class Tree {
public:
    Tree() {}
    virtual ~Tree() {}
    // basic operation
    virtual void insert(int key) = 0;
    virtual void remove(int key) = 0;
    virtual bool find(int key) = 0;
    // statistics
    virtual unsigned int size() = 0;    // number of nodes
    virtual unsigned int height() = 0;  // height of the tree
};
#endif