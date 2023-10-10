#include <ft_test.h>
#include <registers.h>

START_TEST(test_registers_get_type, "Test registers_get_type for x86_64")
{
	assert_true(registers_get_type(sizeof(struct user_regs_struct)) == X86_64);
}
END_TEST

START_TEST(test_registers_get_type_32, "Test registers_get_type for x86_32")
{
	assert_true(registers_get_type(sizeof(struct i386_user_regs_struct)) == X86_32);
}
END_TEST