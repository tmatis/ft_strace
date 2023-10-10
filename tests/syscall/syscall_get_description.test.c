#include <ft_test.h>
#include <syscall_strace.h>

START_TEST(test_read_description, "Test that the description is right for read")
{
	const syscall_description_t *description = syscall_get_description(0, X86_64);
	assert_string_equal(description->name, "read");
	assert_equal(description->return_type, SIGNED_INT);
	assert_equal(description->arg_types[0], -SIGNED_INT);
	assert_equal(description->arg_types[1], MEMSEG);
	assert_equal(description->arg_types[2], INT);
	assert_equal(description->arg_types[3], NONE);
}
END_TEST

START_TEST(test_unknown_description, "Test that the description is right for unknown")
{
	const syscall_description_t *description = syscall_get_description(10000, X86_64);
	assert_string_equal(description->name, "unknown");
	assert_equal(description->return_type, INT);
	assert_equal(description->arg_types[0], NONE);
	assert_equal(description->arg_types[1], NONE);
	assert_equal(description->arg_types[2], NONE);
	assert_equal(description->arg_types[3], NONE);
}
END_TEST

START_TEST(test_unknown_description_32, "Test that the description is right for unknown on x86_32")
{
	const syscall_description_t *description = syscall_get_description(10000, X86_32);
	assert_string_equal(description->name, "unknown");
	assert_equal(description->return_type, INT);
	assert_equal(description->arg_types[0], NONE);
	assert_equal(description->arg_types[1], NONE);
	assert_equal(description->arg_types[2], NONE);
	assert_equal(description->arg_types[3], NONE);
}
END_TEST