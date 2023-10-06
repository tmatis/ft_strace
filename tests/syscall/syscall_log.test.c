#include <ft_test.h>
#include <syscall_strace.h>
#include <unistd.h>

START_TEST(test_syscall_log_name_params, "Test that syscall_log_name_params logs the name of the syscall and its parameters")
{
    user_regs_x86_64_t regs_before;
    regs_before.orig_rax = 0x0;
    record_output record = launch_record();
    pid_t my_pid = getpid();
    syscall_log_name_params(my_pid, &regs_before);
    char *output = stop_record(&record);
    assert_string_equal(output, "read(");
    free(output);
}
END_TEST