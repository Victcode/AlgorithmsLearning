/*
问题：当图中有负权路的时候，dijkstra算法会然绕着权重为负的路径转圈。那对于这种有负权值的路径该怎么办
分析：（1）bellman算法解决了负权路的问题。跟dijkstra相比，两中算法思想有相似的地方，不同的是bellman是对
     点和路径进行松弛操作。
     （2）算法最多的遍历次数是((num_point-1) x num_route)，这是最坏的情况，在循环的过程中，distan数组可能已经
     不更新了，此时已经得到了最终结果，算法可以退出。
     （3）该算法可以判断图中是否存在负权路，在完成循环遍历之后，再加一次循序，如果distan数组中的数据还在改变，
     则说明在整个图中存在负权路。
*/
#include <iostream>
#include "datas.hpp"

class Bellman
{
private:
    int num_point;
    int num_route;
    int distan[5];

public:
    Bellman(int in_num_point, int in_num_route);
    ~Bellman();

    void get_distance();
    void get_result();
};

Bellman::Bellman(int in_num_point, int in_num_route)
                : num_point(in_num_point), num_route(in_num_route) {}

Bellman::~Bellman(){}

void Bellman::get_distance() {
    distan[0] = 99;
    for (int r = 0; r < num_route; ++r) {
        distan[v_be[r]] = u_be[r] == 0 ? w_be[r] : 99;
    }
}

void Bellman::get_result() {

    // Using Bellman to get the 'distan' of shortest
    for (int p = 0; p < num_point - 1; ++p) {
        
        int check = 0; // Check if diatan dont update
        for (int r = 0; r < num_route; ++r) {
            if (distan[v_be[r]] > distan[u_be[r]] + w_be[r]) {
                check = 1;
                distan[v_be[r]] = distan[u_be[r]] + w_be[r];
            }
        }
        if (!check) {
            std::cout << "Get the result earlier !" << std::endl;
            break;
        }
    }

    // for checking negative loops
    int neg_check = 0; 
    for (int r = 0; r < num_route; ++r) {
        if (distan[v_be[r]] > distan[u_be[r]] + w_be[r]) {
            neg_check = 1;
            break;
        }
    }
    if (neg_check)
        std::cout << "Negative path in the graph." << std::endl;

    std::cout << "Get the result: " << std::endl;
    for (int i = 1; i < num_point; ++i) {
        std::cout << "From 0 to " << i << " is: " << distan[i] << std::endl;
    }
}

int main() {

    Bellman bellman(5, 5);
    bellman.get_distance();
    bellman.get_result();

    return 0;
}
