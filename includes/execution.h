#pragma once

#include <bool_t.h>
#include <sys/types.h>

#define EXEC_ERROR -1
#define EXEC_CHILD_END -2

/**
 * @brief check if the file is executable and does exist
 *
 * @param path the path to the file to check
 * @return bool_t true if the file is executable and does exist, false otherwise
 */
bool_t file_exist(const char *path);

/**
 * @brief Search for a command in path
 *
 * @param command_name The command to search in path
 * @param path The path to search in
 * @return char* The path to the command, or NULL if not found
 */
char *search_in_path(const char *command_name, const char *path);

/**
 * @brief Execute a program
 *
 * @param argc
 * @param argv
 * @param envp
 * @return the pid of the child process or EXEC_ERROR if an error occurred
 */
int exec_program(char **argv, char **envp);

/**
 * @brief Setup tracing for tracee
 *
 * @param pid the pid of the tracee
 * @return 1 if an error occurred, 0 otherwise
 */
int setup_tracing(pid_t pid);