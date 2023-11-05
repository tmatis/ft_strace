#include <statistics.h>

/**
 * @brief Get the statistics for the whole program.
 *
 * @return statistics_t* the statistics
 */
statistics_t *statistics_get(void)
{
	static statistics_t statistics = {
		.stats_x86_64 = NULL,
		.total_time_x86_64 = {0, 0},
		.stats_i386 = NULL,
		.total_time_i386 = {0, 0}
	};
	return &statistics;
}