/*
问题：在一个群岛区域，小A随机落在一个小岛上，求小A当前所在小岛的面积。在一个二维数组中，海水用0表示，
     小岛土地用大于0的数值表示
思路：可以用深度优先遍历和广度优先遍历来遍历从起始点开始的非零点，然后标记所有点，统计点的个数，
     就可以得到岛的面积；
 */
#include <iostream>
#include <cstring>
#include "datas.hpp"

int g_next_step[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
int g_book[10][10];
static int g_count = 1;

// DFS, depth first search
void search_DFS(int width, int height, int *start) {
    for (int i = 0; i < 4; ++i) {
        int temp_x = start[0] + g_next_step[i][0];
        int temp_y = start[1] + g_next_step[i][1];

        // check the boundary condition and strip the sea
        if (temp_x <= 0 || temp_y <= 0 || temp_x > width || temp_y > height) {
            continue;
        }
        if (g_book[temp_x][temp_y] == 0 && map_island[temp_x][temp_y] > 0) {
            g_count++;
            g_book[temp_x][temp_y] = 1;
            int temp_point[2] = {temp_x, temp_y};
            search_DFS(width, height, temp_point);
        }
    }     
    return ;
}

// BFS, breath first search
void search_BFS(int width, int height, int *start_point) {
    struct node {
        int x;
        int y;
        int flag; // 1-checked, 0-no check
    };

    struct node search_nodes[100];
    int head = 0;
    int tail = 0;
    int temp_x, temp_y;
    // init the fist node
    search_nodes[head].x = start_point[0];
    search_nodes[head].y = start_point[1];
    search_nodes[head].flag = 1;

    tail++;
    
    while (head < tail) {
        for (int i = 0; i < 4; ++i) {
            temp_x = search_nodes[head].x + g_next_step[i][0];
            temp_y = search_nodes[head].y + g_next_step[i][1];

            // for check the boundary conditions
            if (temp_x <= 0 || temp_x > width || temp_y <= 0 || temp_y > height) {
                continue;
            }
            // check if the point is shecked before
            if (map_island[temp_x][temp_y] > 0 && g_book[temp_x][temp_y] == 0) {
                g_count++;
                search_nodes[tail].x = temp_x;
                search_nodes[tail].y = temp_y;
                g_book[temp_x][temp_y] = 1;
                tail++;
            }
        }
        head++;
    }

}

int main() {
    int width = 10;
    int height = 10;

    int start_point[2] = {6, 8};
    g_book[start_point[0]][start_point[1]] = 1;
    search_DFS(width, height, start_point);
    std::cout << "DFS get the area of island: " << g_count << std::endl;

    g_count = 1; // count start_point
    memset(g_book, 0, sizeof(int) * 10 * 10); // memset is declared in cstring
    g_book[start_point[0]][start_point[1]] = 1;
    search_BFS(width, height, start_point);
    std::cout << "BFS get the area of island: " << g_count << std::endl;  

    return 0;
}

