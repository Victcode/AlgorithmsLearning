#include <iostream>
#include <string>
#include <fstream>
#include <cassert>
#include <vector>
#include <time.h>
#include <chrono>

class UnionFind
{
private:
	int count;
	int size_id;
	int* weght_in;
	int* id;

public:
	UnionFind(int num);
	~UnionFind();

	// for all methos, return true if the two elements are in the same set
	int isConnecked(int a, int b, int (UnionFind::* find)(int)); // equal to "connected" in book
	// check index
	void check_index(int idx) {
		if (idx < 0 || idx >= size_id)
			throw "Error! index is wrong!";
	}
	int get_count() { return count;}

	void reset() {
		count = size_id;
		for (int i = 0; i < size_id; ++i){
			id[i] = i;
			weght_in[i] = 1;
		}
	};

	// quick-find
	int   find_qf(int a);
	void  union_qf(int a, int b);
	// quick-union
	int   find_qu(int a);
	void  union_qu(int a, int b);
	// weighted quick-union
	int   find_wqu(int a);
	void  union_wqu(int a, int b);
	// path commression weighted quick-union
	int   find_pwqu(int a);
	void  union_pwqu(int a, int b);

};

UnionFind::UnionFind(int num){
	count = num;
	size_id = num;
	id = new int[num];
	weght_in = new int[num]; // for weighted and path compression quick-union
	for (int i = 0; i < num; ++i){
		id[i] = i;
		weght_in[i] = 1;
	}
}

UnionFind::~UnionFind(){
	delete [] id;
	delete [] weght_in;
}

int UnionFind::isConnecked(int a, int b, int (UnionFind::* find)(int)) {
	return (this->* find)(a) == (this->* find)(b);
}

// =================== quick-find ==============================
int UnionFind::find_qf(int a) {
	check_index(a);
	return id[a];
}
void UnionFind::union_qf(int a, int b) {
	check_index(a);
	check_index(b);
	int aID = find_qf(a);
	int bID = find_qf(b);

	if (aID == bID) return;

	for (int i = 0; i < size_id; ++i) {
		if(id[i] == bID)
			id[i] = aID;
	}
	count--;
}

// =================== quick-union ==============================
// find the set root, reduce the io times 
int UnionFind::find_qu(int n) {
	check_index(n);
	while (n != id[n] ) {
		n = id[n];
	}
	return n;
}
void UnionFind::union_qu(int a, int b) {
	check_index(a);
	check_index(b);

	int aID = find_qu(a);
	int bID = find_qu(b);

	if (aID == bID) return;
	id[bID] = aID;
	count--;
}

// =================== weighted quick-union ==============================
// find the set root, reduce the io times 
int UnionFind::find_wqu(int n) {
	check_index(n);
	while (n != id[n] ) {
		n = id[n];
	}
	return n;
}
void UnionFind::union_wqu(int a, int b) {
	check_index(a);
	check_index(b);
	int aID = find_wqu(a);
	int bID = find_wqu(b);

	if (aID == bID) return;

	if (weght_in[aID] >= weght_in[bID]) {
		id[bID] = aID;
		weght_in[aID] += weght_in[bID];
	} else
	{
		id[aID] = bID;
		weght_in[bID] += weght_in[aID];
	}
	
	count--;
}

// =================== path compression weighted quick-union ==============================
// find the set root, reduce the io times 
int UnionFind::find_pwqu(int n) {
	check_index(n);
	int root = n;
	// firstly find the root node
	while (root != id[root] ) {
		root = id[root];
	}

	// change parent node
	while (n != id[root]) {
		int new_n = id[n];
		id[n] = root;
		n = new_n;
	}
	
	return root;
}
void UnionFind::union_pwqu(int a, int b) {
	check_index(a);
	check_index(b);
	int aID = find_wqu(a);
	int bID = find_wqu(b);

	if (aID == bID) return;
	
	if (weght_in[aID] >= weght_in[bID]) {
		id[bID] = aID;
		weght_in[aID] += weght_in[bID];
	} else
	{
		id[aID] = bID;
		weght_in[bID] += weght_in[aID];
	}
	count--;
}