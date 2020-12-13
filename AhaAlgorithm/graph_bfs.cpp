/*
问题：现有5个城市，标记从0到4，小A要从城市0坐飞机到城市4，没有直达，已知各个城市之间的分型路线，问小A应该
      怎么飞才能转机次数最少。
分析：使用宽度优先遍历，当然深度优先遍历也一样有用，这里就是联系广度优先遍历图的方法。
     有一点也要注意，这个问题中的地图是个不带权重的无向图，当不带权重的时候，使用广度优先遍历要更有效，
     具体原因不明。
*/
#include <iostream>
#include <vector>
#include <list>
#include "datas.hpp"

using namespace std;

//std::list<int> my_route;
struct node
{
    int x;
    int father;
    int dist;
};

struct node g_route[25];
int g_book[5];

void search_BFS(int current) {

    // current == 0
    int head = 0;
    int tail = 1;
    g_route[head].x = current;
    g_route[head].dist = 0;

    g_book[head] = 1;
    int dist = 0, flag = 0;
    while (head < tail) {
        for (int i = 0; i < 5; ++i) {

            if (g_book[i] != 1 && graph_city2[g_route[head].x][i] == 1) {
                if (i == 4) {
                    flag = 1;
                    break;
                }
                g_route[tail].x = i;
                g_route[tail].father = head;
                g_route[tail].dist = 1 + g_route[g_route[tail].father].dist;
                tail++;
                g_book[i] = 1;
            }   
        }
   
        if (flag) {
            cout << "We arrive the destination! distance: " << g_route[tail - 1].dist << endl;
            cout << "The route is: " << endl;
            int father = tail - 1;
            for (int j = 0; j <= g_route[tail - 1].dist; ++j) {
                cout << g_route[father].x << " ";
                father = g_route[father].father;
            }
            return;
        }
        head++;
    }
}

int main() {
    search_BFS(0);
    return 1;
}