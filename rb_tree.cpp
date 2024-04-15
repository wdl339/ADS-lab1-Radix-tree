#include <iostream>
#include <cstdio>
#include "rb_tree.hpp"
using namespace std;


RBTree::RBTree() {
	root = NULL;
}


RBTree::~RBTree() {
	clear();
}

// 左旋
void RBTree::leftRotate(RBNode<int> *x) {
	// x 的右儿子为 y
	RBNode<int> *y = x->right;
	// y的左儿子设为 x 的右儿子
	x->right = y->left;
	if (y->left != NULL) {
		y->left->parent = x;
	}
	y->parent = x->parent;
	if (x->parent == NULL) {
		root = y;
	} else if (x == x->parent->left) {
		x->parent->left = y;
	} else {
		x->parent->right = y;
	}
	y->left = x;
	x->parent = y;
}

// 右旋
void RBTree::rightRotate(RBNode<int> *y) {
	RBNode<int> *x = y->left;
	y->left = x->right;
	if (x->right != NULL) {
		x->right->parent = y;
	}
	x->parent = y->parent;
	if (y->parent == NULL) {
		root = x;
	} else if (y == y->parent->right) {
		y->parent->right = x;
	} else {
		y->parent->left = x;
	}
	x->right = y;
	y->parent = x;
}

// 插入一个键为 key 的节点的操作
void RBTree::insert(int key) {
    // 重复的直接返回
    if (find(key)) return;
	// 要插入的节点 node
	RBNode<int> *node = new RBNode<int>(key, BLACK, NULL, NULL, NULL);

	// 找出树中 node 应在的位置 y
	RBNode<int> *y = NULL;
	RBNode<int> *x = root;
	while (x != NULL) {
		y = x;
		if (node->key < x->key) {
			x = x->left;
		} else {
			x = x->right;
		}
	}
	node->parent = y;
	if (y == NULL) {
		root = node;
	} else if (node->key < y->key) {
		y->left = node;
	} else {
		y->right = node;
	}
	node->left = NULL;
	node->right = NULL;
	node->color = RED;

	// 添加修正操作
	insertFix(node);
}

// 添加节点的修正操作
void RBTree::insertFix(RBNode<int> *node) {
	RBNode<int> *p, *pp;
	// p 为 node 节点的父节点
	while ((p = node->parent) && p->color == RED) {
		// pp 为 node 节点的祖父节点
		pp = p->parent;
		if (p == pp->left) {
			// case 1 叔叔为红色
			RBNode<int> *uncle = pp->right;
			if (uncle && uncle->color == RED) {
				p->color = BLACK;
				uncle->color = BLACK;
				pp->color = RED;
				node = pp;
			} else if (node == p->right) { // case 2
				RBNode<int> *tmp;
				leftRotate(p);
				tmp = p;
				p = node;
				node = tmp;
			} else if (node == p->left) { // case 3
				p->color = BLACK;
				pp->color = RED;
				rightRotate(pp);
			}
		} else {
			RBNode<int> *u = pp->left;
			if (u && u->color == RED) {
				p->color = BLACK;
				u->color = BLACK;
				pp->color = RED;
				node = pp;
			} else if (node == p->left) {
				RBNode<int> *tmp;
				rightRotate(p);
				tmp = p;
				p = node;
				node = tmp;
			} else if (node == p->right) {
				p->color = BLACK;
				pp->color = RED;
				leftRotate(pp);
			}
		}
	}
	root->color = BLACK;
}

// 删除节点操作
void RBTree::remove(int key) {
    // 先查找要删除的点, 若不存在直接返回
    RBNode<int> *node = find(root, key);
    if (node == NULL) return;
    // 删除操作
    RBNode<int> *child, *parent;
    int color;
    // 存在左右孩子
    if (node->left != NULL && node->right != NULL) {
        RBNode<int> *re = node->right;
        // re 为要替换掉 node 的节点
        while(re->left != NULL) {
            re = re->left;
        }
        if (node->parent) {
            // node 是其父结点的左孩子
            if (node == node->parent->left) {
                node->parent->left = re;
            } else {
                node->parent->right = re;
            }
        } else {
            // node 为根结点
            root = re;
        }
        child = re->right;
        parent = re->parent;
        color = re->color;
        if (parent == node) {
            parent = re;
        } else {
            if (child)
                child->parent = parent;
            parent->left = child;
            re->right = node->right;
            node->right->parent = re;
        }

        re->parent = node->parent;
        re->color = node->color;
        re->left = node->left;
        node->left->parent = re;
        // 黑色节点需调整
        if (color == BLACK)
            eraseFix(child, parent);
        delete node;
        return;
    }

    if (node->left) {
        child = node->left;
    } else {
        child = node->right;
    }

    parent = node->parent;
    color = node->color;
    if (child)
        child->parent = parent;
    
    if (parent) {
        if (node == parent->left) {
            parent->left = child;
        } else {
            parent->right = child;
        }
    } else {
        root = child;
    }

    if (color == BLACK) {
        eraseFix(child, parent);
    }
    delete node;
}

// 删除节点的修正操作
void RBTree::eraseFix(RBNode<int> *node, RBNode<int> *parent) {
    RBNode<int> *brother;
    while((node == NULL || node->color == BLACK) && node != root) {
        // node 为左节点
        if (node == parent->left) {
            brother = parent->right;
            if (brother->color == RED) {
                // case 1: brother is red node
                brother->color = BLACK;
                parent->color = RED;
                leftRotate(parent);
                brother = parent->right;
            } else if ((brother->left == NULL || brother->left->color == BLACK) &&
                       (brother->right == NULL || brother->right->color == BLACK)) {
                // case 2: brother is black node and brother's 2 children is black
                brother->color = RED;
                node = parent;
                parent = node->parent;
            } else {
                if (brother->right == NULL || brother->right->color == BLACK) {
                    // case 3: brother's right child is black, left child is red
                    brother->left->color = BLACK;
                    brother->color = RED;
                    rightRotate(brother);
                    brother = parent->right;
                } else {
                    // case 4: brother's right child is red
                    brother->color = parent->color;
                    parent->color = BLACK;
                    brother->right->color = BLACK;
                    leftRotate(parent);
                    node = root;
                    break;
                }
            }
        } else {
            // node 为右节点
            brother = parent->left;
            if (brother->color == RED) {
                // case 1: brother's color is RED
                brother->color = BLACK;
                parent->color = RED;
                rightRotate(parent);
                brother = parent->left;
            } else if ((brother->left == NULL || brother->left->color == BLACK) &&
                       (brother->right == NULL || brother->right->color == BLACK)) {
                // case 2: brother's 2 children node is black
                brother->color = RED;
                node = parent;
                parent = node->parent;
            } else {
                if (brother->left == NULL || brother->left->color == BLACK) {
                    // case 3: brother's left child is black, right child is red
                    brother->right->color = BLACK;
                    brother->color = RED;
                    leftRotate(brother);
                    brother = parent->left;
                } else {
                    // case 4: brother's left child is red
                    brother->color = parent->color;
                    parent->color = BLACK;
                    brother->left->color = BLACK;
                    rightRotate(parent);
                    node = root;
                    break;
                }
            }
        }
    }
    if (node) {
        node->color = BLACK;
    }
}

// 递归查找节点
RBNode<int>* RBTree::find(RBNode<int>* node, int key) {
    if (node == NULL || node->key == key) return node;
    if (key < node->key)
        return find(node->left, key);
    else
        return find(node->right, key);
}

// 查找节点操作
bool RBTree::find(int key) {
    RBNode<int> *node = find(root, key);
    if (node == NULL) return false;
    return true;
}

// 递归清除节点
void RBTree::clear(RBNode<int> * &node) {
	if (node == NULL) return;
	if (node->left != NULL) {
		return clear(node->left);
	}
	if (node->right != NULL) {
		return clear(node->right);
	}
	delete node;
	node = NULL;
}

// 清空操作
void RBTree::clear() {
	clear(root);
}

// 递归打印节点信息
void RBTree::print(RBNode<int> *node, int key, int direction) {
	if (node != NULL) {
		if (direction == 0) {
			printf("key = %d, color = black (root)\n", node->key);
		} else {
			printf("key = %d, color = ", node->key);
			if (node->color == RED)
				printf("red");
			else
				printf("black");
			printf(", %d's ", key);
			if (direction == 1)
				printf("right child\n");
			else
				printf("left child\n");
		}
		print(node->left, node->key, -1);
		print(node->right, node->key, 1);
	}
}

// debug
void RBTree::print() {
	if (root == NULL) {
		printf("The tree is empty.\n");
		return;
	}
	print(root, root->key, 0);
}