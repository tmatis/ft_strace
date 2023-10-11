#include <macros.h>
#include <signal.h>
#include <stddef.h>

/**
 * @brief Block signals
 *
 */
void signals_block(void)
{
	sigset_t blocked = {0};
	int to_block[] = {SIGHUP, SIGINT, SIGQUIT, SIGPIPE, SIGTERM};

	for (size_t i = 0; i < ELEM_COUNT(to_block); i++)
		sigaddset(&blocked, to_block[i]);
	sigprocmask(SIG_BLOCK, &blocked, NULL);
}

/**
 * @brief Unblock signals
 *
 */
void signals_unblock(void)
{
	sigset_t empty_mask;
	sigemptyset(&empty_mask);
	sigprocmask(SIG_SETMASK, &empty_mask, NULL);
}
