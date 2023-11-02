#include <ft_rbtree.h>

void ft_rbtree_destroy(ft_rbtree_t *tree)
{
	if (tree == NULL)
		return;
	ft_rbtree_node_t *buffRoot = tree->root;
	while (buffRoot != NULL)
	{
		if (buffRoot->left != NULL)
		{
			ft_rbtree_node_t *left = buffRoot->left;
			buffRoot->left = NULL;
			buffRoot = left;
		}
		else if (buffRoot->right != NULL)
		{
			ft_rbtree_node_t *right = buffRoot->right;
			buffRoot->right = NULL;
			buffRoot = right;
		}
		else
		{
			ft_rbtree_node_t *parent = buffRoot->parent;
			free(buffRoot);
			buffRoot = parent;
		}
	}
	free(tree);
}