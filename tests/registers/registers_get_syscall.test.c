#include <ft_test.h>
#include <registers.h>

START_TEST(test_registers_get_syscall, "Test registers_get_syscall for x86_64")
{
	user_regs_t regs = {0};
	regs.x86_64.orig_rax = 42;
	assert_true(registers_get_syscall(&regs, X86_64) == 42);
}
END_TEST

START_TEST(test_registers_get_syscall_32, "Test registers_get_syscall for x86_32")
{
	user_regs_t regs = {0};
	regs.x86_32.orig_eax = 42;
	assert_true(registers_get_syscall(&regs, X86_32) == 42);
}
END_TEST