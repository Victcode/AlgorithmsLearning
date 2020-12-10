/*
问题：一个摆放水管的游戏，语言太容易描述，具体可参照书中内容，书中插图更直观一些。
     这里简述一下，有一块土地被分成mxn个正方形，每个正方形中埋有一块水管，利用这些水管组合出一条通路，
     让水能从起点（0,0）一直流到（m-1，n-1），并输出这条通路。水管的类型一共有两种，直的和弯的。
思路：(1)使用深度优先遍历，从（1,1）开始到（m-1，n）结束，注意这里的纵坐标要超出边界，才算是流到了终点。
     (2)深度优先遍历是要遍历当前节点所有可能的方案。这里的重点是要分析走到每个节点的时候可能遇到的情况，
        然后捋清楚这些情况。这里的管道一共分为6中，其中弯的管道有4种，直的有2种。在地图中用1-6表示在当前
        方块中管道的类型，其中有个方块上有个障碍物，需要绕开，用0表示。
     (3)用栈来记录具体路线；
     (4)这里的关键是要弄清楚在每个节点处怎么寻找接下来要的方向。根据入水口的方位决定当前节点处要用的管道
        类型，然后用根据当前节点的管道类型决定下个节点的入水口方向。这也决定了saerch_pipe函数的参数。
     (5)管道的具体情况还是有图更容易看，具体参看书中内容。
*/
#include <iostream>
#include "datas.hpp"

using namespace std;

// set gloabal variables
// the map_pipe is defined in datas.hpp.
// m = 5, n = 4
int g_book[5][4];
// create a stack
struct node{
    int x;
    int y;
};
int g_top = 0;
struct node lines[21];

void search_line(int x, int y, int inflow) {
    int m = 5, n = 4;    
    // arrive the end 
    if (x == m - 1 && y == n) {
        cout << "The line is : " << endl;
        for (int i = 0; i < g_top; ++i) {
            cout << "(" << lines[i].x << ", " << lines[i].y << ") ";
        }
        cout << endl;
        return;
    }

    if (x < 0 || x > m - 1 || y < 0 || y > n - 1) {

        return;
    }
    
    if (g_book[x][y] > 0) {
        return;
    }
    
    g_book[x][y] = 1;
    lines[g_top].x = x;
    lines[g_top].y = y;
    g_top++;
    int next_pipe_type = map_pipe[x][y];
    // for 4 directions, 1:left, 2:top, 3:right, 4:bottom
    switch (inflow)
    {
    case 1:
        if (next_pipe_type < 5 && next_pipe_type > 0) {
            search_line(x + 1, y, 2); // pipe_type == 3
            search_line(x - 1, y, 4); // pipe_type == 4 
        }
        if (next_pipe_type > 4 && next_pipe_type < 7) {
            search_line(x, y + 1, 1); // pipe_type == 5
        }
        break;
    case 2:
        if (next_pipe_type < 5 && next_pipe_type > 0) {
            search_line(x, y + 1, 1); // pipe_type == 1
            search_line(x, y - 1, 3); // pipe_type == 4
        }
        if (next_pipe_type > 4 && next_pipe_type < 7) {
            search_line(x + 1, y, 2); // pipe_type == 6
        }
        break;
    case 3:
        if (next_pipe_type < 5 && next_pipe_type > 0) {
            search_line(x - 1, y, 4); // pipe_type == 1
            search_line(x + 1, y, 2); // pipe_type == 2
        }
        if (next_pipe_type > 4 && next_pipe_type < 7) {
            search_line(x, y - 1, 3); // pipe_type == 5
        }
        break;
    case 4:
        if (next_pipe_type < 5 && next_pipe_type > 0) {
            search_line(x, y + 1, 2); // pipe_type == 2
            search_line(x, y - 1, 3); // pipe_type == 3
        }
        if (next_pipe_type > 4 && next_pipe_type < 7) {
            search_line(x + 1, y, 4); // pipe_type == 5
        }
        break;
    }  

    g_book[x][y] = 0;
    g_top--;
}

int main() {
    int start_point[2] = {0, 0};
    cout << "start search !" << endl;
    search_line(0, 0, 1);
    cout << "end search !" << endl;
    return 0;
}







