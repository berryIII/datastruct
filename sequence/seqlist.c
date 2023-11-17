/**
 * 使用链式存储实现的线性表，带头结点的单链表
 */

# include <stdio.h>
# include <stdlib.h>
# include <assert.h>

typedef int ElemType;
typedef struct Node{
    /* data */
    struct Node* next;
    ElemType data;
}LNode,*LinkedList;

LinkedList newNode(ElemType x){
    LinkedList l=(LinkedList) malloc(sizeof(LinkedList));
    l->data=x;
    l->next=NULL;
    return l;
}

// 初始一个链式表，带有头结点
LinkedList* init(){
    return newNode(-1);
}

// 在结点p后插入一个
int insert(LinkedList p,LinkedList x){
    x->next=p->next;
    p->next=x;
    return 0;
}

// 查找，找不到返回NULL
LinkedList find(LinkedList p,ElemType x){
    if(p==NULL) {
        return NULL;
    }
    if(p->data==x){
        return p;
    }else{
        return find(p->next,x);
    }
}

// 返回链表最后一个结点
LinkedList last(LinkedList l){
    LinkedList pre=l;
    while (pre->next!=NULL){
        pre=pre->next;
    }
    return pre;
}

// 是否为空
int isEmpty(LinkedList l){
    if(l->next==NULL){
        return 1;
    }else{
        return 0;
    }
}

// 删除一个结点，失败返回-1，成功返回0
int delete(LinkedList l,ElemType x){
    LinkedList pre=l;
    while (l->next!=NULL&&l->next->data!=x){
        l=l->next;
    }
    if(l->next==NULL){
        return -1;
    }
    pre->next=pre->next->next;
    return 0;
}

int length(LinkedList l){
    if(l==NULL){
        return 0;
    }
    return length(l->next)+1;
}

void print(LinkedList l) {
    LinkedList pre=l->next;
    if(pre==NULL){
        return;
    }
    for(;pre->next!=NULL;pre=pre->next){
        printf("%d->",pre->data);
    }
    printf("%d\n",pre->data);
    return;
}

// josephus问题，n个人，从k开始报数，数到m的人处死，最后留一个人幸存
void josephus(int n,int m,int k) {
    LinkedList list=NULL,last=NULL; // 有必要初始化
    int i;
    for(i=1;i<=n;i++){
        LinkedList cur=newNode(i);
        if(list==NULL){
            last=list=cur;
        }else{
            last->next=cur;
            last=last->next;
        }
    }
    last->next=list; // 初始化循环队列完成
    LinkedList cur=list;
    LinkedList pre=last;
    for(i=0;i<k-1;i++){
        pre=cur;
        cur=cur->next;
    }
    while (cur!=cur->next){
        int j;
        for(j=1;j<=m-1;j++){
            pre=cur;
            cur=cur->next;
        }
        printf("%d dead\n",cur->data);
        pre->next=cur->next;
        LinkedList d=cur;
        cur=cur->next;
        free(d);
    }
    printf("%d live\n",cur->data);
    return;
}

int main(int argc,char* argv[]) {
    LinkedList l=init();
    assert(l->data==-1);
    assert(last(l)==l);
    LinkedList n1=newNode(7);
    LinkedList n2=newNode(5);
    LinkedList n3=newNode(4);
    insert(last(l),n1);
    insert(n2,n3);
    assert(length(n2)==2);
    insert(n1,n2);
    assert(length(n2)==1);
    josephus(8,4,3);
    return 0;
}