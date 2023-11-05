#include <ft_printf.h>
#include <statistics.h>
#include <syscall_strace.h>

// % time     seconds  usecs/call     calls    errors syscall
// ------ ----------- ----------- --------- --------- ----------------

static void log_table_head(void)
{
	ft_dprintf(STDERR_FILENO, "%% time     seconds  usecs/call     calls    errors syscall\n");
}

static void log_table_separator(void)
{
	ft_dprintf(STDERR_FILENO,
			   "------ ----------- ----------- --------- --------- ----------------\n");
}

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
		ft_dprintf(STDERR_FILENO, " %8s", "");
	ft_dprintf(STDERR_FILENO, " %s\n", syscall_name);
}

static int cmp_statistics_entry(statistics_entry_t *a, statistics_entry_t *b)
{
	if (a->time_percentage > b->time_percentage)
		return -1;
	else if (a->time_percentage < b->time_percentage)
		return 1;
	else
		return a->syscall_no - b->syscall_no;
}

typedef struct
{
	double total_time_sec;
	ft_rbtree_t *sorted_tree;
} statistics_entry_arg_t;

static void add_statistic_entry(statistics_entry_t *entry,
								statistics_entry_arg_t *statistics_entry_arg)
{
	double total_time_sec = statistics_entry_arg->total_time_sec;
	double entry_time_sec = entry->total_time.tv_sec + entry->total_time.tv_usec / 1000000.0;
	entry->time_percentage = entry_time_sec / total_time_sec * 100.0;
	ft_rbtree_insert(statistics_entry_arg->sorted_tree, entry);
}

static ft_rbtree_t *build_sorted_tree(ft_rbtree_t *tree, double total_time_sec)
{
	ft_rbtree_t *sorted_tree = ft_rbtree_new(sizeof(statistics_entry_t), cmp_statistics_entry);
	if (sorted_tree == NULL)
		return NULL;
    statistics_entry_arg_t statistics_entry_arg = {
        .total_time_sec = total_time_sec,
        .sorted_tree = sorted_tree
    };
	ft_rbtree_foreach_arg(tree, add_statistic_entry, &statistics_entry_arg);
	return sorted_tree;
}

static void log_table_line_callback(statistics_entry_t *entry)
{
    log_table_line(entry->time_percentage, &(entry->total_time), entry->calls, entry->errors, "syscall_name");
}

void log_table(ft_rbtree_t *tree, struct timeval *total_time, register_t type)
{
    (void)type;
    double total_time_sec = total_time->tv_sec + total_time->tv_usec / 1000000.0;
    ft_rbtree_t *sorted_tree = build_sorted_tree(tree, total_time_sec);
	log_table_head();
	log_table_separator();
    ft_rbtree_foreach(sorted_tree, log_table_line_callback);
    log_table_separator();
    ft_rbtree_destroy(sorted_tree);
}

/**
 * @brief Log the statistics.
 *
 * @param statistics the statistics
 */
void statistics_log(statistics_t *statistics)
{
    // log_table(statistics->stats_x86_64, &(statistics->total_time_x86_64), X86_64);
	if (statistics->stats_i386->value_size > 0)
	{
		ft_dprintf(STDERR_FILENO, "System call usage summary for 32 bit mode:\n");
	}
}