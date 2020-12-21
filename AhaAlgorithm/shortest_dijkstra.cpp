/*
问题：求从一点出发到其他各个点的最短路径，这种问题有个专用名：单源最短路径。
思路：（1）解题思路，Dijkstra算法，在未排列的情况下，先排出起始点到各个点的距离，找出距离最短的点，
          然后看通过这个最短的点，能不能让其他点的距离也变短，这个操作有个专用名词叫松弛。
          就这样循环下去。
      （2）图的表示方式，这次用链接表来表示图，用数组表示链表结构，表示起来略显抽象。
           用五个数组u，v，w，first，next，表示从u[i]到v[i]的路径的权重为w[i]，first中存放的是顶点
           u[i]的第一个路径，next中存放的是first[u[i]]
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include "datas.hpp"

//using namespace std;

void dijkstra() {
    // m is the number of point, n is the number of route
    int points = 6, routes = 9;
    // get the distance from 0 to the others
    std::vector<int> distan(points, 99);
    std::vector<int> distan_res(points, -1);

    for (int i = 0; i < routes; ++i) {
        if (u[i] == 0) {
            distan.at(v[i])= w[i]; 
        }
    }
    
    int book[6]; // sizeof book equal to points
    for (int j = 0; j < points - 1; ++j){
        auto res_min = std::min_element(distan.begin(), distan.end());
        int min_value = *res_min;
        int min_index = std::distance(std::begin(distan), res_min);
        
        distan_res.at(min_index) = *res_min;
        
        // mark the ponit that have been min
        book[min_index] = 1;
        
        // compute the other points min value
        for (int i = 1; i < points; ++i) {
            if (book[i] == 1)
                continue;
            
            // 
            int k  = first[min_index];
            while (k != -1)
            {
                if (v[k] == i && w[k] + min_value < distan[i]) {
                    distan.at(i) = min_value + w[k];
                } 
                k = next[k];
            }
        }

        distan.at(min_index) = 99;
    }
    std::cout << "We get the result:" << std::endl;
    for (int i = 1; i < points; ++i) {
         std::cout << "From 0 to " << i << " is: " << distan_res.at(i) << std::endl;
    }
}

int main() {
    dijkstra();
}