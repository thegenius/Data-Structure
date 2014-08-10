#include <stdio.h>
#include <stdint.h>

struct lt_node_t {
public:
	lt_node_t(int64_t data) : 
		data(data),dist(0),lchild(NULL),rchild(NULL) {
	}
	int64_t data;
	int64_t dist;
	struct lt_node_t *lchild;
	struct lt_node_t *rchild;
};

template <typename T>
inline void swap(T &a, T&b) {
	T tmp = a;
	a = b;
	b = tmp;
}


void inOrder(lt_node_t *root) {
	if (root != NULL) {
		inOrder(root->lchild);
		printf("%ld\n", root->data);
		inOrder(root->rchild);
	}
}

lt_node_t* merge(lt_node_t *&a, lt_node_t* &b) {
	if (a==NULL || b==NULL) {
		return a==NULL?b:a;
	}
	
	if (a->data > b->data) {
		swap(a,b);
	}

	a->rchild = merge(a->rchild, b);
	
	if (a->lchild==NULL || a->rchild->dist > a->lchild->dist) {
		swap(a->lchild, a->rchild);
	}
	
	if (a->rchild == NULL) {
		a->dist = 0;
	} else {
		a->dist = a->rchild->dist + 1;
	}
	
	return a;
}

void insert(lt_node_t *&root, int x) {
	lt_node_t *p = new lt_node_t(x);
	
	root = merge(root, p);
}

lt_node_t* extractMin(lt_node_t *&root) {
	lt_node_t *p = root;
	root = merge(root->lchild, root->rchild);
	return p;
}


int main() {
	lt_node_t *root = new lt_node_t(1);
	insert(root, 2);
	insert(root, 3);
	insert(root, 7);
	insert(root, 4);
	insert(root, 6);
	insert(root, 5);
	lt_node_t *p = extractMin(root);
	printf("%ld\n", p->data);
	p = extractMin(root);
	printf("%ld\n", p->data);
	p = extractMin(root);
	printf("%ld\n", p->data);
	p = extractMin(root);
	printf("%ld\n", p->data);
	p = extractMin(root);
	printf("%ld\n", p->data);
	p = extractMin(root);
	printf("%ld\n", p->data);
	p = extractMin(root);
	printf("%ld\n", p->data);





	return 0;
}











