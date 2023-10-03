#include <execution.h>
#include <ft_test.h>
#include <sys/wait.h>

START_TEST(exec_program_not_found, "Test if exec_program returns EXEC_ERROR when the program is not found")
{
    char *argv[] = {"not_found", NULL};
    char *envp[] = {NULL};
    int result = exec_program(argv, envp);
    assert_equal(result, EXEC_ERROR);
} END_TEST

START_TEST(exec_program_valid, "Test if exec_program returns the pid of the child process when the program is found")
{
    char *argv[] = {"pwd", NULL};
    char *envp[] = {NULL};
    record_output record = launch_record();
    int result = exec_program(argv, envp);
    char *output = stop_record(&record);
    free(output);
    assert_true(result > 0);
    assert_true(waitpid(result, 0, 0) > 0);
} END_TEST