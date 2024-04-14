#ifndef RB_TREE_H
#define RB_TREE_H

// https://github.com/Waydrow/RBTree/tree/master

#include "tree.hpp"

#define RED		0
#define BLACK	1

template <class T>
class RBNode {
public:
	T key;
	int color;
	RBNode *left;
	RBNode *right;
	RBNode *parent;
    // Constructor
	RBNode(T _key, int _color, RBNode *_left, RBNode *_right, RBNode *_parent)
		:key(_key), color(_color), left(_left), right(_right), parent(_parent) {}
};

class RBTree : public Tree{
private:
    // 根结点
	RBNode<int> *root;

	// 左旋操作
	void leftRotate(RBNode<int> *x);
	// 右旋操作
	void rightRotate(RBNode<int> *y);
	// 添加的修正操作
	void insertFix(RBNode<int> *node);
	// 删除的修正操作
	void eraseFix(RBNode<int> *node, RBNode<int> *parent);
    // 查找私有接口
    RBNode<int>* find(RBNode<int> *node, int key);
    // 清空的私有接口
	void clear(RBNode<int> * &node);
	// 打印的私有接口
	void print(RBNode<int> *node, int key, int direction);

public:

	RBTree();
	// 插入操作
	void insert(int key);
	// 删除操作
	void remove(int key);
	// 查找操作
	bool find(int key);
	// 清空操作
	void clear();
	// debug
	void print();

    unsigned int size(){
        return 0;
    }

    unsigned int height(){
        return 0;
    }

	~RBTree();
};

#endif