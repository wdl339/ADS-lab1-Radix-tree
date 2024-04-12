#include "compressed_radix_tree.hpp"

CompressedRadixTree::CompressedRadixTree()
{
    root = new Node();
}

CompressedRadixTree::~CompressedRadixTree()
{
    delete root;
}

void CompressedRadixTree::insert(int32_t value)
{
    Node* tmp = root;
    uint32_t val = (uint32_t)value;

    for (int i = 30; i >= 0; )
    {
        int bit = (value >> i) & 0x3;
        if (tmp->children[bit] == nullptr)
        {
            tmp->children[bit] = new Node(tmp, val, i + 2);
            break;
        }
        tmp = tmp->children[bit];

        int len = tmp->len;
        int32_t mask =  ~(0xffffffff << len);
        uint32_t bit2 = (value >> (i - len + 2)) & mask;

        if (bit2 != tmp->val)
        {
            // 选取两个数字⼆进制表示的最⻓公共 2n 个⽐特前缀替代当前节点，并创建两个节点分别保存这两个数字后缀的不同部分
            Node* p = tmp->parent;

            break;
        }

        val = val >> tmp->len;
        i -= tmp->len;
    }
}

void CompressedRadixTree::remove(int32_t value)
{
    
}

bool CompressedRadixTree::find(int32_t value)
{
    Node* tmp = root;
    for (int i = 30; i >= 0; )
    {
        uint32_t bit = (value >> i) & 0x3;
        if (tmp->children[bit] == nullptr)
        {
            return false;
        }
        tmp = tmp->children[bit];

        int len = tmp->len;
        int32_t mask =  ~(0xffffffff << len);
        uint32_t bit2 = (value >> (i - len + 2)) & mask;

        if (bit2 != tmp->val)
        {
            return false;
        }

        i -= len;
    }
    return true;
}

uint32_t CompressedRadixTree::size()
{
    return root->countSize();
}

uint32_t CompressedRadixTree::height()
{
    
    return 0;
}
