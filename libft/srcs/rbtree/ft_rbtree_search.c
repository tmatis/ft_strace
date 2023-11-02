#include <ft_rbtree.h>

ft_rbtree_node_t *ft_rbtree_search(ft_rbtree_t *tree, void *value_to_match)
{
	ft_rbtree_node_t *buffRoot = tree->root;
	if (buffRoot == NULL)
		return NULL;
	while (1)
	{
		int cmp = tree->cmp(value_to_match, buffRoot->variable_value);
		if (cmp == 0)
			break;

		if (cmp > 0)
		{
			if (buffRoot->right != NULL)
			{
				buffRoot = buffRoot->right;
			}
			else
				return NULL;
		}
		else
		{
			if (buffRoot->left != NULL)
				buffRoot = buffRoot->left;
			else
				return NULL;
		}
	}
	return buffRoot;
}