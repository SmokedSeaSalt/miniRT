#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>
#include <inttypes.h>
#include <cmocka.h>

#include "helpers.h"
#include <stdlib.h> //to use free

static void test_basic_split(void **state) {
	(void) state; // unused

	char **result = ft_split_set("hello world test", " ");

	assert_non_null(result);
	assert_string_equal(result[0], "hello");
	assert_string_equal(result[1], "world");
	assert_string_equal(result[2], "test");
	assert_null(result[3]);

	// free memory to avoid leaks
	for (int i = 0; result[i]; i++)
		free(result[i]);
	free(result);
}

static void test_empty_string(void **state) {
	(void) state;
	char **result = ft_split_set("", " ");
	assert_non_null(result);
	assert_null(result[0]);  // should be just an empty array
	free(result);
}

static void test_only_delimiters(void **state) {
	(void) state;
	char **result = ft_split_set(",,,", ",");
	assert_non_null(result);
	assert_null(result[0]);  // no words
	free(result);
}

static void test_single_word(void **state) {
	(void) state;
	char **result = ft_split_set("hello", " ");
	assert_non_null(result);
	assert_string_equal(result[0], "hello");
	assert_null(result[1]);
	free(result[0]);
	free(result);
}

static void test_multi_set(void **state) {
		(void) state;
	char **result = ft_split_set("hello,test.valid!check done", " ,.!");

	assert_non_null(result);
	assert_string_equal(result[0], "hello");
	assert_string_equal(result[1], "test");
	assert_string_equal(result[2], "valid");
	assert_string_equal(result[3], "check");
	assert_string_equal(result[4], "done");
	assert_null(result[5]);

	// free memory to avoid leaks
	for (int i = 0; result[i]; i++)
		free(result[i]);
	free(result);
}

int main(void) {
	const struct CMUnitTest tests[] = {
		cmocka_unit_test(test_basic_split),
		cmocka_unit_test(test_empty_string),
		cmocka_unit_test(test_only_delimiters),
		cmocka_unit_test(test_single_word),
		cmocka_unit_test(test_multi_set),
	};
	return cmocka_run_group_tests(tests, NULL, NULL);
}