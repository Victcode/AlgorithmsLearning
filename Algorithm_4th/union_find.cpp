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

*/
#include "union_find.hpp"

using namespace std::chrono;

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
		if(union_find.isConnecked(datas[i][0], datas[i][1], UnionFind::find_pwqu))
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
		if(union_find.isConnecked(datas[i][0], datas[i][1], UnionFind::find_qu))
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
		if(union_find.isConnecked(datas[i][0], datas[i][1], UnionFind::find_wqu))
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
		if(union_find.isConnecked(datas[i][0], datas[i][1], UnionFind::find_pwqu))
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

