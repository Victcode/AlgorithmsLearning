/*
问题：实现三种排序算法，分别为桶排序、冒泡排序、快速排序
分析：（1）桶排序，书中介绍的是简化版的，查资料也有说是叫做计数排序。为了便于区分就先叫他计数排序吧。
		  计算排序需要提前知道待排序数据的取值范围，申请一个相同大小的计数数组，遍历待排数据，
		  然后根据遍历到的数据修改计数数组，比如遍历到了2，则在计数数组下标为2的位置加1.遍历完成后，
		  在遍历一次计数数组，为0不打印，为n则打印对应下标n次即可。
		  那么什么又是真正的桶排序呢，桶排序主要分为两步：分桶、排序。现将原始数据按照某种规则进行分桶，
		  然后对每个桶中的数据再使用快排等算法进行排序。所以分桶是关键，数据分布越均匀，整体的时间
		  复杂度越低
	 （2）冒泡排序，简单，时间复杂度最高的排序算法。
	 	  以从小到大排序为例，每次比较两个相邻的元素，遇到比他小的就交换。一次遍历只能确定一个元素，
		  且是末位元素。时间复杂度是O(N*N)
	 （3）快速排序，分治的思想
	 	  以从小到大的排序为例，随机选取一个点，找到他应该在的位置，就是让左边的数都小于他，
		  右边的数都大于他。然后以该数为分界线，对左边和右边也进行这样的操作，通过递归来实现。
*/
#include <iostream>
#include "datas.hpp"

class Sort
{
private:
	int len_data;
public:
	Sort(int in_len_data);
	~Sort();

	void bubble_sort();
	void quick_sort(int start_index, int end_index);
	void count_sort();
};

Sort::Sort(int in_len_data) : len_data(in_len_data) {}

Sort::~Sort() {}

void Sort::bubble_sort() {
	for (int i = 0; i < len_data - 1; ++i) {
		for (int j = 0; j < len_data - 1 - i; ++j) {
			if (sort_data[j] > sort_data[j + 1]) {
				int temp = sort_data[j];
				sort_data[j] = sort_data[j + 1];
				sort_data[j + 1] = temp;
			}
		}
	}

	std::cout << "The bubble sort result: " << std::endl;
	for (int i = 0; i < len_data; ++i) {
		std::cout << sort_data[i] << " ";
	}
	std::cout << std::endl;
	return;
}

void Sort::quick_sort(int start_index, int end_index) {

	if (start_index < 0 || end_index > len_data || end_index < start_index)
		return;

	int i  = start_index;
	int j  = end_index;

	int bench_data = sort_data[start_index];
	while (i < j) {
		while (sort_data[j] >= bench_data && j > i)
			j--;
		while (sort_data[i] <= bench_data && i < j)
			i++;
		
		// Change value
		int temp = sort_data[j];
		sort_data[j] = sort_data[i];
		sort_data[i] = temp;
	}
	sort_data[start_index] = sort_data[i];
	sort_data[i] = bench_data;

	quick_sort(start_index, i - 1);
	quick_sort(i + 1, end_index);

	return;
}

void Sort::count_sort() {
	// We need to know the
	int len_count_a =  len_data + 10;
	int *count_a = new int[len_count_a](); // NOTE: add () can init count_a 0

	for (int i = 0; i < len_data; ++i) {
		count_a[sort_data[i]]++;
	}
	std::cout << "The result of count sort: " << std::endl;
	for (int i = 0; i < len_count_a; ++i) {
		for (int j = 0; j < count_a[i]; ++j) {
			std::cout << i << " ";
		} 
	}
	std::cout << std::endl;
	delete [] count_a;
	return;
}

int main() {
	Sort my_sort(10);

	//my_sort.bubble_sort();

	// my_sort.quick_sort(0, 9);
	// std::cout << "The quick sort result: " << std::endl;
	// for (int i = 0; i < 10; ++i) {
	// 	std::cout << sort_data[i] << " ";
	// }
	// std::cout << std::endl;

	my_sort.count_sort();

	return 0;
}