#include <ft_printf.h>
#include <statistics.h>
#include <syscall_strace.h>

// % time     seconds  usecs/call     calls    errors syscall
// ------ ----------- ----------- --------- --------- ----------------

typedef struct
{
	double total_time_sec;
	ft_rbtree_t *sorted_tree;
} statistics_entry_arg_t;

typedef struct
{
	register_t type;
	size_t total_call_count;
	size_t total_error_count;
} log_table_line_callback_arg_t;

/**
 * @brief Log the table head.
 *
 */
static void log_table_head(void)
{
	ft_dprintf(STDERR_FILENO, "%% time     seconds  usecs/call     calls    errors syscall\n");
}

/**
 * @brief Log the table separator.
 *
 */
static void log_table_separator(void)
{
	ft_dprintf(STDERR_FILENO,
			   "------ ----------- ----------- --------- --------- ----------------\n");
}

/**
 * @brief Log a line of the table.
 *
 * @param time_percentage the percentage of time spent in the syscall
 * @param total_time the total time spent in the syscall
 * @param calls the number of calls to the syscall
 * @param errors the number of errors returned by the syscall
 * @param syscall_name the name of the syscall
 */
static void log_table_line(double time_percentage, struct timeval *total_time, uint64_t calls,
						   uint64_t errors, const char *syscall_name)
{
	uint64_t total_time_usec = total_time->tv_sec * 1000000 + total_time->tv_usec;
	uint64_t usec_per_call = calls > 0 ? total_time_usec / calls : 0;
	double total_time_sec = total_time_usec / 1000000.0;
	ft_dprintf(STDERR_FILENO, "%6.2f %11lf %11ld %9ld", time_percentage, total_time_sec,
			   usec_per_call, calls);
	if (errors > 0)
		ft_dprintf(STDERR_FILENO, " %9ld", errors);
	else
		ft_dprintf(STDERR_FILENO, " %9s", "");
	ft_dprintf(STDERR_FILENO, " %s\n", syscall_name);
}

/**
 * @brief Compare two statistics entries.
 *
 * @param a the first entry
 * @param b the second entry
 * @return int difference between the two entries
 */
static int cmp_statistics_entry(statistics_entry_t *a, statistics_entry_t *b)
{
	if (a->time_percentage > b->time_percentage)
		return -1;
	else if (a->time_percentage < b->time_percentage)
		return 1;
	else
		return a->syscall_no - b->syscall_no;
}

/**
 * @brief Add a statistics entry to the sorted tree. (Callback for ft_rbtree_foreach_arg)
 *
 * @param entry the entry to add
 * @param statistics_entry_arg the argument to the function
 */
static void add_statistic_entry(statistics_entry_t *entry,
								statistics_entry_arg_t *statistics_entry_arg)
{
	double total_time_sec = statistics_entry_arg->total_time_sec;
	double entry_time_sec = entry->total_time.tv_sec + entry->total_time.tv_usec / 1000000.0;
	entry->time_percentage = entry_time_sec / total_time_sec * 100.0;
	ft_rbtree_insert(statistics_entry_arg->sorted_tree, entry);
}

/**
 * @brief Build a sorted tree from a tree of statistics entries.
 *
 * @param tree the tree of statistics entries
 * @param total_time_sec the total time spent in syscalls
 * @return ft_rbtree_t* the sorted tree
 */
static ft_rbtree_t *build_sorted_tree(ft_rbtree_t *tree, double total_time_sec)
{
	ft_rbtree_t *sorted_tree = ft_rbtree_new(sizeof(statistics_entry_t), cmp_statistics_entry);
	if (sorted_tree == NULL)
		return NULL;
	statistics_entry_arg_t statistics_entry_arg = {.total_time_sec = total_time_sec,
												   .sorted_tree = sorted_tree};
	ft_rbtree_foreach_arg(tree, add_statistic_entry, &statistics_entry_arg);
	return sorted_tree;
}

/**
 * @brief Log a line of the table. (Callback for ft_rbtree_foreach_arg)
 *
 * @param entry the entry to log
 * @param arg the argument to the function
 */
static void log_table_line_callback(statistics_entry_t *entry, log_table_line_callback_arg_t *arg)
{
	const syscall_description_t *syscall_description =
		syscall_get_description(entry->syscall_no, arg->type);
	log_table_line(entry->time_percentage, &(entry->total_time), entry->calls, entry->errors,
				   syscall_description->name);
	arg->total_call_count += entry->calls;
	arg->total_error_count += entry->errors;
}

/**
 * @brief Log the table.
 *
 * @param tree the tree of statistics entries
 * @param total_time the total time spent in syscalls
 * @param type the type of registers
 */
static void log_table(ft_rbtree_t *tree, struct timeval *total_time, register_t type)
{
	double total_time_sec = total_time->tv_sec + total_time->tv_usec / 1000000.0;
	ft_rbtree_t *sorted_tree = build_sorted_tree(tree, total_time_sec);
	log_table_head();
	log_table_separator();
	log_table_line_callback_arg_t arg = {
		.type = type, .total_call_count = 0, .total_error_count = 0};
	ft_rbtree_foreach_arg(sorted_tree, log_table_line_callback, &arg);
	ft_rbtree_destroy(sorted_tree);
	log_table_separator();
	log_table_line(100.0, total_time, arg.total_call_count, arg.total_error_count, "total");
}

/**
 * @brief Log the statistics.
 *
 * @param statistics the statistics
 */
void statistics_log(statistics_t *statistics)
{
	log_table(statistics->stats_x86_64, &(statistics->total_time_x86_64), X86_64);
	if (statistics->stats_i386->node_count > 0)
	{
		ft_dprintf(STDERR_FILENO, "System call usage summary for 32 bit mode:\n");
		log_table(statistics->stats_i386, &(statistics->total_time_i386), I386);
	}
}