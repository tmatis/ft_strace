#include <ft_rbtree.h>

static ft_rbtree_node_t *min_node(ft_rbtree_node_t *node)
{
    while (node->left != NULL)
        node = node->left;
    return node;
}

/**
 * @brief Get the next node in the tree.
 * 
 * @param node the node to get the next node of
 * @return ft_rbtree_node_t* the next node
 */
static ft_rbtree_node_t *next_node(ft_rbtree_node_t *node)
{
   ft_rbtree_node_t *next = NULL;
    if (node->right != NULL)
         next = min_node(node->right);
    else
    {
         next = node->parent;
         while (next != NULL && node == next->right)
         {
              node = next;
              next = next->parent;
         }
    }
    return next;
}

/**
 * @brief Applies a function to each node's value in a red-black tree.
 * 
 * @param tree the tree to iterate over
 * @param f the function to apply to each node's value
 */
void ft_rbtree_foreach(ft_rbtree_t *tree, void *f)
{
	if (tree == NULL || tree->root == NULL)
		return;
    ft_rbtree_node_t *node = tree->root;
    ((foreach_f)f)(node->variable_value);
    while ((node = next_node(node)) != NULL)
        ((foreach_f)f)(node->variable_value);
}

/**
 * @brief Applies a function to each node's value in a red-black tree.
 * 
 * @param tree the tree to iterate over
 * @param f the function to apply to each node's value with an argument
 * @param arg an argument to pass to the function
 */
void ft_rbtree_foreach_arg(ft_rbtree_t *tree, void *f, void *arg)
{
    if (tree == NULL || tree->root == NULL)
        return;
    ft_rbtree_node_t *node = tree->root;
    ((foreach_arg_f)f)(node->variable_value, arg);
    while ((node = next_node(node)) != NULL)
        ((foreach_arg_f)f)(node->variable_value, arg);
}