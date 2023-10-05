#include <unistd.h>
#include <stdlib.h>
#include <ft_string.h>
#include <execution.h>
#include <ft_strace_utils.h>
#include <stdio.h>
#include <signal.h>

/**
 * @brief Execute a program
 *
 * @param argc
 * @param argv
 * @param envp
 * @return the pid of the child process or EXEC_ERROR if an error occurred or EXEC_END_CHILD if the child process ended
 */
int exec_program(char **argv, char **envp)
{
    char *program_path = argv[0];
    char *slash_ptr = ft_strchr(program_path, '/');
    if (slash_ptr == NULL)
    {
        program_path = search_in_path(program_path, getenv("PATH"));
        if (program_path == NULL)
            return EXEC_ERROR;
    }
    pid_t pid = fork();
    if (pid == -1)
    {
        log_error("exec_program", "fork failed", true);
        if (slash_ptr == NULL)
            free(program_path);
        return EXEC_ERROR;
    }
    if (pid == 0)
    {
        raise(SIGSTOP); // we stop the child process to let the parent trace it
        execve(program_path, argv, envp);
        if (slash_ptr == NULL)
            free(program_path);
        log_error("exec_program", "execve failed", true);
        return EXEC_CHILD_END;
    }
    if (slash_ptr == NULL)
        free(program_path);
    return pid;
}