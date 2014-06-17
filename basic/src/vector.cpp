#include <stdio.h>
#include <stddef.h>

template <typename T>
class vector {
public:
	/* constructor */
	vector() {
		data = (T*)malloc(1*sizeof(T));
	}
	vector(uint64_t size) {
		data = (T*)malloc(size*sizeof(T));
	}

	//destructor
	~vector(){
	}

	// iterator
	

	// assign operator
	



private:
	T *data;
};


int main() {

	return 0;
}
