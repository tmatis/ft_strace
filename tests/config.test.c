#include <ft_test.h>
#include <config.h>

START_TEST(test_help_short, "Test that help option is activated when -h is passed")
{
    config_t *config = get_config();
    args_t args;

    char *argv[] = {"./test", "-h", NULL};
    int argc = 2;

    assert_equal(0, parse_args(argc, argv, &args, config));

    assert_true(is_option_set(OPT_MASK_HELP, config));
} END_TEST


START_TEST(test_help_long, "Test that help option is activated when --help is passed")
{
    config_t *config = get_config();
    args_t args;

    char *argv[] = {"./test", "--help", NULL};
    int argc = 2;

    assert_equal(0, parse_args(argc, argv, &args, config));

    assert_true(is_option_set(OPT_MASK_HELP, config));
} END_TEST

START_TEST(test_help_short_long, "Test that help option is activated when -h and --help are passed")
{
    config_t *config = get_config();
    args_t args;

    char *argv[] = {"./test", "-h", "--help", NULL};
    int argc = 3;

    assert_equal(0, parse_args(argc, argv, &args, config));

    assert_true(is_option_set(OPT_MASK_HELP, config));
} END_TEST