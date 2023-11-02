#include <ft_rbtree.h>

ft_rbtree_t *ft_rbtree_new(size_t value_size, cmp_f cmp)
{
	ft_rbtree_t *tree = malloc(sizeof(ft_rbtree_t));
	if (tree == NULL)
		return NULL;
	tree->root = NULL;
	tree->value_size = value_size;
	tree->cmp = cmp;
	tree->node_count = 0;
	return tree;
}
