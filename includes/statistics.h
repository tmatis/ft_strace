#pragma once

#include <bool_t.h>
#include <ft_rbtree.h>
#include <registers.h>
#include <stdint.h>
#include <sys/time.h>

typedef struct
{
	ft_rbtree_t *stats_x86_64;
	struct timeval total_time_x86_64;
	ft_rbtree_t *stats_i386;
	struct timeval total_time_i386;
} statistics_t;

typedef struct
{
	uint64_t syscall_no;
	uint64_t calls;
	uint64_t errors;
	struct timeval total_time;
	double time_percentage;
} statistics_entry_t;

/**
 * @brief Destroy the statistics.
 *
 * @param statistics the statistics to destroy
 */
void statistics_destroy(statistics_t *statistics);

/**
 * @brief Get the statistics for the whole program.
 *
 * @return statistics_t* the statistics
 */
statistics_t *statistics_get(void);

/**
 * @brief Initialize the statistics.
 *
 * @param statistics the statistics to initialize
 * @return int 0 if successful, 1 otherwise
 */
int statistics_init(statistics_t *statistics);

/**
 * @brief Add an entry to the statistics.
 *
 * @param statistics the statistics
 * @param entry the entry to add
 * @param type the registers type
 */
void statistics_add_entry(statistics_t *statistics, uint64_t syscall_no, bool_t is_error,
						  struct timeval *total_time, register_type_t type);

/**
 * @brief Log the statistics.
 * 
 * @param statistics the statistics
 */
void statistics_log(statistics_t *statistics);