#ifndef FT_RBTREE_H
#define FT_RBTREE_H

#include <stdlib.h>

typedef int (*cmp_f)(const void *, const void *);

typedef struct ft_rbtree_node_s
{
	struct ft_rbtree_node_s *parent;
	struct ft_rbtree_node_s *left;
	struct ft_rbtree_node_s *right;
	int color;
	char variable_value[];
} ft_rbtree_node_t;

#define ACCESS_VALUE(node, type) (*((type *)node->variable_value))

typedef struct
{
	ft_rbtree_node_t *root;
	size_t value_size;
	size_t node_count;
	cmp_f cmp;
} ft_rbtree_t;

#define RBT_RED 1
#define RBT_BLACK 0

ft_rbtree_t *ft_rbtree_new(size_t value_size, cmp_f cmp);
ft_rbtree_node_t *ft_rbtree_insert(ft_rbtree_t *tree, void *value);
void ft_rbtree_destroy(ft_rbtree_t *tree);
ft_rbtree_node_t *ft_rbtree_search(ft_rbtree_t *tree, void *value_to_match);
void ft_rbtree_delete(ft_rbtree_t *tree, ft_rbtree_node_t *to_delete);

#endif