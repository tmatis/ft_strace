#include <ft_test.h>
#include <syscall_strace.h>

START_TEST(test_syscall_log_param_int, "Test that syscall_log_param logs an positive int")
{
    record_output record = launch_record();
    syscall_log_param(0, INT, 42);
    char *output = stop_record(&record);
    assert_string_equal(output, "42");
    free(output);
} END_TEST

START_TEST(test_syscall_log_param_negative_int, "Test that syscall_log_param logs a negative int")
{
    record_output record = launch_record();
    syscall_log_param(0, INT, -42);
    char *output = stop_record(&record);
    assert_string_equal(output, "-42");
    free(output);
} END_TEST

START_TEST(test_syscall_log_param_string, "Test that syscall_log_param logs a hex")
{
    record_output record = launch_record();
    syscall_log_param(0, HEX, 0x42);
    char *output = stop_record(&record);
    assert_string_equal(output, "0x42");
    free(output);
} END_TEST
