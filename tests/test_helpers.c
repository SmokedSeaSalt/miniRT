#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>
#include <inttypes.h>
#include <cmocka.h>

#include "helpers.h"
#include <stdlib.h> //to use free
#include <math.h>   // for fabs

/******************************************************************************/
/*                                                                            */
/* ft_split_set.c                                                             */
/*                                                                            */
/******************************************************************************/

static void split_set_basic_split(void **state) {
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

static void split_set_empty_string(void **state) {
	(void) state;
	char **result = ft_split_set("", " ");
	assert_non_null(result);
	assert_null(result[0]);  // should be just an empty array
	free(result);
}

static void split_set_only_delimiters(void **state) {
	(void) state;
	char **result = ft_split_set(",,,", ",");
	assert_non_null(result);
	assert_null(result[0]);  // no words
	free(result);
}

static void split_set_single_word(void **state) {
	(void) state;
	char **result = ft_split_set("hello", " ");
	assert_non_null(result);
	assert_string_equal(result[0], "hello");
	assert_null(result[1]);
	free(result[0]);
	free(result);
}

static void split_set_multi_set(void **state) {
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

/******************************************************************************/
/*                                                                            */
/* ft_atof.c                                                                  */
/*                                                                            */
/******************************************************************************/

// Basic integers
static void atof_integer_values(void **state) {
	(void) state;
	assert_double_equal(0.0, ft_atof("0"), 1e-9);
	assert_double_equal(123.0, ft_atof("123"), 1e-9);
	assert_double_equal(-456.0, ft_atof("-456"), 1e-9);
}

// Decimal numbers
static void atof_decimal_values(void **state) {
	(void) state;
	assert_double_equal(3.14, ft_atof("3.14"), 1e-9);
	assert_double_equal(-0.987, ft_atof("-0.987"), 1e-9);
	assert_double_equal(42.5, ft_atof("42.5"), 1e-9);
}

// Leading/trailing spaces
static void atof_whitespace(void **state) {
	(void) state;
	assert_double_equal(7.25, ft_atof("   7.25"), 1e-9);
	assert_double_equal(-12.5, ft_atof(" -12.5  "), 1e-9);
}

// Invalid input handling
static void atof_invalid_input(void **state) {
	(void) state;
	// Depending on how your atof handles errors: returns 0.0 or stops at first invalid char
	assert_double_equal(0.0, ft_atof("abc"), 1e-9);
	assert_double_equal(12.0, ft_atof("12abc"), 1e-9);
}

// Edge cases
static void atof_edge_cases(void **state) {
	(void) state;
	assert_double_equal(0.5, ft_atof(".5"), 1e-9);
	assert_double_equal(-0.75, ft_atof("-.75"), 1e-9);
	assert_double_equal(123.0, ft_atof("123."), 1e-9);
}

// Explicitly check unsupported scientific notation
static void atof_scientific_notation(void **state) {
	(void) state;
	// Since "1e3" is not supported, expect it to stop at 'e' and return just 1
	assert_double_equal(1.0, ft_atof("1e3"), 1e-9);
	assert_double_equal(-2.0, ft_atof("-2E5"), 1e-9);
}

/******************************************************************************/
/*                                                                            */
/* ft_atof.c                                                                  */
/*                                                                            */
/******************************************************************************/

// Explicitly check unsupported scientific notation
static void ftoa_basics(void **state) {
	(void) state;
	assert_string_equal("1.0", ft_ftoa(1.0f));
	assert_string_equal("-123.0", ft_ftoa(-123.0f));
	assert_string_equal("0.7", ft_ftoa(0.7f));
	assert_string_equal("0.1", ft_ftoa(0.1f));
	assert_string_equal("-0.7", ft_ftoa(-0.7f));
	assert_string_equal("-0.1", ft_ftoa(-0.1f));
}



int main(void) {
	const struct CMUnitTest helpers[] = {
		cmocka_unit_test(split_set_basic_split),
		cmocka_unit_test(split_set_empty_string),
		cmocka_unit_test(split_set_only_delimiters),
		cmocka_unit_test(split_set_single_word),
		cmocka_unit_test(split_set_multi_set),
		cmocka_unit_test(atof_integer_values),
		cmocka_unit_test(atof_decimal_values),
		cmocka_unit_test(atof_whitespace),
		cmocka_unit_test(atof_invalid_input),
		cmocka_unit_test(atof_edge_cases),
		cmocka_unit_test(atof_scientific_notation),
		cmocka_unit_test(ftoa_basics),
	};
	return cmocka_run_group_tests(helpers, NULL, NULL);
}