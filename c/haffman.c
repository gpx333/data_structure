/*************************************************************************
	> File Name: haffman.c
	> Author: gpx
	> Mail: 1457495424@qq.com
	> Created Time: 2018年10月28日 星期日 20时01分44秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>

typedef struct Node {
    int key, freq;
    struct Node *lchild, *rchild;
} Node;

Node *getNewNode(int key, int freq) {
    Node *p = (Node *)malloc(sizeof(Node));
    p->key = key;
    p->freq = freq;
    p->lchild = p->rchild = NULL;
    return p;
}

void clear(Node *root) {
    if (root == NULL) return ;
    clear(root->lchild);
    clear(root->rchild);
    free(root);
    return ;
}

int swap_node(Node **p, Node **q) {
    Node *temp = *p;
    *p = *q;
    *q = temp;
    return 1;
}

Node *build_haffman(Node **arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j]->freq < arr[n - i - 1]->freq) {
                swap_node(arr + j, arr + n - i - 1);                              // arr[n - i - 1]存储最小的那个
            }
            if (arr[j]->freq < arr[n - i  -2]->freq) {
                swap_node(arr + j, arr + n - i - 2);                              // arr[n - i - 2]存储次小的那个
            }
        }
        Node *temp = getNewNode(0, arr[n - i - 1]->freq + arr[n - i - 2]->freq);  // 申请一个地址空间,作为arr[n - i - 1]和arr[n - i - 2]的父节点,它的key是0
        temp->lchild = arr[n - i - 1];
        temp->rchild = arr[n - i - 2];
        arr[n - i - 2] = temp;                                                    // 将这个父节点放在最后一个位置,即arr[n - i - 2]处
    }
    return arr[0];
}

void extract_code(Node *root, char (*code)[20], int k, char *buffer) {
    buffer[k] = 0;
    if (root->key) {                                                              // 如果它的key不是0，代表是叶子节点，也就是我们待编码的节点
        strcpy(code[root->key], buffer);
        return ;
    }                                                                             // 否则左0右1向下编码
    buffer[k] = '0';
    extract_code(root->lchild, code, k + 1, buffer);
    buffer[k] = '1';
    extract_code(root->rchild, code, k + 1, buffer);
    return ;
}

void output(Node *root) {
    if (root == NULL) {return;}
    printf("%d ", root->freq);
    output(root->lchild);
    output(root->rchild);
    return ;
}

int main() {
    int n;
    scanf("%d", &n);
    Node **arr = (Node **)malloc(sizeof(Node *) * n);
    Node *root  = NULL;
    for (int i = 0; i < n; i++) {
        char key[10];
        int freq;
        scanf("%s%d", key, &freq);
        arr[i] = getNewNode(key[0], freq);
    }
    root = build_haffman(arr, n);
    //output(root);
    //printf("\n");
    char code[256][20] = {0}, buffer[20];
    extract_code(root, code, 0, buffer);
    for (int i = 0; i < 256; i++) {
        if (code[i][0] == 0) continue;
        printf("%c : %s\n", i, code[i]);
    }
    return 0;
}
