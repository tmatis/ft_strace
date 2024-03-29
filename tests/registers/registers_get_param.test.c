#include <ft_test.h>
#include <registers.h>

START_TEST(test_registers_get_param_0, "Test registers_get_param for x86_64 for param 0")
{
	user_regs_t regs = {0};
	regs.x86_64.rdi = 42;
	assert_true(registers_get_param(&regs, X86_64, 0) == 42);
}
END_TEST

START_TEST(test_registers_get_param_1, "Test registers_get_param for x86_64 for param 1")
{
	user_regs_t regs = {0};
	regs.x86_64.rsi = 42;
	assert_true(registers_get_param(&regs, X86_64, 1) == 42);
}
END_TEST

START_TEST(test_registers_get_param_2, "Test registers_get_param for x86_64 for param 2")
{
	user_regs_t regs = {0};
	regs.x86_64.rdx = 42;
	assert_true(registers_get_param(&regs, X86_64, 2) == 42);
}
END_TEST

START_TEST(test_registers_get_param_3, "Test registers_get_param for x86_64 for param 3")
{
	user_regs_t regs = {0};
	regs.x86_64.r10 = 42;
	assert_true(registers_get_param(&regs, X86_64, 3) == 42);
}
END_TEST

START_TEST(test_registers_get_param_4, "Test registers_get_param for x86_64 for param 4")
{
	user_regs_t regs = {0};
	regs.x86_64.r8 = 42;
	assert_true(registers_get_param(&regs, X86_64, 4) == 42);
}
END_TEST

START_TEST(test_registers_get_param_5, "Test registers_get_param for x86_64 for param 5")
{
	user_regs_t regs = {0};
	regs.x86_64.r9 = 42;
	assert_true(registers_get_param(&regs, X86_64, 5) == 42);
}
END_TEST

START_TEST(test_registers_get_param_0_32, "Test registers_get_param for i386 for param 0")
{
	user_regs_t regs = {0};
	regs.i386.ebx = 42;
	assert_true(registers_get_param(&regs, I386, 0) == 42);
}
END_TEST

START_TEST(test_registers_get_param_1_32, "Test registers_get_param for i386 for param 1")
{
	user_regs_t regs = {0};
	regs.i386.ecx = 42;
	assert_true(registers_get_param(&regs, I386, 1) == 42);
}
END_TEST

START_TEST(test_registers_get_param_2_32, "Test registers_get_param for i386 for param 2")
{
	user_regs_t regs = {0};
	regs.i386.edx = 42;
	assert_true(registers_get_param(&regs, I386, 2) == 42);
}
END_TEST

START_TEST(test_registers_get_param_3_32, "Test registers_get_param for i386 for param 3")
{
	user_regs_t regs = {0};
	regs.i386.esi = 42;
	assert_true(registers_get_param(&regs, I386, 3) == 42);
}
END_TEST

START_TEST(test_registers_get_param_4_32, "Test registers_get_param for i386 for param 4")
{
	user_regs_t regs = {0};
	regs.i386.edi = 42;
	assert_true(registers_get_param(&regs, I386, 4) == 42);
}
END_TEST

START_TEST(test_registers_get_param_5_32, "Test registers_get_param for i386 for param 5")
{
	user_regs_t regs = {0};
	regs.i386.ebp = 42;
	assert_true(registers_get_param(&regs, I386, 5) == 42);
}
END_TEST