/*
二分法，一种用于查找的方法，输入一个有序序列，从中间位置开始，判断跟要查找数据的关系，相等则得到结果，
	   若大于或小于，则在可能的一半数据中继续查找，仍然从另一半的中间位置继续查找，如此循环，直到找到
	   要找的元素。
注意：（1）输入序列必须是有序的，因为在后续的查找过程中，需要用到大小关系来确定继续查找的范围；
	  （2）当总元素个数为n，最坏情况下，二分法的之间复杂度为O(logN), 比如n=8，则最多需要三步就能找到；
*/
#include <iostream>
#include "datas.hpp"

class BinarySearch
{
private:
	int len_input;
public:
	BinarySearch(int in_len_input);
	~BinarySearch();

	int search(int * in_datas, int seach_data);
};

BinarySearch::BinarySearch(int in_len_input) : len_input(in_len_input){}

BinarySearch::~BinarySearch() {}

int BinarySearch::search(int * in_datas, int seach_data) {
	
	int start = 0;
	int end = len_input - 1;
	while (start < end)
	{
		int mid = start + (end - start + 1) / 2;
		if (seach_data == in_datas[mid]) {
			return mid;
		}
		if (seach_data > in_datas[mid]) {
			start = mid - 1; 	
		} else if (seach_data < in_datas[mid])
		{
			end = mid - 1;
		}
	}
	return -1;
	
}

int main() {
	BinarySearch my_search(5);
	int index = my_search.search(binary_data, 3);
	if (index)
	{
		std::cout << "The index of 3 in binary_data id : " << index << std::endl;
	}else
	{
		std::cout << "The 3 isn't in binary_data" << std::endl;
	}
	
	index = my_search.search(binary_data, -1);
	if (index > 0)
	{
		std::cout << "The index of -1 in binary_data id : " << index << std::endl;
	}else
	{
		std::cout << "The -1 isn't in binary_data" << std::endl;
	}
	
	return 0;
}
