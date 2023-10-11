#include <execution.h>
#include <ft_test.h>
#include <signal.h>

START_TEST(exec_program_not_found,
		   "Test if exec_program returns EXEC_ERROR when the program is not found")
{
	char *argv[] = {"not_found", NULL};
	char *envp[] = {NULL};
	int result = exec_program(argv, envp);
	assert_equal(result, EXEC_ERROR);
}
END_TEST