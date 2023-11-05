#include <registers.h>
#include <statistics.h>

/**
 * @brief Add an entry to the statistics.
 *
 * @param statistics the statistics
 * @param entry the entry to add
 * @param type the registers type
 */
void statistics_add_entry(statistics_t *statistics, uint64_t syscall_no, bool_t is_error,
						  struct timeval *total_time, register_type_t type)
{
	ft_rbtree_t *tree = type == X86_64 ? statistics->stats_x86_64 : statistics->stats_i386;
	struct timeval *total_time_all = type == X86_64 ? &(statistics->total_time_x86_64)
													  : &(statistics->total_time_i386);
	ft_rbtree_node_t *node = ft_rbtree_search(tree, &(statistics_entry_t){.syscall_no = syscall_no});
	if (node == NULL)
	{
		ft_rbtree_insert(tree, &(statistics_entry_t){.syscall_no = syscall_no,
													 .calls = 1,
													 .errors = is_error ? 1 : 0,
													 .total_time = *total_time,
													 .time_percentage = 0});
	}
	else
	{
		statistics_entry_t *node_entry = (statistics_entry_t *)node->variable_value;
		node_entry->calls += 1;
		if (is_error)
			node_entry->errors += 1;
		node_entry->total_time.tv_sec += total_time->tv_sec;
		node_entry->total_time.tv_usec += total_time->tv_usec;
	}
	total_time_all->tv_sec += total_time->tv_sec;
	total_time_all->tv_usec += total_time->tv_usec;
}