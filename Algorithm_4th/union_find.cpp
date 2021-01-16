/*
问题：输入一系列的整数对，整数对中的两个元素相连（假设相连是一种等价关系，且满足自反性、等价性、传递性），
	  要求编写程序过滤掉输入序列中无意义的整数对，输出有意义的整数对的个数。
	  无意义整数对的意思是这两个数来自于同一个等价关系，举例，四个整数对{{1,2}, {2,3}, {3,1}, {5,4}}，
	  1和2相连，2和3相连，3和1相连，5和4相连。由
	  传递性可得，从前两个输入就可以得到1连3，因此第3个输入{3,1}就是无意义的整数对。
分析：按照书中的数序实现四种解决办法；
	 （1）quick-find
	 （2）quick-union
	 （3）带权重的quick-union
	 （4）带路径压缩的quick-union

NOTE： 代码未调试
*/
#include<iostream>
#include<string>
#include <fstream>
#include <cassert>
#include <vector>
#include <time.h>
#include <chrono>

using namespace std::chrono;

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
	int isConnecked(int a, int b, int (*find)(int)); // equal to "connected" in book
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

int UnionFind::isConnecked(int a, int b, int (*find)(int)) {
	return find(a) == find(b);
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

	// std::cout << "aID: " << aID << "bID " << bID << std::endl;
	// getchar();

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

void SplitString(const std::string& s, std::vector<std::string>& v, const std::string& c)
{
  std::string::size_type pos1, pos2;
  pos2 = s.find(c);
  pos1 = 0;
  while(std::string::npos != pos2)
  {
    v.push_back(s.substr(pos1, pos2-pos1));
 
    pos1 = pos2 + c.size();
    pos2 = s.find(c, pos1);
  }
  if(pos1 != s.length())
    v.push_back(s.substr(pos1));
}

int main() {
	int num_elements = 0;
	int len_datas = 0;
	int** datas;
	// read txt
	std::string file_path = "./datas/mediumUF.txt";
	std::ifstream infile;
    infile.open(file_path.data());
    assert(infile.is_open()); 

    std::string s_line;
	int num = 0;
	std::vector<std::string> split_lines;

    while(getline(infile, s_line))
    {	
		if (num == 0) {
			num_elements = stoi(s_line);
			num++;
		}
		split_lines.push_back(s_line);
		num++;
	}

	len_datas = split_lines.size();
	datas = new int* [len_datas - 1];
    for(int i = 1;i < len_datas; i++) {
		datas[i] = new int[2];
		std::vector<std::string> split_line;
		SplitString(split_lines[i], split_line, " ");
		datas[i][0] = stoi(split_line[0]);
		datas[i][1] = stoi(split_line[1]);
	}
    infile.close(); 

	UnionFind union_find(num_elements);

	// quick-find
	union_find.reset();
	auto clock_start = steady_clock::now();

	for (int i = 1; i < len_datas; ++i) {
		if(union_find.find_qf(datas[i][0]) == union_find.find_qf(datas[i][1]))
			continue;
		union_find.union_qf(datas[i][0], datas[i][1]);
	}

	auto clock_end = steady_clock::now();
	duration<long, std::micro> tiem_result = 
        	duration_cast<microseconds>(clock_end - clock_start);
	std::cout << "Quick-Find's result is : " << union_find.get_count() <<
	             " time: " << tiem_result.count() << 
			     "us" << std::endl;

	// quick-union
	union_find.reset();
	clock_start = steady_clock::now();

	for (int i = 1; i < len_datas; ++i) {
		if(union_find.find_qu(datas[i][0]) == union_find.find_qu(datas[i][1]))
			continue;
		union_find.union_qu(datas[i][0], datas[i][1]);
	}

	clock_end = steady_clock::now();
	tiem_result = 
        	duration_cast<microseconds>(clock_end - clock_start);
	std::cout << "Quick-Union's result is : " << union_find.get_count() <<
	             " time: " << tiem_result.count() << 
			     "us" << std::endl;

	//======== weighted quick-union =================
	union_find.reset();
	clock_start = steady_clock::now();

	for (int i = 1; i < len_datas; ++i) {
		if(union_find.find_wqu(datas[i][0]) == union_find.find_wqu(datas[i][1]))
			continue;
		union_find.union_wqu(datas[i][0], datas[i][1]);
	}

	clock_end = steady_clock::now();
	tiem_result = 
        	duration_cast<microseconds>(clock_end - clock_start);
	std::cout << "Weighted Quick-Union's result is : " << union_find.get_count() <<
	             " time: " << tiem_result.count() << 
			     "us" << std::endl;

	// path compression weighted quick-union
	union_find.reset();
	clock_start = steady_clock::now();
	for (int i = 1; i < len_datas; ++i) {
		if(union_find.find_pwqu(datas[i][0]) == union_find.find_pwqu(datas[i][1]))
			continue;
		union_find.union_pwqu(datas[i][0], datas[i][1]);
	}
	clock_end = steady_clock::now();
	tiem_result = 
        	duration_cast<microseconds>(clock_end - clock_start);
	std::cout << "Path Weighted Quick-Find's result is : " << union_find.get_count()<<
	             " time: " << tiem_result.count() << 
			     "us" << std::endl;

	// free datas
    for(int i = 1;i < len_datas;i++)
        delete [] datas[i];

	return 0;
}
