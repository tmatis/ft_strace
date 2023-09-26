#pragma once

/**
 * @brief Search for a command in path
 * 
 * @param command_name The command to search in path
 * @param path The path to search in
 * @return char* The path to the command, or NULL if not found
 */
char *search_in_path(const char *command_name, const char *path);