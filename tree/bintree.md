## 概念
二叉树的度：所有结点的出度的最大值（树形结构入度出根结点外都为1）。
结点的度：一般指结点的出度，子结点个数。

性质<br>
1.度数+1=结点数。<br>
2.根据前/后/层序+中序可以确定恢复唯一的二叉树，根据前序+后序无法确定。<br>

满二叉树
```
             1
            /  \
           2    3 
          / \   / \
         4   5  6  7       
```
性质<br>
1.只有最后一层有叶结点<br>
2.n1=0 （不存在出度为1度结点）。<br>
3.从1开始索引，左子树为2i，右子树为2i+1，父结点为[i/2]。<br>


完全二叉树
```
               1
             /   \
            /     \
           2       3 
          /\       /\
         /  \     /  \
        4    5   6    7          
       /\   /\
      7  8 9 10
```
性质<br>
1.叶结点只在最后两层<br>
2.n1<=1<br>
3.索引特性同满二叉树<br>

[线索二叉树](https://blog.csdn.net/m0_68287216/article/details/127919045)<br>
根据遍历顺序将其空闲的左右指针设置前驱或后继结点的指针。
```c
typedef struct Node{
    ElemType data;
    struct Node* left;
    struct Node* right;
    int ltag; // 1表示left指向前躯
    int rtag; // 1表示right指向后继
}BTNode,*BTREE;
```
不同遍历顺序构造线索二叉树和使用对其的遍历方式不同
以中序为例，线索化后的遍历方式为（中序后序方式略不同）
```c
// 初始和线索中断后寻找当前子树的右子树的最左结点
void inOrder(BTREE root){
  BTREE cur=first(root);
  while(cur!=NULL){
    visit(cur);
    if(cur->rtag==1){
      cur=cur->right;
    }else{
      cur=first(cur->right);
    }
  }
}

// 寻找root的最左结点，即遍历顺序中的第一个结点
BTREE first(BTREE root){
  BTREE cur=root;
  while(cur!=NULL&&root->ltag==0){
    cur=cur->left;
  }
  return cur;
}
```

哈夫曼树<br>
用于编码压缩的二叉树，左边编码0，右边编码1。
哈夫曼树没有度为1的点，n=2*n0-1.
WPL（带权路径长度）最小的二叉树称为最优二叉树或哈夫曼树。

构造过程<br>
初始时所有结点各成一个树，这些树的权值为对应结点的权值，每次选两个权值最小的组成一颗树，新树的权值为两树之后，不断重复直到得到最终的树。

平均wpl<br>
sum(路径长度*权值)

## 计算等式
结点数计算，n为结点数,n0,n1,n2分别为出度为0，1，2的结点数
1. n=n0+n1+n2 
2. n=n1+2*n2+1 (节点数=入/出度数+1)
3. n0=n2+1 （n0+n2为奇数）
3. h层满二叉树结点数=2^h-1,m叉树=(m^h-1)/(m-1)
4. 第i层（0开始）最大结点数 2^i
5. 满/完全二叉树高度 log2(n+1)，n个m叉树的高度为[n,logm(n+1)]
6. 对完全二叉树，由于n1=0或1，若n=2k，则n1=1,n0=k，若n=2k-1,则n1=0,n0=k