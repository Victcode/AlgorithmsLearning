/*
树，不包含回路的连通无向图。树的特性：
（1）一个树中的任意两个节点之间有且只有一条通路；
（2）一棵树如果有n个节点，那么它一定恰好有n-1条边；
（3）在一棵树中加一条边将会构成一个回路；

二叉树，每个节点最多有两个子节点。
二叉树的表示：可以用一个数组来表示，通过数组中元素的下标来确定父子节点关系，数组和树的关系如下：
      （1）比如下标为k的点，他的左子节点为2k，右子节点为2k+1，他的父节点为(int)(k/2)。
      （2）数组大小为n，则最后一个非叶子节点的索引值是（n/2）。
      （3）当k*2 > n，可以判断k为一个叶子节点。

问题：堆是二叉树的一种应用，通过最大堆和最小堆可以实现排序，也就是堆排序，时间复杂度是O(Nlog(N)).
分析：（1）最大堆定义：根节点比子节点大；
          最小堆定义：根节点比子节点小；
     （2）建堆，建堆有两种方式，一种是向上调整，一种是向下调整。
          向上调整法构建一个堆的时间复杂度是O(Nlog(N))
          向下调整法构建一个堆的时间复杂度是O(N).
     （2）排序过程，例如从大到小排序，使用最小堆。排序步骤如下：
          a.设置一个数组sort_result存放排序的结果，先讲最小堆数组中min_heap的第一元素赋值给sort_result
          b.将min_heap中的最后一个元素赋值给第一个元素，即min_heap[0] = min_heap[n - 1]，n为数组长度
          c.数组元素大小减1，n--
          d.重复上述三个步骤
*/
#include <iostream>
#include "datas.hpp"

class TreeHeap
{
private:
     int num_node;
     int *min_heap = nullptr;

     void sift_down(int in_node, int * min_heap);
     void sift_up(int in_node, int * min_heap);

public:
     TreeHeap(int in_node);
     ~TreeHeap();

     void create_min_heap();
     void heap_sort();
};

TreeHeap::TreeHeap(int in_num) : num_node(in_num) {
     min_heap = new int[num_node];
}
     
TreeHeap::~TreeHeap() {
     delete(min_heap);
}

void TreeHeap::sift_up(int in_node, int * min_heap) {
     if (in_node == 0)
          return;

     // Check the father of the in_node until it reaches the root
     while (in_node != 0)
     {
          if (min_heap[in_node] < min_heap[in_node / 2]) {
              std::swap(min_heap[in_node], min_heap[in_node / 2]);
              in_node = in_node / 2;
          }else {
               break;
          }
     }
     
     return;
}

void TreeHeap::sift_down(int in_node, int * min_heap) {
     // 1. Check if the in_node is a leaf
     if (in_node * 2 > num_node)
          return;

     int flag = 0;
     int orig_node = in_node;
     while (in_node * 2 < num_node)
     {
          flag = 0;
          // 2. Check its left sun
          if (min_heap[in_node] > min_heap[in_node * 2 + 1]) {
               flag++;
          }
          // 3.Check its right sun
          if (in_node * 2 + 2 < num_node && // Check if in_node have right sun
                   min_heap[in_node] > min_heap[in_node * 2 + 2]) {
               flag++;
          }
          
          // 4. Check if the in_node changed
          // note: pick the smaller one in two sun nodes
          if (flag) {
               int temp_node = min_heap[in_node * 2 + 1] < min_heap[in_node * 2 + 2]
                                   ? in_node * 2 + 1 : in_node * 2 + 2;
               std::swap(min_heap[in_node], min_heap[temp_node]);
               in_node = temp_node;

               continue;
          } else{
               // No changing means in_node is the min node
               break;
          }
     }
     return;
}

void TreeHeap::create_min_heap() {
     // use orig_data in datas.hpp
     // There are two implitaton for create a min heap

     // Using sift_up
     // for (int i = 0; i < num_node; ++i) {
     //      min_heap[i] = orig_data[i];
     //      sift_up(i, min_heap);
     // }

     // Using sift_dowm
     memcpy(min_heap, orig_data, num_node * sizeof(int));
     for (int i = num_node / 2; i >= 0; --i) {
          sift_down(i, min_heap);
     }

     // Print the min_heap data for debug. 
     // for (int i = 0; i < num_node; ++i) {
     //      std::cout << min_heap[i] << std::endl;
     // }
}

void TreeHeap::heap_sort() {
     int *sort_result = new int[num_node];

     // Heap sort
     int orig_num_node = num_node;
     for (int i = 0; i < orig_num_node; ++i) {
          sort_result[i] = min_heap[0];
          min_heap[0] = min_heap[num_node - 1];
          num_node--;
          sift_down(0, min_heap);
     }

     // Print the sort result
     std::cout << "Heap sort result : " ;
     for (int i = 0; i < orig_num_node; i++) {
          std::cout << sort_result[i] << " "; 
     }
     std::cout << std::endl;
     
     return;
}

int main() {
     TreeHeap my_heap(14);
     my_heap.create_min_heap();
     my_heap.heap_sort();
     return 0;
}