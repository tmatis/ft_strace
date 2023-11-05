#include <ft_test.h>
#include <registers.h>

START_TEST(test_registers_get_return, "Test registers_get_return for x86_64")
{
	user_regs_t regs = {0};
	regs.x86_64.rax = 42;
	assert_true(registers_get_return(&regs, X86_64) == 42);
}
END_TEST

START_TEST(test_registers_get_return_32, "Test registers_get_return for i386")
{
	user_regs_t regs = {0};
	regs.i386.eax = 42;
	assert_true(registers_get_return(&regs, I386) == 42);
}
END_TEST