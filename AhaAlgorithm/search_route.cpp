/*
问题：小A迷路了，小B要去寻找小A。现在已知整张地图坐标、其中障碍物的位置、小A的位置，
     小B从起点出发去找小A，求取最短路径；
思路：先找出所有可能路径，然后得出最短步数。
     查找所有路径使用两种算法分别来实现：
     （1）深度优先遍历，首先以一个未被访问过的顶点为起始顶点，然后走到下一个未被访问过的顶点，
          当走到某个顶点没有相连的未被访问的顶点时，则返回上一个顶点，继续遍历其他未被访问过的顶点。
     （2）广度优先遍历，以一个未被访问过的顶点为起始顶点，访问与其相邻的所有顶点，然后再访问相邻点的
          未被访问过的所有相邻点，直到访问完所有顶点。
做法：小B从头起点开始找，从起点开始遍历所有可能路线，具体方法是找出当前点所有可能的走向，
     此时的限制条件下个点不能是障碍物或者地图之外，比如可以向前、向下，此时就出现了两种情况，
     两种情况都要遍历到，先向前走一步，然后判断一下是否已经走到了小A的位置，如果没有，
     则沿用上述规则，寻找当前点所有可能的路线。
*/
#include "stdio.h"
#include "iostream"

using namespace std;

int map[51][51];  // store the map coordinates,input by user
int obstacle[51][51];  // store the obstacle coordinates, generate by random
int width = 20; // the width of map
int height = 20; // the height of map
int min_step = 10000; // set a large number
//DFS, Depth Fist Search
void search_DFS(int *A, int *B, int &step){
    int next[4][2] = {{0,1}, {1,0}, {0,-1}, {-1,0}};  //direction，right、front、left、down
    //check to see if have reached the destination
    if (A[0] == B[0] && A[1] == B[1]){
        if (step < min_step) {
            min_step = step;
        }
        return;
    }
    
    // search the routes by DFS
    for (int next_idx = 0; next_idx < 4; next_idx++) {
        
        B[0] += next[next_idx][0];
        B[1] += next[next_idx][1];
        // check the boundary conditions
        if (B[0] < 0 || B[1] < 0 ||  B[0] > width || B[1] > height)
            continue;
        if (map[B[0]][B[1]] == 0 && obstacle[B[0]][B[1]] == 0) {
            map[B[0]][B[1]] = 1;
            int next_step = step + 1;
            search_DFS(A, B, next_step); // recursion
            map[B[0]][B[1]] = 0;
        }

    }
    return;
}

//BFS，Breath first search
void search_BFS(int *A, int *B, int &step) {
    //use queue to store the route
    struct node{
        int x;
        int y;
        int father;
        int step;
    };

    struct node my_routes[2500];
    
    int next[4][2] = {{0,1}, {1,0}, {0,-1}, {-1,0}};  //direction，right、front、left、down
    int temp_x = 0, temp_y = 0;
    int flag = 0;
    // init my_route
    int head = 0;
    int tail = 0;
    my_routes[head].x = B[0];
    my_routes[head].y = B[1];
    my_routes[head].step = step;
    my_routes[head].father = 0;
    
    // get next step
    tail++;
    while (head < tail)
    {
        // check four directions
        for (int i = 0; i < 4; ++i){
            // check to see if have reached the destination
            if (A[0] == my_routes[head].x && 
                A[1] == my_routes[head].y){
                flag = 1;
                if (my_routes[head].step < min_step)
                    min_step = my_routes[head].step;
                continue;
            }
            // get the next coordinates
            temp_x = my_routes[head].x + next[i][0];
            temp_y = my_routes[head].y + next[i][1];

            // check the boundary conditons
            if (temp_x < 0 || temp_y < 0 || temp_x > width || temp_y > height) {
                continue;
            }

            if (map[temp_x][temp_y] == 0 && obstacle[temp_x][temp_y] == 0) {
                my_routes[tail].x =  temp_x;
                my_routes[tail].y = temp_y;
                my_routes[tail].father = head;
                my_routes[tail].step = my_routes[head].step + 1;
                // move the tail
                tail++; 
                map[temp_x][temp_y] = 1;
            }
        }
        //if (flag == 1) break;
        head++;
    }

}

int main() {
    int A[2];
    int B[2];
    int step = 0;
    cout << "Set map width and height ( < 50):" << endl;
    scanf("%d %d", &width, &height);
    cout << "Set point of A: " << endl;
    scanf("%d %d", &A[0], &A[1]);
    cout << "Set point of B: " << endl;
    scanf("%d %d", &B[0], &B[1]);

    // Init the obstacle
    for (int w = 0; w < width / 2; ++w){
        for (int h = 0; h < height / 2; ++h){
            int rand_w = rand() % width;
            int rand_h = rand() % height;
            obstacle[rand_w][rand_h] = 1;
        }
    }
    
    search_DFS(A, B, step);
    cout << "DFS gets the min step: " << min_step << endl;

    min_step = 10000;
    search_BFS(A, B, step);
    cout << "BFS gets the min step: " << min_step << endl;

    return 0;
}


