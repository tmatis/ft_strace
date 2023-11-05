#include <ft_test.h>
#include <syscall_strace.h>

START_TEST(test_syscall_is_execve, "Test syscall_is_execve for x86_64")
{
	assert_true(syscall_is_execve(X_86_64_EXECVE_SYSCALL, X86_64));
}
END_TEST

START_TEST(test_syscall_is_execve_32, "Test syscall_is_execve for i386")
{
	assert_true(syscall_is_execve(X_86_32_EXECVE_SYSCALL, I386));
}
END_TEST