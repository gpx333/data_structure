/*************************************************************************
	> File Name: AVL.c
	> Author: gpx
	> Mail: 1457495424@qq.com
	> Created Time: 2019年01月25日 星期五 15时07分09秒
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>

#define max(a, b) ({ \
    __typeof(a) __a = (a); \
    __typeof(b) __b = (b); \
    __a > __b ? __a : __b; \
})

typedef struct Node {
    int key;
    int heigth;
    struct Node *lchild, *rchild;
} Node;

Node *NIL = NULL;

Node *init(int key) {
    Node *p = (Node *)calloc(sizeof(Node), 1);
    p->key = key;
    p->heigth = 1;
    p->lchild = p->rchild = NIL;
    return p;
}

__attribute__((constructor))
void init_NIL() {
    NIL = init(0);
    NIL->heigth = 0;
    NIL->lchild = NIL->rchild = NIL;
    return ;
}

void calc_heigth(Node *root) {
    root->heigth = max(root->lchild->heigth, root->rchild->heigth) + 1;
    return ;
}

Node *left_rotate(Node *root) {
    Node *temp = root->rchild;
    root->rchild = temp->lchild;
    temp->lchild = root;
    calc_heigth(root);
    calc_heigth(temp);
    return temp;
}

Node *right_rotate(Node *root) {
    Node *temp = root->lchild;
    root->rchild = temp->rchild;
    temp->rchild = root;
    calc_heigth(root);
    calc_heigth(temp);
    return temp;
}

Node *maintain(Node *root) {
    if (abs(root->lchild->heigth - root->rchild->heigth) <= 1) return root;
    if (root->lchild->heigth > root->rchild->heigth) {
        if (root->lchild->lchild->heigth < root->lchild->rchild->heigth) {
            root->lchild = left_rotate(root->lchild);
        }
        root = right_rotate(root);
    } else {
        if (root->rchild->rchild->heigth < root->rchild->lchild->heigth) {
            root->rchild = right_rotate(root->rchild);
        }
        root = left_rotate(root);
    }
    return root;
}

Node *insert(Node *root, int key) {
    if (root == NIL) return init(key);
    if (root->key == key) return root;
    else if (root->key < key) root->rchild = insert(root->rchild, key);
    else root->lchild = insert(root->lchild, key);
    calc_heigth(root);
    return maintain(root);
}

Node *predecessor(Node *root) {
    Node *temp = root->lchild;
    while (temp->rchild != NIL) temp = temp->rchild;
    return temp;
}

Node *erase(Node *root, int key) {
    if (root == NIL) return root;
    if (root->key < key) {
        root->rchild = erase(root->rchild, key);
    } else if (root->key > key) {
        root->lchild = erase(root->lchild, key);
    } else {
        if (root->lchild == NIL && root->rchild == NIL) {
            free(root);
            return NIL;
        } else if (root->lchild == NIL || root->rchild == NIL) {
            Node *temp = (root->lchild != NIL ? root->lchild : root->rchild);
            free(root);
            return temp;
        } else {
            Node *temp = predecessor(root);
            root->key = temp->key;
            root->lchild = erase(root->lchild, temp->key);
        }
    }
    calc_heigth(root);
    return maintain(root);
}

void clear(Node *node) {
    if (node == NIL) return ;
    clear(node->lchild);
    clear(node->rchild);
    free(node);
    return ;
}

void output(Node *root) {
    if (root == NIL) return ;
    printf("(%d, %d, %d)\n", root->key, root->lchild->key, root->rchild->key);
    output(root->lchild);
    output(root->rchild);
    return ;
}

int main() {
    int op, val;
    Node *root = NIL;
    while (scanf("%d%d", &op, &val) != EOF) {
        switch (op) {
            case 1: root = insert(root, val); break;
            case 2: root = erase(root, val); break;
        }
        output(root);
    }
    clear(root);
    return 0;
}
