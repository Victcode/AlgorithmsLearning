/*
问题：小A准备去城市旅游，先有这些城市的地图，有些城市之间有路连接有些没有，而且通路都是单向的，
     小A预算有限，需要提前知道两个城市间的最短路径，以便做好出行规划，省点路费。
分析：本次用floyd算法。本问题前提是两点之间不是直线最短，既然不是直线最短就可以引入第三个点作为中转，
    依次类推，也可以引入第四个点、第五个点……遍历这些情况，比较得出最短的点，就是floyd算法。
    用邻接矩阵的方法表示图。
    注意，该算法不适合权重有赋值的情况，有负值的时候，算法会一直过负值那条路，停不下来。
*/
#include <iostream>
#include "datas.hpp"

int main() {
    int m = 4, n = 4;
    // Floyd
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            for (int k = 0; k < n; ++k)
                if (map_floyd[i][j] > map_floyd[i][k] + map_floyd[k][j])
                    map_floyd[i][j] = map_floyd[i][k] + map_floyd[k][j];
        }
    }
    
    // 
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i != j)
                std::cout << "The shortest way from " << i << " to "
                << j << " is " << map_floyd[i][j] << std::endl;
        }
    }

    return 0;
}



