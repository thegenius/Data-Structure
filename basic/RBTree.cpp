#include "RBTree.h"
#include <algorithm>
enum {
	RED   = 0,
	BLACK = 1
};

/************************************************
*           ��ѯ��ؽڵ�ĸ�������              *
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
*           ����ƽ���������ת����              *
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
	// pָ����Ҫ�޸ĵ��ڴ�λ��
	TreeNode **p = &root;
	TreeNode *x = root;
	// ���Ҳ���λ��, p��¼ʵ����Ҫ�޸ĵ��ڴ�λ��
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
	// case 1 : ������ڵ㣬 ֱ��Ϳ�� BLACK
	// case 2 : ���븸�ڵ��Ǻ�ɫ���Լ��Ǻ�ɫ��ʲôҲ����
	// case 3 : ���븸�ڵ��Ǻ�ɫ������ڵ�Ҳ�Ǻ�ɫ��
	//          ��Ӧ��2-3-4���У����뵽һ���Ѿ���3��ֵ��4�����ӵĽڵ�
	//          �ڵ���ѣ�����Ԫ�س����ںϵ����ڵ�
	//          �����ڵ����ڵ�Ⱦ�� BLACK���游�ڵ�Ⱦ�� RED
}





TreeNode* deleteNode(TreeNode*& root, int key) {
	TreeNode **y  = nullptr; // ��¼ʵ��(*y)->key == key�Ľڵ�
	TreeNode **px = nullptr; // ��¼ʵ��ɾ����Ҷ�ӽڵ�
	TreeNode **x  = &root;   // ����ָ��
	while (*x != nullptr) {
		if (key < (*x)->key) {
			px = x;
			x  = &(*x)->left;
		} else {
			if (key == (*x)->value) {
				y = x;
			}
			px = x;          //px���ʵ���ҵ�������������ĺ�̽ڵ�
			x  = &(*x)->right;
		}
	}

	TreeNode *ret = nullptr;
	if (y == nullptr) {
		// ���û���ҵ�key��Ӧ�Ľڵ㣬��ɾ���κνڵ�
		ret = nullptr;
	} else if ((*y)->right == nullptr) {
		// ��ɾ���ڵ�������Ϊ�գ�ɾ�����ڵ㣬
		// ��Ҫ���õ����ڵ�ĵط����õ����ڵ����������
		ret = *y;
		*y = (*y)->left;
	} else {
		// ������������ڣ������������Ƿ���ڣ�һ�������ҵ�������
		// ֱ�Ӻ������̽������ݣ�ɾ��������
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







