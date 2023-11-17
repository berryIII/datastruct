## 概念
1. 简单图，无环无重边。
2. 度，结点的边数，有向图中度=出度+入度。
3. 完全图与有向完全图，边数达到最大值，即n(n-1)/2与n(n-1)
4. 稀疏图和稠密图，边数较少或较多。
5. 加权图（网），边带有附加信息，包括无向加权图和有向加权图。
6. 若无向图中任意两点都是可达的（有路径），则称该无向图是连通图，若是有向图，则称其为强连通图。 
7. 无向图中的极大连通子图为连通分量，若无向图是连通的，则连通分量只有一个。有向图的连通分量叫强连通分量，有多个。连通分量总和的结点数为n，不多不少。
8. 生成树，连通图（无向连通）的一个极小连通子图（包含n个节点），该子图一定仅具有n-1条边（反之未必），生成树可以有多个。
9. 对无向图而言，n个结点的图若边数少于n-1，则必非连通，若超过n-1个，则必有回路。

##
```
         C— - — D
        / \    /
       /   \  /
      A — - B
```
```
         C
        / \    
       /   \  
      A ——>  B
      \_
       \
        \
         D
```

## 存储
1.邻接矩阵存储
|-|0|1|2|3|
|-|-|-|-|-|
|0|0|1|1|0|
|1|1|0|1|1|
|2|1|1|0|1|
|3|0|1|1|0|

特点
1. 无向图存储是对称矩阵
2. 空间复杂度o(n^2)
3. 可以很快判断两点间是否有边
4. 稀疏图时浪费存储
5. 计算总边数需要遍历矩阵。

2.邻接表
i|-|-|
-|-|-|
0|A|->B->C|
1|B|->A->C->D|
2|C|->A->B->D|
3|D|->B->C|

特点
1. 空间复杂度o(n+e)，n为结点数，e为边数
2. 无向图时有重复存储
3. 判断两点是否有边需要遍历链表
4. 存储结构不唯一。

## 遍历
深度优先
```c
dfs(node[n],visited[n],start){
    visit(node[start]);
    visited[start]=1;
    for(j in node[start].neighbors){
        if(visited[j]!=1){
            dfs(node,visited,j);
        }
    }
}
```
空间复杂度O(n)，时间复杂度O(n^2)或O(n+e)

广度优先
```c
bfs(node[n],visited[n],start){
    queue q;
    inqueue(q,start);
    while(nonEmpty(q)){
        cur=dequeue(q);
        visit(node[cur]);
        visited[cur]=1;
        for(j in node[cur].neighbors){
            if(visited[j]!=1){
                inqueue(q,j);
            }
        }
    }
}
```
复杂度与深度优先相同。

## 连通分量
检测无向图是否连通，或计算有多少个连通分量，使用dfs/bfs进行x次搜索，将全部结点访问一遍，则x个连通分量。

对于有向图而言，若要判断是否连通，无法像无向图那样进行一次dfs/bfs，根据是否访问全部结点判断（不同的起点结果可能不同）。
一个直观的办法是对从每个结点开始搜索一次，这种情况最坏时间复杂度为o(n*(n+e))。

## 环检测
对无向图而言，可以从起点遍历看是否能回到该点，dfs/bfs均可。

拓扑排序<br>
从入度为0的点开始访问，访问后更新该邻接点的入度信息，重复这个过程，直到访问完所有结点，或者有环。时间复杂度O(n+e)。
```c
topologicalSort(node[n]){
    // 统计各结点入度数
    int indegree[n];
    for(i=0;i<n;i++){
        indegree[i]=0;
    }
    for(i=0;i<n;i++){
        for(j in node[i].neighbors){
            indegree[j]+=1;
        }
    }

    // 使用队列顺序访问所有入度为0的结点
    queue q;
    for(i=0;i<n;i++){
        if(indegree[i]==0){
            inqueue(q,i);
        }
    }
    int visited=0;
    while(nonEmpty(q)){
        cur=dequeue(q);
        visit(cur);
        visited+=1;
        for(j in node[cur].neighbors){
            indegree[j]-=1;
            if(indegree[j]==0){
                inqueue(q,j);
            }
        }
    }
    if(visited!=n){
        print("cycle exits.")
    }
}
```

## 最小生成树
prim算法

## 最短路径

## 带权图（网）


