# include "seqarray.c"

void testSeqArray() {
    SeqList* l;
    printf("%d\n",l->capacity);
    l=init(16);
    printf("%d\n",l->capacity);
    //insert(l,2,3);
    //printf("%d\n",find(l,2));

}

int main(int argc,char* argv[]) {
    testSeqArray();
    return 0;
}
