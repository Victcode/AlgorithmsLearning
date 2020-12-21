#ifndef DATAS_H
#define DATAS_H
int map_island[10][10] = {{1, 2, 1, 0, 0, 0, 0, 0, 2, 3},
                          {3, 0, 2, 0, 1, 2, 1, 0, 1, 2},
                          {4, 0, 1, 0, 1, 2, 3, 2, 0, 1},
                          {3, 2, 0, 0, 0, 1, 2, 4, 0, 0},
                          {0, 0, 0, 0, 0, 0, 1, 5, 3, 0},
                          {0, 1, 2, 1, 0, 1, 5, 4, 3, 0},
                          {0, 1, 2, 3, 1, 3, 6, 2, 1, 0},
                          {0, 0, 3, 4, 8, 9, 7, 5, 0, 0},
                          {0, 0, 0, 3, 7, 8, 6, 0, 1, 2},
                          {0, 0, 0, 0, 0, 0, 0, 0, 1, 0}}; 

int map_pipe[5][4] = {{5, 3, 5 ,3},
                       {1, 5, 3, 0},
                       {2, 3, 5, 1},
                       {6, 1, 1, 5},
                       {1, 5, 5, 4}};

int graph_city[5][5] = {{0 , 2 , 99, 99, 10},
                        {99, 0 , 3 , 99, 7 },
                        {4 , 99, 0 , 4 , 99},
                        {99, 99, 99, 0 , 5 },
                        {99, 99, 3 , 99, 0 }};

int graph_city2[5][5] = {{0 , 1 , 1 , 99, 99},
                         {1 , 0 , 1 , 1 , 99},
                         {1 , 1 , 0 , 1 , 1 },
                         {99, 1 , 1 , 0 , 1 },
                         {99, 99, 1 , 1 , 0 }};
                         
int map_floyd[4][4] = {{0 , 2 , 6 , 4 },
                       {99, 0 , 3 , 99},
                       {7 , 99, 0 , 1 },
                       {5 , 99, 12, 0 }};

// data for dijkstra, 6 points and 9 routes
// the order of the sides is from back to front
int u[9] = {0, 0 , 1, 1, 2, 3, 3 , 3 , 4};  
int v[9] = {1, 2 , 2, 3, 4, 2, 4 , 5 , 5};
int w[9] = {1, 12, 9, 3, 5, 4, 13, 15, 4};
// first[u[i]] means the number of u[i]'s first route
int first[6] = {1, 3, 4, 7, 8, -1};
// next[i] means the number of i-route's next route
// when the i-route only one route, the value is -1
int next[9] = {-1, 0, -1, 2, -1, -1, 5, 6, -1};

// Data for bellman, 5 points and 5 routes
int u_be[5] = {1, 0, 0, 3, 2};
int v_be[5] = {2, 1, 4, 4, 3};
int w_be[5] = {2, -3, 5, 2, 3};


#endif