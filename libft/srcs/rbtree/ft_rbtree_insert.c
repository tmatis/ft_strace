#include <ft_rbtree.h>
#include <ft_string.h>

/**
 * @brief Create a new node
 *
 * @param value the value to insert
 * @param value_size the size of the value
 * @param parent the parent of the node
 * @return ft_rbtree_node_t* the new node
 */
static ft_rbtree_node_t *new_node(void *value, size_t value_size, ft_rbtree_node_t *parent)
{
	ft_rbtree_node_t *node = malloc(sizeof(ft_rbtree_node_t) + value_size);
	if (node == NULL)
		return NULL;
	void *value_ptr = node->variable_value;
	ft_memcpy(value_ptr, value, value_size);
	node->color = RBT_RED;
	node->left = NULL;
	node->right = NULL;
	node->parent = parent;
	return node;
}

/**
 * @brief Check the node after insertion to see if it violates any of the red-black tree properties.
 *
 * @param node The node to check.
 */
static void check_node(ft_rbtree_node_t *node)
{
	if (node == NULL || node->parent == NULL)
		return;
	ft_rbtree_node_t *child = node;

	if (node->color == RBT_BLACK || (node->parent)->color == RBT_BLACK)
		return;
	ft_rbtree_node_t *parent = node->parent;
	ft_rbtree_node_t *grandParent = parent->parent;
	if (grandParent == NULL)
	{
		parent->color = RBT_BLACK;
		return;
	}

	if (grandParent->right != NULL && (grandParent->right)->color == RBT_RED &&
		grandParent->left != NULL && (grandParent->left)->color == RBT_RED)
	{
		(grandParent->right)->color = RBT_BLACK;
		(grandParent->left)->color = RBT_BLACK;
		grandParent->color = RBT_RED;
		return;
	}
	else
	{
		ft_rbtree_node_t *greatGrandParent = grandParent->parent;
		if (grandParent->right == parent)
		{
			if (parent->right == node)
			{
				grandParent->right = parent->left;
				if (parent->left != NULL)
				{
					(parent->left)->parent = grandParent;
				}
				parent->left = grandParent;
				grandParent->parent = parent;

				parent->parent = greatGrandParent;
				if (greatGrandParent != NULL)
				{
					if (greatGrandParent->left != NULL && greatGrandParent->left == grandParent)
						greatGrandParent->left = parent;
					else
						greatGrandParent->right = parent;
				}

				parent->color = RBT_BLACK;
				grandParent->color = RBT_RED;
			}
			else
			{
				parent->left = child->right;
				if (child->right != NULL)
				{
					(child->right)->parent = parent;
				}
				child->right = parent;
				parent->parent = child;

				grandParent->right = child->left;
				if (child->left != NULL)
				{
					(child->left)->parent = grandParent;
				}
				child->left = grandParent;
				grandParent->parent = child;

				child->parent = greatGrandParent;
				if (greatGrandParent != NULL)
				{
					if (greatGrandParent->left != NULL && greatGrandParent->left == grandParent)
						greatGrandParent->left = child;
					else
						greatGrandParent->right = child;
				}

				child->color = RBT_BLACK;
				grandParent->color = RBT_RED;
			}
		}
		else
		{
			if (parent->left == node)
			{
				grandParent->left = parent->right;
				if (parent->right != NULL)
				{
					(parent->right)->parent = grandParent;
				}
				parent->right = grandParent;
				grandParent->parent = parent;

				parent->parent = greatGrandParent;
				if (greatGrandParent != NULL)
				{
					if (greatGrandParent->left != NULL && greatGrandParent->left == grandParent)
						greatGrandParent->left = parent;
					else
						greatGrandParent->right = parent;
				}

				parent->color = RBT_BLACK;
				grandParent->color = RBT_RED;
			}
			else
			{
				parent->right = child->left;
				if (child->left != NULL)
					(child->left)->parent = parent;
				child->left = parent;
				parent->parent = child;

				grandParent->left = child->right;
				if (child->right != NULL)
				{
					(child->right)->parent = grandParent;
				}
				child->right = grandParent;
				grandParent->parent = child;

				child->parent = greatGrandParent;
				if (greatGrandParent != NULL)
				{
					if (greatGrandParent->left != NULL && greatGrandParent->left == grandParent)
						greatGrandParent->left = child;
					else
						greatGrandParent->right = child;
				}

				child->color = RBT_BLACK;
				grandParent->color = RBT_RED;
			}
		}
	}
}

/**
 * @brief Insert a node into the red-black tree.
 *
 * @param tree the tree to insert into
 * @param value the value to insert
 * @return ft_rbtree_node_t* the new node or NULL if an error occurred
 */
ft_rbtree_node_t *ft_rbtree_insert(ft_rbtree_t *tree, void *value)
{
	if (tree->root == NULL)
	{
		tree->root = new_node(value, tree->value_size, NULL);
		tree->root->color = RBT_BLACK;
		tree->node_count++;
		return tree->root;
	}
	ft_rbtree_node_t *buffRoot = tree->root;
	ft_rbtree_node_t *toInsert = NULL;
	while (buffRoot)
	{
		if (tree->cmp(value, buffRoot->variable_value) < 0)
		{
			// Go left
			if (buffRoot->left != NULL)
				buffRoot = buffRoot->left;
			else
			{
				// Insert The ft_rbtree_node_t
				toInsert = new_node(value, tree->value_size, buffRoot);
				if (toInsert == NULL)
					return NULL;
				buffRoot->left = toInsert;
				buffRoot = toInsert;

				// Check For Double Red Problems
				break;
			}
		}
		else
		{
			// Go right
			if (buffRoot->right != NULL)
				buffRoot = buffRoot->right;
			else
			{
				// Insert The ft_rbtree_node_t
				toInsert = new_node(value, tree->value_size, buffRoot);
				if (toInsert == NULL)
					return NULL;
				buffRoot->right = toInsert;
				buffRoot = toInsert;

				// Check For Double Red Problems
				break;
			}
		}
	}

	while (buffRoot != tree->root)
	{
		check_node(buffRoot);
		if (buffRoot->parent == NULL)
		{
			tree->root = buffRoot;
			break;
		}
		buffRoot = buffRoot->parent;
		if (buffRoot == tree->root)
			buffRoot->color = RBT_BLACK;
	}
	tree->node_count++;
	return toInsert;
}
