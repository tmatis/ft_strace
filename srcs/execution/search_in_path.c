#include <ft_string.h>
#include <ft_strace_utils.h>
#include <stdlib.h>
#include <ft_printf.h>
#include <sys/stat.h>

/**
 * @brief check if the file is executable and does exist
 * 
 * @param path the path to the file to check
 * @return bool_t true if the file is executable and does exist, false otherwise
 */
bool_t file_exist(const char *path)
{
    struct stat path_stat;
    if (stat(path, &path_stat) == -1)
        return false;
    return true;
}

/**
 * @brief Search for a command in path
 * 
 * @param command_name The command to search in path
 * @param path The path to search in
 * @return char* The path to the command, or NULL if not found
 */
char *search_in_path(const char *command_name, const char *path)
{
    if (!path)
    {
        log_error("search_in_path", "path is unset", false);
        return NULL;
    }
    char *path_copy = ft_strdup(path);
    if (!path_copy)
    {
        log_error("search_in_path", "ft_strdup failed", true);
        return NULL;
    }

    char *path_saveptr = path_copy;
    char *path_token = NULL;
    while ((path_token = ft_strtok(path_copy, ":")) != NULL)
    {
        char *command_path_to_test = NULL;
        int asprintf_result = ft_asprintf(
            &command_path_to_test,
            "%s/%s",
            path_token,
            command_name);
        if (!command_path_to_test || asprintf_result == -1)
        {
            log_error("search_in_path", "ft_asprintf failed", true);
            free(path_saveptr);
            return NULL;
        }
        if (file_exist(command_path_to_test))
        {
            free(path_saveptr);
            return command_path_to_test;
        }
        free(command_path_to_test);
        path_copy = NULL;
    }
    free(path_saveptr);
    return NULL;
}