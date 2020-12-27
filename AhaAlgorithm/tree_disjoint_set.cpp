/*
问题：实现并查集。
分析：（1）并查集是将本来相互独立的元素进行归类，归类之后的每一类之间仍旧是相互独立的。
			（2）基于树结构实现的，根据两个元素是否有相同的父节点来确定这两个元素是否是属于同一类。
					 分类之后的每个类彼此之间即使相互独立的树，可以看做是一个森林。
			（3）并查集主要分两个步骤：合并、查找
				   查找：确定元素属于哪一个子集；
					 合并：将两个子集合并成同一个集合；
			（4）路径压缩，在查找的时候会出现关系链很长的问题，比如，1是2的父节点，2是3的，3是4的，
					这四个元素属于同一个子集，1 <- 2 <- 3 <- 4，现在这样表示使得树的深度较大，在继续查找的时候
					效率较低，路径压缩就是用来优化这个问题，在查找的过程中，发现1是2的父节点，2是3的父节点，那么
					就将3的父节点也设置为1，同样4的父节点也设置为1，也就是2、3、4都为同一个父节点，从而提高查找
					效率。具体实现方法用递归。
*/
#include <iostream>
#include "datas.hpp"

class DisjointSet
{
private:
	int *pro_data = nullptr;
    int num_elements;
	int num_relat;

public:
	DisjointSet(int in_num_elem, int in_num_relat);
	~DisjointSet();

	void init();
	int  find(int index);
	void merge(int index1, int index2);
	void get_sub_sets();
};

DisjointSet::DisjointSet(int in_num_elem, int in_num_relat) :
							num_elements(in_num_elem), 
							num_relat(in_num_relat) {
	pro_data = new int[num_elements];
}

DisjointSet::~DisjointSet(){
	delete[](pro_data);
}

void DisjointSet::init() {
	for (int i = 0; i < num_elements; i++) {
		pro_data[i] = i;
	}
	return;
}

int DisjointSet::find(int index) {
	if (index == pro_data[index])
		return index;  // 
	else
		return find(pro_data[index]);
}

void DisjointSet::merge(int index1, int index2) {
	// One rule here is to take the index1 node as the father node
	int father1 = find(index1);
	int father2 = find(index2);

	if (father1 != father2) {
		// NOTE: Change the father point's father point
		pro_data[father2] = father1;
	}
	return;
}

void DisjointSet::get_sub_sets() {
	// Computing how many sub-sets
	int count_sets = 0;
	for (int i = 0; i < num_elements; ++i) {
		if (pro_data[i] == i)
			count_sets++;
	} 
	std::cout << "The number of sub-sets is: " << count_sets << std::endl;
}

int main() {
	int in_num_elem  = 10;
	int in_num_relat = 9;
	DisjointSet my_disjoint(in_num_elem, in_num_relat);
	my_disjoint.init();
	for (int i = 0; i < in_num_relat; ++i) {
		my_disjoint.merge(relat_data[i][0], relat_data[i][1]);
	}
	my_disjoint.get_sub_sets();

	return 1;
}