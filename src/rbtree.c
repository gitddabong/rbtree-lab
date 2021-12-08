#include "rbtree.h"

#include <stdlib.h>

// 기존에 있던 함수 이외에 새로 만든 함수들
node_t *find_key(node_t *root, node_t *nil, const key_t key);
void free_rbtree(node_t *root);
void left_rotate(rbtree *t, node_t *x);
void right_rotate(rbtree *t, node_t *x);
void rbtree_insert_fixup(rbtree *t, node_t *z);
void rbtree_delete_fixup(rbtree *t, node_t *x);
void rb_transplant(rbtree *t, node_t *u, node_t *v);
void make_array(node_t *root, key_t *arr, const size_t n);

rbtree *new_rbtree(void) {
  rbtree *p = (rbtree *)calloc(1, sizeof(rbtree));
  // TODO: initialize struct if needed
  return p;
}

// 전위순회로 돌면서 메모리 반환
void delete_rbtree(rbtree *t) {
  // TODO: reclaim the tree nodes's memory
  free_rbtree(t->root);
}

void free_rbtree(node_t *root) {
    if (root == NULL)
    return;

  delete_rbtree(root->left);
  printf("%d\n", root->key);
  delete_rbtree(root->right);
  free(root);
}

void left_rotate(rbtree *t, node_t *x) {
  node_t *y = x->right;
  x->right = y->left;
  if (y->left != t->nil)
    y->left->parent = x;
  y->parent = x->parent;

  if (x->parent == t->nil)
    t->root = y;
  else if (x == x->parent->left)
    x->parent->left = y;
  else
    x->parent->right = y;
  y->left = x;
  x->parent = y;
}

void right_rotate(rbtree *t, node_t *y) {
  node_t *x = y->left;
  y->left = x->right;
  if (x->right != t->nil)
    x->right->parent = y;
  x->parent = y->parent;

  if (x->parent == t->nil)
    t->root = x;
  else if (y == y->parent->right)
    y->parent->right = x;
  else
    y->parent->left = x;
    x->right = y;
    y->parent = x;
}

node_t *rbtree_insert(rbtree *t, const key_t key) {
  // TODO: implement insert

  // part1. 새 노드의 컬러를 RED로 해서 삽입
  node_t *z = calloc(1, sizeof(node_t));
  node_t *y = t->nil;
  node_t *x = t->root;

  z->key = key;

  while (x != t->nil) {
    y = x;
    if (key < x->key)
      x = x->left;
    else
      x = x->right;
  }
  z->parent = y;

  if (y == t->nil)
    t->root = z;
  else if (key < y->key)
    y->left = z;
  else  
    y->right = z;

  z->left = t->nil;
  z->right = t->nil;
  z->color = RBTREE_RED;
  rbtree_insert_fixup(t, z);

  return t->root;
}

void rbtree_insert_fixup(rbtree *t, node_t *z) {
  node_t *y;
  
  while (z->parent->color == RBTREE_RED) {
    if (z->parent == z->parent->parent->left)
    {
      y = z->parent->parent->right;

      if (y->color == RBTREE_RED)
      {
        z->parent->color = RBTREE_BLACK;
        y->color = RBTREE_BLACK;
        z->parent->parent->color = RBTREE_RED;
        z = z->parent->parent;
      }
      else{
        if (z == z->parent->right) {
          z = z->parent;
          left_rotate(t, z);
        }
        z->parent->color = RBTREE_BLACK;
        z->parent->parent->color = RBTREE_RED;
        right_rotate(t, z->parent->parent);
      }
    }
    else {
      y = z->parent->parent->left;

      if (y->color == RBTREE_RED)
      {
        z->parent->color = RBTREE_BLACK;
        y->color = RBTREE_BLACK;
        z->parent->parent->color = RBTREE_RED;
        z = z->parent->parent;
      }
      else{
        if (z == z->parent->left) {
          z = z->parent;
          left_rotate(t, z);
        }
        z->parent->color = RBTREE_BLACK;
        z->parent->parent->color = RBTREE_RED;
        right_rotate(t, z->parent->parent);
      }
    }
  }
  t->root->color = RBTREE_BLACK;
}

node_t *rbtree_find(const rbtree *t, const key_t key) {
  // TODO: implement find
  return find_key(t->root, t->nil, key);
}

node_t *find_key(node_t *root, node_t *nil, const key_t key) {
  if (root == nil)
    return nil;

  if (root->key == key)
    return root;
  else if (root->key > key)
    return find_key(root->left, nil, key);
  else
    return find_key(root->right, nil, key);
}

node_t *rbtree_min(const rbtree *t) {
  // TODO: implement find
  node_t *tmp = t->root;
  while (tmp->left != NULL)
    tmp = tmp->left;
  
  return tmp;
}

node_t *rbtree_max(const rbtree *t) {
  // TODO: implement find
  node_t *tmp = t->root;
  while (tmp->right != NULL)
    tmp = tmp->right;

  return tmp;
  // return t->root;
}

int rbtree_erase(rbtree *t, node_t *z) {
  // TODO: implement erase
  node_t *y = z;    // z의 빈자리를 대체할 수를 가진 노드
  node_t *x;        // 살려야 될 z의 자식 노드 (많아봐야 1개. 있을 수도 없을 수도 있다)
  int y_ori_color = y->color;
  // 오른쪽 자식밖에 없는 경우
  if (z->left == t->nil) {
    x = z->right;
    rb_transplant(t, z, z->right);
  }
  // 왼쪽 자식밖에 없는 경우
  else if (z->right == t->nil) {
    x = z->left;
    rb_transplant(t, z, z->left);
  }
  // 자식이 둘 있는 경우 (없는 경우도 커버 가능?)
  else{
    y = rbtree_min(z->right);
    y_ori_color = y->color;
    x = y->right;
    if (y->parent == z)
      x->parent = z;
    else{
      rb_transplant(t, y, y->right);
      y->right = z->right;
      y->right->parent = y;
    }

    rb_transplant(t, z, y);
    y->left = z->left;
    y->left->parent = y;
    y->color = z->color;

  free(z);
  
  if (y_ori_color == RBTREE_BLACK)
    rbtree_delete_fixup(t, x);
  }
  return 0;
}

void rbtree_delete_fixup(rbtree *t, node_t *x) {
  node_t *w;
  while (x != t->root && x->color == RBTREE_BLACK) {
    if (x == x->parent->left){
      w = x->parent->right;
      if (w->color == RBTREE_RED){
        w->color = RBTREE_BLACK;
        x->parent->color = RBTREE_RED;
        left_rotate(t, x->parent);
        w = x->parent->right;
      }

      if (w->left->color == RBTREE_BLACK && w->right->color == RBTREE_BLACK) {
        w->color = RBTREE_RED;
        x = x->parent;
      }
      else {
        if (w->right->color == RBTREE_BLACK) {
          w->left->color = RBTREE_BLACK;
          w->color = RBTREE_RED;
          right_rotate(t, w);
          w = x->parent->right;
        }

        w->color = x->parent->color;
        x->parent->color = RBTREE_BLACK;
        w->right->color = RBTREE_BLACK;
        left_rotate(t, x->parent);
        x = t->nil;
      }
    }

    // right와 left를 바꾼 경우와 같다
    else {
      w = x->parent->left;
      if (w->color == RBTREE_RED){
        w->color = RBTREE_BLACK;
        x->parent->color = RBTREE_RED;
        left_rotate(t, x->parent);
        w = x->parent->left;
      }

      if (w->right->color == RBTREE_BLACK && w->left->color == RBTREE_BLACK) {
        w->color = RBTREE_RED;
        x = x->parent;
      }
      else {
        if (w->left->color == RBTREE_BLACK) {
          w->right->color = RBTREE_BLACK;
          w->color = RBTREE_RED;
          right_rotate(t, w);
          w = x->parent->left;
        }

        w->color = x->parent->color;
        x->parent->color = RBTREE_BLACK;
        w->left->color = RBTREE_BLACK;
        left_rotate(t, x->parent);
        x = t->nil;
      }
    }
  }
  x->color = RBTREE_BLACK;
}

void rb_transplant(rbtree *t, node_t *u, node_t *v) {
  if (u->parent == t->nil) 
    t->root = v;
  else if (u == u->parent->left)
    u->parent->right = v;
  else
    u->parent->right = v;
  
  v->parent = u->parent;
}

int idx = 0;
int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n) {
  // TODO: implement to_array
  // 중위순회하면 정렬된 배열을 얻을 수 있다
  node_t *root = t->root;
  make_array(root, arr, n);
  idx = 0;
  
  return 0;
}

void make_array(node_t *root, key_t *arr, const size_t n) {  
  if (root == NULL)
    return;
    
  if (idx == n)
    return;

  make_array(root->left, arr, n);
  arr[idx] = root->key;
  idx++;
  make_array(root->right, arr, n);
}