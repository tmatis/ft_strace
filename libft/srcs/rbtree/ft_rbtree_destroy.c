#include <ft_rbtree.h>

void ft_rbtree_destroy(ft_rbtree_t *tree)
{
	if (tree == NULL)
		return;
	ft_rbtree_node_t *buff_root = tree->root;
	while (buff_root != NULL)
	{
		if (buff_root->left != NULL)
		{
			ft_rbtree_node_t *left = buff_root->left;
			buff_root->left = NULL;
			buff_root = left;
		}
		else if (buff_root->right != NULL)
		{
			ft_rbtree_node_t *right = buff_root->right;
			buff_root->right = NULL;
			buff_root = right;
		}
		else
		{
			ft_rbtree_node_t *parent = buff_root->parent;
			free(buff_root);
			buff_root = parent;
		}
	}
	free(tree);
}