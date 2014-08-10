#include <stdio.h>
#include <map>
using namespace std;


struct edge_t;
struct node_t;

struct edge_t {
	char* str;
	void* value;
	struct node_t* node;
};

struct node_t {
	struct edge_t e[26];
};



bool insertPair(node_t* tree, const char* key, void *value) {
	if (key == NULL) {
		return true;	
	}

	for (char ch=*key; ch!='\0'; ch=*(++key)) {
				
	}
	return true;
}

bool deletePair(node_t* tree, const char* key) {
	if (key == NULL) {
		return true;
	}



}

int main() {

	multimap<char,int> mymap;
	mymap.insert('a', 10);
	mymap.insert(std::pair<char,int>('a', 20));
	mymap.insert(std::pair<char,int>('a', 30));
	mymap.insert(std::pair<char,int>('a', 40));
	mymap.insert(std::pair<char,int>('a', 50));

	auto ret = mymap.equal_range('a');
	printf("a=>"); 
	for (auto it=ret.first; it!=ret.second; ++it) {
		printf("%d\n", it->second);
	}



	return 0;
}


