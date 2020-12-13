/*
问题：一个城市中的5个地点，组成一个带权重的有向图，地点编号从0到4，找出从0点到达4点的最短路线。
分析：这里主要联系对图的遍历操作，不探讨寻找最短路径的算法。
     用深度优先搜索遍历图，然后得出最短路径。
     这里使用邻接矩阵来表示图，定义在datas.h文件中。除了邻接矩阵还可以用连接表。
     临界矩阵是个二维数组，比如G[1][3] == 7，表示有从1到3的边，并且权重为7。
     为简单起见，用99表示无穷大，无穷大表示两个定点之间没有边，比如G[2][5] == 99，表示从2到5没有边。
*/
#include <iostream>
#include <vector>
#include "datas.hpp"

using namespace std;
int g_min_dist = 99;
int g_book[5];
std::vector<int> g_way;
void search_DFS(int current, int dist) {
    
    if (dist > g_min_dist)
        return;
    // check for arrival
    if (current == 4) {
        cout << "Reaching the destination!" << endl;
        int way_size = g_way.size();
        if (g_min_dist > dist) {
            g_min_dist = dist;
            cout << "Update the min distance: " << g_min_dist << endl;
            cout << "The route is:"<< endl;
            for (int i = 0; i < way_size; ++i) {
                cout << g_way[i] << " ";
            }
            cout << endl;
        } else {
            cout << "But not the min distance." << endl;
        }
        return;
    }
    
    // search routes
    for (int i = 0; i < 5; ++i) {
        if (graph_city[current][i] == 99 || g_book[i] == 1)
            continue;

        g_book[i] = 1;
        g_way.push_back(i);
        int curr_dist = graph_city[current][i] + dist;
        search_DFS(i, curr_dist);
        g_book[i] = 0;
        g_way.pop_back();
        
    }
    return;
}
int main() {
    int start_piont = 0;
    g_way.clear();
    g_book[0] = 1;
    g_way.push_back(0);
    search_DFS(0, 0);
    cout << "Search end" << endl;

    return 0;
}