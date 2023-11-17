/**
 * 使用顺序存储实现的线性表，包括顺序表，支持动态扩容
 */
// 线性表，逻辑结构，可以使用顺序存储结构和链式存储结构实现

// ======== 顺序存储 ========
# include <stdio.h>
# include <stdlib.h>
# include <assert.h>

typedef int ElemType;
typedef struct SeqList {
    int length;
    int capacity;
    ElemType* data; 
}SeqList;

// 初始化顺序表，初始容量为n
SeqList* init(int n) {
    SeqList* l= (SeqList*) malloc(sizeof(SeqList));
    l->length=0;
    l->capacity=n;
    l->data=(ElemType*) malloc((l->capacity)*sizeof(ElemType));
    return l;
}

// TODO 释放顺序表
int destroy(SeqList* l){
    return 0;
}

int resize(SeqList* l) {
    // TODO 释放旧空间，申请新空间
    return 0;
}


// 未找到返回-1，否则返回元素的索引
int find(SeqList* l, ElemType e) {
    int res=-1;
    for(int i=0;i<l->length;i++){
        if(l->data[i]==e){
            res=i;
        }
    }
    return res;
}

// 在第i个位置插入元素，i为[0,n]，失败返回-1，成功返回下标
int insert(SeqList* l,int i,ElemType e) {
    if(i<0||i>l->length){
        return -1;
    }
    for(int j=l->length;j>i;j--){
        l->data[j]=l->data[j-1];
    }
    l->data[i]=e;
    l->length+=1;
    return i;
}

// 更新第i个位置的元素
int update(SeqList* l,int i,ElemType e) {
    if(i<0||i>=l->length){
        return -1;
    }
    l->data[i]=e;
    return 0;
}

// 删除第i个位置的元素
int delete(SeqList* l,int i) {
    if(i<0||i>=l->length){
        return -1;
    }
    for(int j=i;j<l->length-1;j++){
        l->data[j]=l->data[j+1];
    }
    l->length-=1;
    return 0;
}

void print(SeqList* l) {
    int i=0;
    for(i=0;i<l->length-1;i++){
        printf("%d, ",l->data[i]);
    }
    if(i<l->length){
        printf("%d\n",l->data[i]);
    }
    return;
}

int main(int argc,char* argv[]) {
    SeqList* l=init(16);
    assert(l->capacity==16);

    assert(insert(l,1,9)==-1);
    insert(l,0,8);
    insert(l,1,7);
    insert(l,2,9);

    assert(find(l,7)==1);
    delete(l,1);
    assert(find(l,7)==-1);
    assert(find(l,9)==1);

    print(l);
    return 0;
}