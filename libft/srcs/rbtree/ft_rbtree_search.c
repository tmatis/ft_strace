#include <ft_rbtree.h>

ft_rbtree_node_t *ft_rbtree_search(ft_rbtree_t *tree, void *value_to_match)
{
	ft_rbtree_node_t *buff_root = tree->root;
	if (buff_root == NULL)
		return NULL;
	while (1)
	{
		int cmp = tree->cmp(value_to_match, buff_root->variable_value);
		if (cmp == 0)
			break;

		if (cmp > 0)
		{
			if (buff_root->right != NULL)
			{
				buff_root = buff_root->right;
			}
			else
				return NULL;
		}
		else
		{
			if (buff_root->left != NULL)
				buff_root = buff_root->left;
			else
				return NULL;
		}
	}
	return buff_root;
}