struct TreeNode {
	TreeNode(int key, int value)
		: key(key), value(value) {
			parent = nullptr;
			left   = nullptr;
			right  = nullptr;
			color  = RED;
	}

	int key;
	int value;

	int      color;
	TreeNode *parent;
	TreeNode *left;
	TreeNode *right;
};