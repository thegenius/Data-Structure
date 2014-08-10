#include "RBTree.h"
#include <algorithm>
enum {
	RED   = 0,
	BLACK = 1
};

/************************************************
*           查询相关节点的辅助函数              *
*************************************************/
TreeNode* getGrandParent(TreeNode *node) {
	return node->parent->parent;
}

TreeNode* getUncle(TreeNode *node) {
	auto grandParent = getGrandParent(node);
	if (grandParent == nullptr) {
		return nullptr;
	}
	if (node->parent == grandParent->left) {
		return grandParent->right;
	} else {
		return grandParent->left;
	}
}

TreeNode* getBrother(TreeNode *node) {
	auto parent = node->parent;
	if (parent == nullptr) {
		return nullptr;
	}
	if (node = parent->left) {
		return parent->right;
	} else {
		return parent->left;
	}
}

/************************************************
*           用于平衡操作的旋转函数              *
*************************************************/
TreeNode* rotateLeft(TreeNode* node) {
	TreeNode* x = node->right;
	node->right = x->left;
	x->left = node;

	x->color = node->color;
	node->color = RED;
	return x;
}

TreeNode* rotateRight(TreeNode* node) {
	TreeNode* x = node->left;
	node->left = x->right;
	x->right = node;

	x->color = node->color;
	node->color = RED;
	return x;
}

void flipColor(TreeNode* node) {
	node->color = !node->color;
	node->left->color = !node->left->color;
	node->right->color = !node->right->color;
}

TreeNode* moveRedLeft(TreeNode* tree) {
	flipColor(tree);
	if (tree->right->left->color == RED) {
		tree->right = rotateRight(tree->right);
		tree = rotateLeft(tree);
		flipColor(tree);
	}
	return tree;
}

TreeNode* moveRedRight(TreeNode* tree) {
	flipColor(tree);
	if (tree->left->left->color == RED) {
		tree = rotateRight(tree->right);
		flipColor(tree);
	}
	return tree;
}


TreeNode* insertNode(TreeNode*& root, int key) {
	// p指向需要修改的内存位置
	TreeNode **p = &root;
	TreeNode *x = root;
	// 查找插入位置, p记录实际需要修改的内存位置
	while (x != nullptr) {
		if (key < x->key) {
			p = &x->left;
			x = x->left;
		} else {
			p = &x->right;
			x = x->right;
		}
	}
	*p = new TreeNode(key, 0);
	return *p;
}

void insertFixUp(TreeNode* tree, TreeNode* z){
	// case 1 : 插入根节点， 直接涂成 BLACK
	// case 2 : 插入父节点是黑色，自己是红色，什么也不做
	// case 3 : 插入父节点是红色，且叔节点也是红色，
	//          对应于2-3-4树中，插入到一个已经有3个值，4个孩子的节点
	//          节点分裂，中央元素尝试融合到父节点
	//          将父节点和叔节点染成 BLACK，祖父节点染成 RED
}





TreeNode* deleteNode(TreeNode*& root, int key) {
	TreeNode **y  = nullptr; // 记录实际(*y)->key == key的节点
	TreeNode **px = nullptr; // 记录实际删除的叶子节点
	TreeNode **x  = &root;   // 遍历指针
	while (*x != nullptr) {
		if (key < (*x)->key) {
			px = x;
			x  = &(*x)->left;
		} else {
			if (key == (*x)->value) {
				y = x;
			}
			px = x;          //px最后实际找到的是中序遍历的后继节点
			x  = &(*x)->right;
		}
	}

	TreeNode *ret = nullptr;
	if (y == nullptr) {
		// 如果没有找到key对应的节点，不删除任何节点
		ret = nullptr;
	} else if ((*y)->right == nullptr) {
		// 待删除节点右子树为空，删除本节点，
		// 需要引用到本节点的地方引用到本节点的左子树上
		ret = *y;
		*y = (*y)->left;
	} else {
		// 如果右子树存在，无论左子树是否存在，一定可以找到中序后继
		// 直接和中序后继交换内容，删除中序后继
		std::swap((*y)->key,   (*px)->key);
		std::swap((*y)->value, (*px)->value);
		ret = *px;
		*px = (*px)->right;
	}
	return ret;
}

void deleteFixUp(TreeNode* tree, TreeNode* n){
	// case 1 : 
	// case 2 : 
	// case 3 : 
	// case 4 : 
	// case 5 :

	if (n->parent == nullptr) {
		// case 1
	} else {
		if (getBrother(n)->color == RED) {
		// case 2
		} else {
			if (getBrother(n)->right->color == BLACK) {
				if (getBrother(n)->left->color == BLACK) {
					if (n->parent->color == BLACK) {
						// case 2
					} else {
						// case 4
					}
				} else {
					//case 5
				}
			} else {
			// case 6

			}
		}
	}
}


TreeNode* search(TreeNode* node, int key) {
	auto x = node;
	while (x != nullptr) {
		if (key == x->key) {
			return x;
		} else if (key < node->key) {
			x = x->left;
		} else {
			x = x->right;
		}
	}
	return nullptr;
}







