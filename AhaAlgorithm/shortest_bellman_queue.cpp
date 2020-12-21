/*
问题：Bellman算法的时间复杂度是O(mn)，怎么提升下算法运行效率。
分析：（1）算法遍历所有的顶点和所有的边，但是某些顶点的已经是最短路径了，没有必要再继续遍历。
        已经是最短路径的点在当前轮中就不会再继续被松弛，因此在上一轮被松弛过的点在这一轮会有可能被松弛，
        在上一轮没有被松弛的点在这一轮不做处理。
     （2）有队列来实现上述想法。从起始点开始，此时起点作为队列的队首。进行第一轮松弛，将被松弛的点按顺序
        放到队尾，队首出列。继续以新的队首为起点进行松弛，重复上述操作。
      (3)要注意的是，已经出对的顶点还有可能从新进队，因为再其他顶点的松弛过程中该顶点的最短路径可能会
         继续变小。
     （4）使用队列的情况下，算法最坏的时间复杂度仍是O(mn).
     （5）同样能检查图中是否含有负权值回路，如果某个顶点进入队列的次数超过num_point，就说明存在；
*/
#include <iostream>
#include <queue>
#include "datas.hpp"

class QBellman
{
private:
    int num_point;
    int num_route;
    int distan[5];
    int book[5];
    std::queue<int> relax_points;
    
public:
    QBellman(int in_num_point, int in_num_route);
    ~QBellman();

    void get_distance();
    void get_result();
};

QBellman::QBellman(int in_num_point, int in_num_route):
                num_point(in_num_point), num_route(in_num_route) {}

QBellman::~QBellman() {}

void QBellman::get_distance() {
    distan[0] = 0;
    for (int r = 0; r < num_route; ++r) {
        distan[v_be[r]] = u_be[r] == 0 ? w_be[r] : 99;
    }
}

void QBellman::get_result() {
    relax_points.push(0);
    book[0] = 1;
    while (!relax_points.empty()) {
        for (int r = 0; r < num_route; ++r) {
            if (distan[v_be[r]] > distan[u_be[r]] + w_be[r]) {
                if (book[v_be[r] == 0])
                    relax_points.push(v_be[r]);
                distan[v_be[r]] = distan[u_be[r]] + w_be[r];
            }
        }
        book[relax_points.front()] = 0;
        relax_points.pop();
    }

    std::cout << "Get the result (using queue): " << std::endl;
    for (int i = 1; i < num_point; ++i) {
        std::cout << "From 0 to " << i << " is: " << distan[i] << std::endl;
    }
}

int main() {

    QBellman bellman(5, 5);
    bellman.get_distance();
    bellman.get_result();

    return 0;

}