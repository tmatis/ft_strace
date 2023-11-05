#include <statistics.h>

static int cmp_statistics_entry(statistics_entry_t *a, statistics_entry_t *b)
{
	return a->syscall_no - b->syscall_no;
}

/**
 * @brief Initialize the statistics.
 *
 * @param statistics the statistics to initialize
 * @return int 0 if successful, 1 otherwise
 */
int statistics_init(statistics_t *statistics)
{
	statistics->stats_x86_64 = ft_rbtree_new(sizeof(statistics_entry_t), cmp_statistics_entry);
	if (statistics->stats_x86_64 == NULL)
		return 1;
	statistics->stats_i386 = ft_rbtree_new(sizeof(statistics_entry_t), cmp_statistics_entry);
	if (statistics->stats_i386 == NULL)
	{
		ft_rbtree_destroy(statistics->stats_x86_64);
		return 1;
	}
	return 0;
}
