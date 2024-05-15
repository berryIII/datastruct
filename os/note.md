## 进程同步
**软件实现(peterson)**
```c
int turn;
bool wanted[];

void p0() {
    /* 进入区 */
    wanted[0]=true;
    turn=1;
    while(turn=1&&wanted[0]);
    /* 临界区 */
    doSth();
    /* 退出区 */
    wanted[0]=false;
    /* 剩余区 */
}

void p1() {
    /* 进入区 */
    wanted[1]=true;
    turn=0;
    while(turn=0&&wanted[0]);
    /* 临界区 */
    doSth();
    /* 退出区 */
    wanted[1]=false;
    /* 剩余区 */
}
```

**硬件支持**
1. 关闭中断
2. 指令支持(原子)
```c
// 读出原来的值并将其更新为真，
// 因此只有当这个函数返回false表示独占成功
TestAndSet(bool *lock) {
    bool old=*lock;
    *lock=true;
    return old;
}

// 全局变量
lock=false; 

while(&lock); // 进入区
doSth(); // 临界区
lock=false; // 退出区
```

P/V操作
```c
void p(semaphore s){
    s-=1;
    if(s<0){
        block(s);
    }
}

void v(semphore s){
    s+=1;
    if(s<=0){
        wake(s);
    }
}
```

**经典同步问题**

互斥锁
```c
semaphore mutex=1;

void func(){
    p(s);
    // 临界区
    v(s);
}
```

生产者-消费者
```c
semaphor bufferCount=n;
semaphor itemCount=0;
semaphor mutex=1;
buffer[]; 

void producer(){
    while(true){
        p(space);
        p(mutex);
        add(buffer);
        v(mutex);
        v(itemCount);
    }
}

void consumer(){
    while(true){
        p(itemCount);
        p(mutex);
        remove(buffer);
        v(mutex);
        v(spaceCount);
    }
}
```

读者-写者
```c
semarphore mutex=1;
semarphore w=1;
int readCount=0;
shared;

void reader(){
    p(mutex);
    readCount+=1;
    if(readCount==1){
        p(w);
    }
    v(mutex);
    read(shared);
    p(mutex);
    readCount-=1;
    if(readCount==0){
        v(w);
    }
    v(mutex);
}

void writer(){
    p(w);
    write(shared);
    v(w);
}
```

哲学家进餐
理发师睡觉

## 死锁
在系统资源不足的情况下，两个或多个进程请求着彼此占用的资源而陷入阻塞，导致他们都不能继续执行，这种情况称为死锁。

**产生条件**
1. 互斥条件
2. 不可剥夺条件
3. 请求与保持条件
4. 循环等待条件

**解决办法**
1. 死锁预防
2. 死锁避免
3. 死锁检测与恢复

**死锁预防**<br>
通过破环死锁的产生条件达到预防系统陷入死锁。<br>
+ 互斥条件 通常并不现实，许多资源不能共享。
+ 不可剥夺条件 当进程新请求的资源不能满足，必须释放已申请全部资源，可能导致系统资源利用率和吞吐量降低，仅适合易于保存和恢复的资源，如寄存器和主存等。
+ 请求与保持条件 采用静态资源分配，直到进程申请完全部资源后才能运行，且后续不得申请，这种方式资源利用率低且不太可能。
+ 循环等待条件 给资源编号，每个进程只能编号顺序申请资源，不能申请比已申请的资源编号小的，进程一般很难保证，且资源序号需要固定。

资源给够：m个同类资源，假设n个进程，每个进程最大需求为x，则当`m-n(x-1)>=1`时，不会死锁。

**死锁避免**<br>
系统在某一时刻能按某种顺序，给进程分配资源直至其最大需求，使得每个进程都可以顺利完成运行，则称系统当前处于**安全状态**，这个分配序列称为**安全序列**。

死锁避免指不对进程使用资源增加条件限制，而是在其申请资源时检查如果分配其资源后进程是否处于安全状态，如果处于则分配资源，否则让进程等待。

**银行家算法**
```c
max[n][m] // n个进程，其所需的m种资源对应的最大值
available[m] // 当前可用的i资源的数量，初始值为资源数
need[n][m] // need[i][j]表示当前进程i还需资源j的数量，初始值和max相同
allocation[n][m] // 进程i已分配的资源j的树量，needed=max-allocation

// 进程i请求的资源数
request(i,request[m]){
    /* 检查请求是否满足条件 */
    for(j=0;j<m;j++){
        if(request[j]>need[i][j]){
            error("requested exceed max needed.")
        }
        if(request[j]<=available[j]){
            error("resource is insufficient now.")
        }
    }
    /* 尝试分配 */
    for(j=0;j<m;j++){
        allocation[i][j]+=request[j];
        need[i][j]-=request[j];
        available[j]-=request[j];
    }

    /* 安全性检查 */
    if(!isSafeNow()){
        error("won't be safe after this allocation.")
        rollback(); // 将尝试分配修改的状态改回去
    }
}

// 安全性检查，判断是否能够以某种顺序完成所有进程
ifSafeNow(){
    // available的一份局部拷贝，避免算法运行干扰全局变量
    workable[m]=available;
    bool finished[n];
    bool proceed=true;
    while(proceed){
        for(int i=0;i<n;i++){;
            proceed=true;
            if(!finished[i]){
                for(int j=0;j<m;j++){
                    if(need[i][j]>workable[j]){
                        proceed=false;
                    }
                }
                if(proceed){
                    for(int j=0;j<m;j++){
                        workable[i][j]+=allocation[i][j];
                    }
                    finished[i]=true;
                }
            }
        }
    }
    for(int i=0;i<n;i++){
        if(!finished[i]){
            return false;
        }
    }
    return true;
}
```

算法局限：
1. 进程需提前给出最大需要的资源数量，这往往不容易确定
2. 进程需要固定
3. 资源数固定，这意味着如果运行期间某个设备损坏算法将失效。
4. 算法开销大，与系统进程数成正比。

**死锁检测和解除**<br>
对资源分配图（一般用圆圈表示进程，方框表示资源，有向边表示a资源被b进程占用，或b进程等待a资源）进行检测，首先找出一个不阻塞也不孤立的进程点，将其所有的边删除，重复这个过程，如果最后剩下的点都是孤立点，则称图是可完全简化的。

死锁定理：系统状态S的资源分配图不可完全简化，则S为死锁状态。

解除方式
1. 剥夺其他进程资源给死锁进程，使其解除死锁。
2. 全部撤销或逐个撤销死锁进程，使系统能够解除死锁状态。




