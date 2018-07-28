#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <assert.h>
#include <limits.h>
#include "../headers/stack.h"
#include "../headers/queue.h"
#include "../headers/set.h"
#include "../headers/chtb.h"
#include "../headers/bitree.h"
#include "../headers/print.h"

// #define print(x) _Generic(x), int: 

/**
 * Polynomial computing
**/

void PolyCompute_speed_test(long (*func)(int, int arr[], int)){
    clock_t start, stop;
    double duration;
    start = clock();

    int n = 36;
    int arr[n+1];
    for(size_t i = 0; i <= n; ++i)
        arr[i] = i;
    (*func)(n, arr, 3);
    
    stop = clock();
    duration =  (double)(stop-start)/CLOCKS_PER_SEC;
    printf("%f\n", duration);
}

// O(n^2)
long PolyCompute1(int n, int arr[n+1], int x){
    long sum = 0;
    for(size_t i = 0; i <= n; ++i)
        sum += arr[i]*(long)pow(x, i);
        
    return sum;
}

// O(n)
long PolyCompute2(int n, int arr[n+1], int x){
    long sum = 0;
    for(size_t i = n+1; i-- > 0; )
        sum = (arr[i] + x * sum);
    return sum;
}

/**
 *  Maximum Subsequence
 **/

void MaxSubSeq_speed_test(int (*func)(int, int arr[])){
    clock_t start, stop;
    double duration;
    start = clock();

    int n = 32*4;
    int arr[32*4] = {4, -3, 5, -2, -1, 2, 6, -2, 
                   4, -3, 5, -2, -1, 2, 6, -2, 
                   4, -3, 5, -2, -1, 2, 6, -2,
                   4, -3, 5, -2, -1, 2, 6, -2,
                   4, -3, 5, -2, -1, 2, 6, -2, 
                   4, -3, 5, -2, -1, 2, 6, -2,
                   4, -3, 5, -2, -1, 2, 6, -2,
                   4, -3, 5, -2, -1, 2, 6, -2};
    
    printf("%d\n", (*func)(n, arr));
    
    stop = clock();
    duration =  (double)(stop-start)/CLOCKS_PER_SEC;
    printf("%f\n", duration);
}

void MaxSubSeq_speed_test1(int (*func)(int, int arr[], int, int)){
    clock_t start, stop;
    double duration;
    start = clock();

    int n = 32*4;
    int arr[32*4] = {4, -3, 5, -2, -1, 2, 6, -2, 
                   4, -3, 5, -2, -1, 2, 6, -2, 
                   4, -3, 5, -2, -1, 2, 6, -2,
                   4, -3, 5, -2, -1, 2, 6, -2,
                   4, -3, 5, -2, -1, 2, 6, -2, 
                   4, -3, 5, -2, -1, 2, 6, -2,
                   4, -3, 5, -2, -1, 2, 6, -2,
                   4, -3, 5, -2, -1, 2, 6, -2};
    
    printf("%d\n", (*func)(n, arr, 0, n-1));
    
    stop = clock();
    duration =  (double)(stop-start)/CLOCKS_PER_SEC;
    printf("%f\n", duration);
}

// O(n^3)
// 直接枚举求和比较
int MaxSubSeq1(int n, int arr[n]){
    int cursum = 0;
    int maxsum = 0;

    for(int i = 0; i < n; ++i)
        for(int j = i; j < n; ++j)
            {
                cursum = 0;
                for(int k = i; k <= j; ++k)
                    cursum += arr[k];
                if(cursum > maxsum) maxsum = cursum;
            }

    return maxsum;
}

// O(n^2)
// 直接枚举求和比较，对求和有优化
int MaxSubSeq2(int n, int arr[n]){
    int cursum = 0;
    int maxsum = 0;

    for(int i = 0; i < n; ++i){
        cursum = 0;
        for(int j = i; j < n; ++j){
            cursum += arr[j];
            if(cursum > maxsum) maxsum = cursum;
        }
    }

    return maxsum;
}

// O(nlogn)
// 分治 跨中间扫描最大序列和时，一端是固定的，所以直接枚举求和比较
int ScanMax(int n, int arr[n], int l, int r){
    int mid = (l+r)/2;
    int curleftsum = 0, currightsum = 0;
    int maxleftsum = 0, maxrightsum = 0;

    for(int i = mid+1; i-->l; ){
        curleftsum += arr[i];
        if(curleftsum > maxleftsum) maxleftsum = curleftsum;
    }

    for(int j = mid+1; j <= r; ++j){
        currightsum += arr[j];
        if(currightsum > maxrightsum) maxrightsum = currightsum;
    }

    return maxleftsum+maxrightsum;
}

int MaxSubSeq3(int n, int arr[n], int i, int j){
    if(i == j) return arr[i];

    int mid = (i+j)/2;
    int leftmax = MaxSubSeq3(n, arr, i, mid);
    int rightmax = MaxSubSeq3(n, arr, mid+1, j);
    int scanmax = ScanMax(n, arr, i, j);

    return ((leftmax > rightmax) ? ((leftmax > scanmax) ? leftmax : scanmax) : ((rightmax > scanmax) ? rightmax : scanmax));
}

// O(n)
// 在线处理：处理到一半时如果程序结束可以返回当前最大子序列和
// 最大的 trick 就是 cursum < 0 时置为0
// 不过这样做不能处理全为负数的情况
int MaxSubSeq4(int n, int arr[n]){
    int cursum = 0, maxsum = 0;

    for(int i = 0; i < n; ++i){
        cursum += arr[i];
        if(cursum > maxsum) maxsum = cursum;
        else if(cursum < 0) cursum = 0;
    }

    return maxsum;
}

int swap(void *a, void *b, int size){
    void *tmp;
    if((tmp = malloc(size)) == NULL) return -1;
    memcpy(tmp, a, size); memcpy(a, b, size); memcpy(b, tmp, size);
    free(tmp);
    return 0;
}

int match(const void *key1, const void *key2){
    return (*(int *)key1 == *(int *)key2);
}

int hash(const void *key){
    return *(int *)key;
}

int main(){
    int arr[] = {1, 2, 4, 3, 5};
    size_t len = sizeof(arr)/sizeof(arr[0]);

    printf("stack:\n");
    Stack *stack = NULL;
    stack = stack_init(stack, NULL);
    for(size_t i = 0; i < len; ++i) stack_push(stack, &arr[i]);
    for(size_t i = 0; i < len; ++i) {
        printf("%d ", *(int *)stack_peek(stack));
        stack_pop(stack, NULL);
    }

    printf("\n\n");

    printf("queue:\n");
    Queue *queue = NULL;
    queue = queue_init(queue, NULL);
    for(size_t i = 0; i < len; ++i) queue_enqueue(queue, &arr[i]);
    for(size_t i = 0; i < len; ++i) {
        printf("%d ", *(int *)queue_peek(queue));
        queue_dequeue(queue, NULL);
    }    

    printf("\n\n");

    printf("set:\n");
    Set *set1 = NULL, *set2 = NULL, *setu = NULL, *seti = NULL, *setd = NULL;
    set1 = set_init(set1, match, NULL);
    set2 = set_init(set2, match, NULL);
    int arr1[] = {1, 2, 3, 4, 5};
    int arr2[] = {3, 4, 5, 6, 7};
    for(size_t i = 0; i < 5; ++i) set_insert(set1, &arr1[i]);
    for(size_t i = 0; i < 5; ++i) set_insert(set2, &arr2[i]);
    setu = set_union(setu, set1, set2);
    seti = set_intersection(seti, set1, set2);
    setd = set_difference(setd, set1, set2);
    set_for_each(set1, int_print);
    set_for_each(set2, int_print);
    set_for_each(setu, int_print);
    set_for_each(seti, int_print);
    set_for_each(setd, int_print);

    printf("\n");

    printf("chtb:\n");
    CHTB *chtb = NULL;
    chtb = chtb_init(chtb, 5, hash, match, NULL);
    for(size_t i = 0; i < 5; ++i) chtb_insert(chtb, &arr2[i]);
    for(size_t i = 0; i < 5; ++i){
        int j = i;
        int *p = &j;
        if((chtb_lookup(chtb, (void **)&p) == 1))
        printf("%d ", *(int *)p);
    }

    printf("\n\n");

    printf("bitree:\n");
    BiTree bt;
    int a = 10;
    bitree_init(&bt, NULL);
    bitree_ins_left(&bt, NULL, &a);
    BiTreeNode *node = bt.root;
    for(size_t i = 0; i < len; ++i) {
        bitree_ins_left(&bt, node, &arr[i]);
        node = node->left;
    }
    bitree_inOrderTraverse(bt.root, int_print);
    bitree_rem_left(&bt, bt.root);
    bitree_inOrderTraverse(bt.root, int_print);
    bitree_destory(&bt);
    
    printf("\n\n");
}