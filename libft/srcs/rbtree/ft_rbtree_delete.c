#include <bool_t.h>
#include <ft_rbtree.h>
#include <ft_string.h>

static ft_rbtree_node_t *left_rotate(ft_rbtree_node_t *node)
{
	ft_rbtree_node_t *parent = node->parent;
	ft_rbtree_node_t *grandParent = parent->parent;

	parent->right = node->left;
	if (node->left != NULL)
	{
		node->left->parent = parent;
	}
	node->parent = grandParent;
	parent->parent = node;
	node->left = parent;
	if (grandParent != NULL)
	{
		if (grandParent->right == parent)
		{
			grandParent->right = node;
		}
		else
		{
			grandParent->left = node;
		}
	}
	return node;
}

static ft_rbtree_node_t *right_rotate(ft_rbtree_node_t *node)
{
	ft_rbtree_node_t *parent = node->parent;
	ft_rbtree_node_t *grandParent = parent->parent;

	parent->left = node->right;
	if (node->right != NULL)
	{
		node->right->parent = parent;
	}
	node->parent = grandParent;
	parent->parent = node;
	node->right = parent;
	if (grandParent != NULL)
	{
		if (grandParent->right == parent)
		{
			grandParent->right = node;
		}
		else
		{
			grandParent->left = node;
		}
	}
	return node;
}

static void check_for_case2(ft_rbtree_node_t *to_delete, int delete, int fromDirection,
							ft_rbtree_node_t **root)
{
	if (to_delete == (*root))
	{
		(*root)->color = RBT_BLACK;
		return;
	}

	if (!delete &&to_delete->color == RBT_RED)
	{
		if (!fromDirection)
		{
			if (to_delete->right != NULL)
				to_delete->right->color = RBT_RED;
		}
		else
		{
			if (to_delete->left != NULL)
				to_delete->left->color = RBT_RED;
		}
		to_delete->color = RBT_BLACK;
		return;
	}

	// Get the sibling for further inspection
	ft_rbtree_node_t *sibling;
	ft_rbtree_node_t *parent = to_delete->parent;
	int locateChild = 0; // 0 if toDeleted is left of its parent else 1
	if (parent->right == to_delete)
	{
		sibling = parent->left;
		locateChild = 1;
	}
	else
	{
		sibling = parent->right;
	}

	// Case 2.1. i.e. if the any children of the sibling is red
	if ((sibling->right != NULL && sibling->right->color == 1) ||
		(sibling->left != NULL && sibling->left->color == 1))
	{
		if (sibling->right != NULL && sibling->right->color == 1)
		{
			// Sibling is left and child is right. i.e. LEFT RIGHT ROTATION
			if (locateChild == 1)
			{
				int parColor = parent->color;

				// Step 1: Left rotate sibling
				sibling = left_rotate(sibling->right);

				// Step 2: Right rotate updated sibling
				parent = right_rotate(sibling);

				// Check if the root is rotated
				if (parent->parent == NULL)
				{
					*root = parent;
				}

				// Step 3: Update the colors
				parent->color = parColor;
				parent->left->color = RBT_BLACK;
				parent->right->color = RBT_BLACK;

				// Delete the node (present at parent->right->right)
				if (delete)
				{
					if (to_delete->left != NULL)
					{
						to_delete->left->parent = parent->right;
					}
					parent->right->right = to_delete->left;
					free(to_delete);
				}
			}
			else
			{ // Sibling is right and child is also right. i.e. LEFT LEFT
			  // ROTATION

				int parColor = parent->color;

				// Left Rotate the sibling
				parent = left_rotate(sibling);

				// Check if the root is rotated
				if (parent->parent == NULL)
				{
					*root = parent;
				}

				// Update Colors
				parent->color = parColor;
				parent->left->color = RBT_BLACK;
				parent->right->color = RBT_BLACK;

				// Delete the node (present at parent->left->left)
				if (delete)
				{
					if (to_delete->right != NULL)
					{
						to_delete->right->parent = parent->left;
					}
					parent->left->left = to_delete->left;
					free(to_delete);
				}
			}
		}
		else
		{
			// Sibling is right and child is left. i.e. RIGHT LEFT ROTATION
			if (locateChild == 0)
			{
				int parColor = parent->color;

				// Step 1: Right rotate sibling
				sibling = right_rotate(sibling->left);

				// printf("%d - reached\n", sibling->val);
				// return;

				// Step 2: Left rotate updated sibling
				parent = left_rotate(sibling);

				// Check if the root is rotated
				if (parent->parent == NULL)
				{
					*root = parent;
				}

				// Step 3: Update the colors
				parent->color = parColor;
				parent->left->color = RBT_BLACK;
				parent->right->color = RBT_BLACK;

				// Delete the node (present at parent->left->left)
				if (delete)
				{
					if (to_delete->right != NULL)
					{
						to_delete->right->parent = parent->left;
					}
					parent->left->left = to_delete->right;
					free(to_delete);
				}
			}
			else
			{ // Sibling is left and child is also left. i.e. RIGHT RIGHT
			  // ROTATION

				int parColor = parent->color;

				// Right Rotate the sibling
				parent = right_rotate(sibling);

				// Check if the root is rotated
				if (parent->parent == NULL)
				{
					*root = parent;
				}

				// Update Colors
				parent->color = parColor;
				parent->left->color = RBT_BLACK;
				parent->right->color = RBT_BLACK;

				// Delete the node (present at parent->right->right)
				if (delete)
				{
					if (to_delete->left != NULL)
					{
						to_delete->left->parent = parent->right;
					}
					parent->right->right = to_delete->left;
					free(to_delete);
				}
			}
		}
	}
	else if (sibling->color == 0)
	{ // Make the sibling red and recur for its parent

		// Recolor the sibling
		sibling->color = RBT_RED;

		// Delete if necessary
		if (delete)
		{
			if (locateChild)
			{
				to_delete->parent->right = to_delete->left;
				if (to_delete->left != NULL)
				{
					to_delete->left->parent = to_delete->parent;
				}
			}
			else
			{
				to_delete->parent->left = to_delete->right;
				if (to_delete->right != NULL)
				{
					to_delete->right->parent = to_delete->parent;
				}
			}
		}

		check_for_case2(parent, 0, locateChild, root);
	}
	else
	{ // Bring the sibling on top and apply 2.1 or 2.2 accordingly
		if (locateChild)
		{ // Right Rotate

			to_delete->parent->right = to_delete->left;
			if (to_delete->left != NULL)
			{
				to_delete->left->parent = to_delete->parent;
			}

			parent = right_rotate(sibling);

			// Check if the root is rotated
			if (parent->parent == NULL)
			{
				*root = parent;
			}

			parent->color = RBT_BLACK;
			parent->right->color = RBT_RED;
			check_for_case2(parent->right, 0, 1, root);
		}
		else
		{ // Left Rotate

			to_delete->parent->left = to_delete->right;
			if (to_delete->right != NULL)
			{
				to_delete->right->parent = to_delete->parent;
			}
			parent = left_rotate(sibling);

			// Check if the root is rotated
			if (parent->parent == NULL)
			{
				*root = parent;
			}

			parent->color = RBT_BLACK;
			parent->left->color = RBT_RED;
			check_for_case2(parent->left, 0, 0, root);
		}
	}
}

void ft_rbtree_delete(ft_rbtree_t *tree, ft_rbtree_node_t *to_delete)
{
	ft_rbtree_node_t *buffRoot = to_delete;
	// Look for the leftmost of right node or right most of left node
	if (to_delete->left != NULL)
	{
		to_delete = to_delete->left;
		while (to_delete->right != NULL)
		{
			to_delete = to_delete->right;
		}
	}
	else if (to_delete->right != NULL)
	{
		to_delete = to_delete->right;
		while (to_delete->left != NULL)
		{
			to_delete = to_delete->left;
		}
	}

	if (to_delete == tree->root)
	{
		free(to_delete);
		tree->root = NULL;
		return;
	}

	ft_memcpy(buffRoot->variable_value, to_delete->variable_value, tree->value_size);
	ft_memcpy(to_delete->variable_value, buffRoot->variable_value, tree->value_size);

	// Checking for case 1
	if (to_delete->color == 1 || (to_delete->left != NULL && to_delete->left->color == 1) ||
		(to_delete->right != NULL && to_delete->right->color == 1))
	{
		// if it is a leaf
		if (to_delete->left == NULL && to_delete->right == NULL)
		{
			// Delete instantly
			if (to_delete->parent->left == to_delete)
			{
				to_delete->parent->left = NULL;
			}
			else
			{
				to_delete->parent->right = NULL;
			}
		}
		else
		{ // else its child should be red

			// Check for the exitstence of left node
			if (to_delete->left != NULL)
			{
				// The node should be right to its parent
				to_delete->parent->right = to_delete->left;
				to_delete->left->parent = to_delete->parent;
				to_delete->left->color = 1;
			}
			else
			{ // else the right node should be red
				to_delete->parent->left = to_delete->right;
				to_delete->right->parent = to_delete->parent;
				to_delete->right->color = 1;
			}
		}

		free(to_delete);
	}
	else
		check_for_case2(to_delete, 1, ((to_delete->parent->right == to_delete)), &(tree->root));
}