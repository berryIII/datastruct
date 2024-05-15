# include <stdio.h>
# include <stdlib.h>
# include <time.h>

# define M 50;
# define MIN -1;

// 打印数组
void printNums(int nums[],int n){
    for(int i=0;i<n;i++){
        printf("%d ",nums[i]);
    }
    printf("\n");
}

// 生成n个随机数，M以内
int generator(int nums[],int n){
    srand(time(NULL));
    for(int i=0;i<n;i++){
        nums[i]=rand()%M;
    }
    printNums(nums,n);
    return 1;
}
void swap(int nums[],int i,int j){
    int tmp=nums[j];
    nums[j]=nums[i];
    nums[i]=tmp;
}

// T=O(n^2),S=O(1),不稳定排序
void selectSort(int nums[],int n){
    for(int i=0;i<n;i++){
        int minIdx=i; // 从[i...n]中选择选择最小的数放到i上，初始最小值为nums[i]
        for(int j=i+1;j<n;j++){
            if(nums[j]<nums[minIdx]){
                minIdx=j;
            }
        }
        swap(nums,i,minIdx);
    }
}

// T=O(n^2),S=O(1),稳定排序
// 近乎有序数组，效率极高，可提前终止循环
void insertSort(int nums[],int n){
    for(int i=1;i<n;i++){
        int cur=nums[i];
        int j=i-1; // [0,i-1]有序
        for(j=i-1;j>=0&&cur<nums[j];j--){
            nums[j+1]=nums[j];
        }
        nums[j+1]=cur;
    }
}

// T=O(n^2),效率比选择高，不如插入，S=O(1)稳定排序
void bubbleSort(int nums[],int n){
    int swaped=1;
    for(int j=n-1;j>=1&&swaped;j--){
        // 将[0,j-1]中最大的元素冒泡交换到j的位置
        swaped=0;
        for(int i=0;i<j;i++){
            if(nums[i]>nums[i+1]){
                swap(nums,i,i+1);
                swaped=1;
            }
        }
    }
}

// 快排的核心部分，以nums[l]为基准，将nums[l,r]分为两部分
int partition(int nums[],int l,int r){
    int key=nums[l];
    int i=l,j=r+1;
    while(i+1<j){
        if(nums[i+1]<=key){
            i+=1;
        }else{
            swap(nums,i+1,--j);
        }
    }
    swap(nums,l,i);
    return i;
}

void quickSort0(int nums[],int l,int r){
    if(l<r){
        int q=partition(nums,l,r);
        quickSort0(nums,l,q-1);
        quickSort0(nums,q+1,r);
    }
}

// 快速排序，O(n*logn)，S=O(1)，不稳定排序
void quickSort(int nums[],int n){
    quickSort0(nums,0,n-1);
}


// 归并排序，T=O(n*logn)，S=O(n)，稳定排序
// TODO，基于链表的归并排序
void mergeSort0(int nums[],int l,int r){
    if(l<r){
        int q=l+(r-l)/2;
        mergeSort0(nums,l,q);
        mergeSort0(nums,q+1,r);
        int left[r-l+1];
        int right[r-l+1];
        for(int i=l;i<=q;i++){
            left[i-l]=nums[i];
        }
        for(int i=q+1;i<=r;i++){
            right[i-q-1]=nums[i];
        }
        int j1=0,j2=0;
        int n1=q-l+1,n2=r-q;
        for(int i=l;i<=r;i++){
            if(j1<n1&&j2<n2){
                if(left[j1]<right[j2]){
                    nums[i]=left[j1++];
                }else{
                    nums[i]=right[j2++];
                }
            }else if(j1<n1){
                nums[i]=left[j1++];
            }else{
                nums[i]=right[j2++];
            }
        }
    }
}

void mergeSort(int nums[],int n){
    mergeSort0(nums,0,n-1);
}


int main(int argc,char* argv[]) {
    int n=15;
    int nums[n];
    generator(nums,n);
    mergeSort(nums,n);
    printNums(nums,n);
    return 0;
}