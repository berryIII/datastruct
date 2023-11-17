# include <stdio.h>
# include <stdlib.h>
# define M 100

/**
 * 顺序存储实现的树形二叉树结构
*/
typedef int ElemType;
typedef struct SeqBinTree {
    int length;
    int capacity;
    ElemType* data; 
}LSeqBinTree,*SeqBinTree;

SeqBinTree init(int n){
    SeqBinTree t=(SeqBinTree) malloc (sizeof(SeqBinTree));
    t->capacity=n;
    t->data=(ElemType*) malloc (n*(sizeof(ElemType*)));
    t->length=0;
    return t;
}


int main(int argc,char* argv[]) {
    // 指针和指针内容的sizeof对比    
    SeqBinTree bt=init(100);
    printf("%d\n",bt->capacity);
    printf("%d\n",sizeof(ElemType*));
    printf("%d\n",sizeof(LSeqBinTree));
    printf("%d\n",sizeof(SeqBinTree));


    int idx=0;
    //int arr[15]={'A','B',-1,-1,'C',-1,-1};
    int arr[15]={'A','B',-1,-1,'C','D','F',-1,-1,'G',-1,-1,'E',-1,-1};
    //BTREE root=createBTREE(arr,&idx);
    //inorder(root);
    //postorder1(root);
}

