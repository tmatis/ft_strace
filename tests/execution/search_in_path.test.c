#include <ft_test.h>
#include <execution.h>

START_TEST(test_search_in_path, "Test that search_in_path works")
{
    char *path = "/bin:/usr/bin:/usr/local/bin";
    char *command = "ls";
    char *expected = "/bin/ls";

    char *result = search_in_path(command, path);

    assert_string_equal(expected, result); // this test will fail if you don't have ls in /bin
    free(result);
} END_TEST

START_TEST(test_search_in_path_not_found, "Test that search_in_path returns NULL when the command is not found")
{
    char *path = "/bin:/usr/bin:/usr/local/bin";
    char *command = "ls_not_found";

    char *result = search_in_path(command, path);

    assert_null(result);
} END_TEST

START_TEST(test_search_in_path_null_path, "Test that search_in_path returns NULL when the path is NULL")
{
    char *path = NULL;
    char *command = "ls";

    char *result = search_in_path(command, path);

    assert_null(result);
} END_TEST