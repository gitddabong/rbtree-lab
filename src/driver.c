#include "rbtree.h"

int main(int argc, char *argv[]) {
    rbtree *t = new_rbtree();
    t->root = rbtree_insert(t, 10);
    t->root = rbtree_insert(t, 20);
    t->root = rbtree_insert(t, 30);
    t->root = rbtree_insert(t, 40);
    t->root = rbtree_insert(t, 50);
    t->root = rbtree_insert(t, 60);

    delete_rbtree(t);
    free(t);
    return 0;
}