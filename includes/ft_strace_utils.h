#pragma once

#include <bool_t.h>

/**
 * @brief show a error message in STDERR
 *
 * @param context the context where the error was raised
 * @param message the error message
 * @param show_error if true, the message derivate from errno will be shown
 */
void log_error(const char *context, const char *message, bool_t show_error);