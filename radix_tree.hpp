
#include <cstdint>
#include "tree.hpp"

class Node{
public:
    Node* parent;
    Node* children[4];

    Node(Node *p = nullptr){
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

class RadixTree : public Tree
{
    Node* root;

public:
    RadixTree();
    ~RadixTree();
    // basic operation
    void insert(int32_t value);
    void remove(int32_t value);
    bool find(int32_t value);
    // statistics
    uint32_t size();
    uint32_t height();
};
