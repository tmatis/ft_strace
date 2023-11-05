#include <statistics.h>

/**
 * @brief Destroy the statistics.
 *
 * @param statistics the statistics to destroy
 */
void statistics_destroy(statistics_t *statistics)
{
	ft_rbtree_destroy(statistics->stats_x86_64);
	ft_rbtree_destroy(statistics->stats_i386);
}