// implement a radix tree that support node compressino and store int32_t values
// each parent node has 4 children, representing 2 bits
#include <cstdint>
#include <algorithm>
#include "tree.hpp"

class Node{
public:
    uint32_t val;
    int len;
    Node* parent;
    Node* children[4];

    Node(Node *p = nullptr, uint32_t v, int l){
        val = v;
        len = l;
        parent = p;
        for(int i = 0; i < 4; i++){
            children[i] = nullptr;
        }
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

    ~Node(){
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
    Node* root;

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