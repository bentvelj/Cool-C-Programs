#include "expr.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define irl if (root->left)
#define ro root->operation
#define nck if (x == NULL)
#define ex expr_string

char *makeString(char *s1, char *s2, char *s3) {
  char *x = malloc((strlen(s1) + strlen(s2) + strlen(s3) + 1) * sizeof(char));
  nck return NULL;
  return strcat(strcat(strcpy(x, s1), s2), s3);
}

Node *createNode(char *s, double val) {
  char *t = malloc((strlen(s) + 1) * (sizeof(char)));
  if (t != NULL)
    strcpy(t, s);
  Node *x = malloc(sizeof(Node));
  nck return NULL;
  x->value = val, x->ex = t, x->num_parents = 0, x->left = x->right = NULL;
  return x;
}

Node *binop(Operation op, Node *a, Node *b) {
  if (a->num_parents || b->num_parents)
    return NULL;
  Node *x;
  if (op == mulop || op == divop) {
    char *t1 = makeString("(", a->ex, op == mulop ? ")*(" : ")/(");
    char *t2 = makeString(t1, b->ex, ")");
    x = createNode(t2, 0);
    free(t1), free(t2);
  } else {
    char *t1 = makeString(a->ex, op == addop ? "+" : "-", b->ex);
    x = createNode(t1, 0);
    free(t1);
  }
  nck return NULL;
  x->operation = op, x->left = a, x->right = b;
  a->num_parents = b->num_parents = 1;
  return x;
}

double evalTree(Node *root) {
  if (!(root->left || root->right))
    return root->value;
  if (ro == addop || ro == subop)
    root->value = ro == addop ? evalTree(root->left) + evalTree(root->right)
                              : evalTree(root->left) - evalTree(root->right);
  else
    root->value = ro == mulop ? evalTree(root->left) * evalTree(root->right)
                              : evalTree(root->left) / evalTree(root->right);
  return root->value;
}

void freeTree(Node *root) {
  irl freeTree(root->left), freeTree(root->right);
  free(root->expr_string), free(root);
}

Node *dth(Node *root, int f) {
  Node *x = createNode(root->expr_string, root->value);
  nck return NULL;
  x->num_parents = f, f = 1, x->operation = ro, x->value = root->value;
  irl x->left = dth(root->left, f), x->right = dth(root->right, f);
  return x;
}

Node *duplicateTree(Node *root) { return dth(root, 0); }

void printTree(Node *root) {
  printf("Node\n    expr_string = %s\n", root->expr_string);
  printf("    value = %g\n", root->value);
  printf("    num_parents = %d\n", root->num_parents);
  irl printTree(root->left), printTree(root->right);
}
