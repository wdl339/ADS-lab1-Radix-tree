
#include <cstdint>
#include "tree.hpp"
class RadixTree : public Tree
{
    // To Be Implemented
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
