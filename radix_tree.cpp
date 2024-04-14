#include "radix_tree.hpp"
#include <iostream>

RadixTree::RadixTree()
{
    root = new Node();
}

void RadixTree::insert(int32_t value)
{
    Node* tmp = root;
    for (int i = 30; i >= 0; i-= 2)
    {
        int bit = (value >> i) & 0x3;
        if (tmp->children[bit] == nullptr)
        {
            tmp->children[bit] = new Node(tmp);
        }
        tmp = tmp->children[bit];
    }
}

void RadixTree::remove(int32_t value)
{
    Node* tmp = root;
    for (int i = 30; i >= 0; i-= 2)
    {
        int bit = (value >> i) & 0x3;
        if (tmp->children[bit] == nullptr)
        {
            return;
        }
        tmp = tmp->children[bit];
    }

    while(tmp->hasNoChild() && tmp->parent != nullptr)
    {
        Node* parent = tmp->parent;
        delete tmp;
        tmp = parent;
    }
    
}

bool RadixTree::find(int32_t value)
{
    Node* tmp = root;
    for (int i = 30; i >= 0; i-= 2)
    {
        int bit = (value >> i) & 0x3;
        if (tmp->children[bit] == nullptr)
        {
            return false;
        }
        tmp = tmp->children[bit];
    }
    return true;
}

uint32_t RadixTree::size()
{
    return root->countSize();
}

uint32_t RadixTree::height()
{
    if (root->hasNoChild())
    {
        return 1;
    } else {
        return 17;
    }
}

RadixTree::~RadixTree()
{
    delete root;
}