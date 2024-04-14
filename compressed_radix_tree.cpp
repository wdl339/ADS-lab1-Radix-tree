#include "compressed_radix_tree.hpp"

CompressedRadixTree::CompressedRadixTree()
{
    root = new CNode();
}

void CompressedRadixTree::insert(int32_t value)
{
    CNode* tmp = root;

    for (int i = 32; i > 0;)
    {
        int bit = (value >> (i - 2)) & 0x3;
        if (tmp->children[bit] == nullptr)
        {
            uint32_t val = ((uint32_t)value << (32 - i)) >> (32 - i);
            tmp->children[bit] = new CNode(tmp, val, i);
            break;
        }
        tmp = tmp->children[bit];

        int len = tmp->len;
        uint32_t bit2 = ((uint32_t)value << (32 - i)) >> (32 - len);

        if (bit2 != tmp->val)
        {
            uint32_t mask2 = bit2 ^ tmp->val;
            int len2 = 0;
            while (mask2)
            {
                mask2 >>= 1;
                len2++;
            }
            if (len2 % 2 != 0)
                len2++;
            
            CNode* p = tmp->parent;
            p->children[bit] = new CNode(p, tmp->val >> len2, len - len2);
            CNode* q = p->children[bit];
            tmp->parent = q;
            uint32_t new_val = (tmp->val << (32 - len2)) >> (32 - len2);
            q->children[new_val >> (len2 - 2)] = tmp;
            tmp->val = new_val;
            tmp->len = len2;

            int bias = i - len + len2;
            uint32_t val = ((uint32_t)value << (32 - bias)) >> (32 - bias);
            q->children[val >> (bias - 2)] = new CNode(q, val, bias);

            break;
        }

        i -= len;
    }
}

void CompressedRadixTree::remove(int32_t value)
{
    CNode* tmp = root;
    for (int i = 32; i > 0;)
    {
        int bit = (value >> (i - 2)) & 0x3;
        if (tmp->children[bit] == nullptr)
        {
            return;
        }
        tmp = tmp->children[bit];

        int len = tmp->len;
        uint32_t bit2 = ((uint32_t)value << (32 - i)) >> (32 - len);

        if (bit2 != tmp->val)
        {
            return;
        }

        i -= len;
    }

    CNode* p = tmp->parent;
    delete tmp;
    int idx = -1;
    if ((idx = p->hasOneChild()) != -1)
    {
        CNode* q = p->children[idx];
        p->len = q->len + p->len;
        p->val = p->val << q->len | q->val;
        for (int i = 0; i < 4; i++)
        {
            if (q->children[i] != nullptr)
            {
                p->children[i] = q->children[i];
                q->children[i]->parent = p;
                q->children[i] = nullptr;
            }
        }
        delete q;
    }
    
}

bool CompressedRadixTree::find(int32_t value)
{
    CNode* tmp = root;
    for (int i = 32; i > 0; )
    {
        uint32_t bit = (value >> (i - 2)) & 0x3;
        if (tmp->children[bit] == nullptr)
        {
            return false;
        }
        tmp = tmp->children[bit];

        int len = tmp->len;
        uint32_t bit2 = ((uint32_t)value << (32 - i)) >> (32 - len);

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
    
    return root->countHeight();
}

CompressedRadixTree::~CompressedRadixTree()
{
    delete root;
}
