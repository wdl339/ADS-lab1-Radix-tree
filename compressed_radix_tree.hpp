// implement a radix tree that support node compressino and store int32_t values
// each parent node has 4 children, representing 2 bits

#ifndef COMPRESSED_RADIX_TREE_H
#define COMPRESSED_RADIX_TREE_H

#include <cstdint>
#include <algorithm>
#include "tree.hpp"

class CNode{
public:
    uint32_t val;
    int len;
    CNode* parent;
    CNode* children[4];

    CNode(CNode *p = nullptr, uint32_t v = 0, int l = 0){
        val = v;
        len = l;
        parent = p;
        for(int i = 0; i < 4; i++){
            children[i] = nullptr;
        }
    }

    int hasOneChild(){
        int count = 0;
        int res;
        for(int i = 0; i < 4; i++){
            if(children[i] != nullptr){
                count++;
                res = i;
            }
        }
        if(count == 1){
            return res;
        }
        return -1;
    }

    bool hasNoChild(){
        for(int i = 0; i < 4; i++){
            if(children[i] != nullptr){
                return false;
            }
        }
        return true;
    }

    uint32_t countSize(){
        uint32_t count = 0;
        for(int i = 0; i < 4; i++){
            if(children[i] != nullptr){
                count += children[i]->countSize();
            }
        }
        return count + 1;
    }

    uint32_t countHeight(){
        uint32_t height = 0;
        for(int i = 0; i < 4; i++){
            if(children[i] != nullptr){
                height = std::max(height, children[i]->countHeight());
            }
        }
        return height + 1;
    }

    ~CNode(){
        for (int i = 0; i < 4; i++)
        {
            if (parent->children[i] == this)
            {
                parent->children[i] = nullptr;
                break;
            }
        }
        parent = nullptr;
        for(int i = 0; i < 4; i++){
            if(children[i] != nullptr){
                delete children[i];
            }
        }
    }  
};


class CompressedRadixTree : public Tree
{
    CNode* root;

public:
    CompressedRadixTree();
    ~CompressedRadixTree();
    // basic operation
    void insert(int32_t value);
    void remove(int32_t value);
    bool find(int32_t value);
    // statistics
    uint32_t size();
    uint32_t height();
};

#endif