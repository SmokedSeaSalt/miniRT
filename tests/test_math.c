#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>
#include <inttypes.h>
#include <cmocka.h>

#include "math_inc.h"
#include <math.h>   // for fabs

/******************************************************************************/
/*                                                                            */
/* normalize_vec3                                                             */
/*                                                                            */
/******************************************************************************/


static void test_normalize_positive_vector(void **state) {
    (void) state;

    t_vec3 v = {3.0f, 4.0f, 0.0f, 0.0f}; // length = 5
    t_vec3 result = normalize_vec3(v);

    assert_float_equal(result.x, 0.6f, 1e-6);
    assert_float_equal(result.y, 0.8f, 1e-6);
    assert_float_equal(result.z, 0.0f, 1e-6);

    float magnitude = sqrtf(result.x*result.x + result.y*result.y + result.z*result.z);
    assert_float_equal(magnitude, 1.0f, 1e-6);
}

static void test_normalize_negative_vector(void **state) {
    (void) state;

    t_vec3 v = {-2.0f, -3.0f, -6.0f, 0.0f};
    t_vec3 result = normalize_vec3(v);

    float magnitude = sqrtf(result.x*result.x + result.y*result.y + result.z*result.z);
    assert_float_equal(magnitude, 1.0f, 1e-6);
}

static void test_normalize_zero_vector(void **state) {
    (void) state;

    t_vec3 v = {0.0f, 0.0f, 0.0f, 0.0f};
    t_vec3 result = normalize_vec3(v);

    assert_float_equal(result.x, 0.0f, 1e-6);
    assert_float_equal(result.y, 0.0f, 1e-6);
    assert_float_equal(result.z, 0.0f, 1e-6);
}

static void test_normalize_mixed_vector(void **state) {
    (void) state;

    t_vec3 v = {-3.0f, 4.0f, -12.0f, 0.0f};
    t_vec3 result = normalize_vec3(v);

    float magnitude = sqrtf(result.x*result.x + result.y*result.y + result.z*result.z);
    assert_float_equal(magnitude, 1.0f, 1e-6);

    // Check that each component maintains the correct sign
    assert_true(result.x < 0);
    assert_true(result.y > 0);
    assert_true(result.z < 0);
}

/******************************************************************************/
/*                                                                            */
/* vec3_dot                                                                   */
/*                                                                            */
/******************************************************************************/

static void test_dot_product_basic(void **state) {
    (void) state;

    t_vec3 a = {1.0, 2.0, 3.0};
    t_vec3 b = {4.0, -5.0, 6.0};

    double result = vec3_dot(a, b);

    // dot = 1*4 + 2*(-5) + 3*6 = 4 - 10 + 18 = 12
    assert_float_equal(result, 12.0, 1e-9);
}

static void test_dot_product_with_zero_vector(void **state) {
    (void) state;

    t_vec3 a = {3.5, -2.0, 7.1};
    t_vec3 zero = {0.0, 0.0, 0.0};

    double result = vec3_dot(a, zero);

    assert_float_equal(result, 0.0, 1e-9);
}

static void test_dot_product_orthogonal(void **state) {
    (void) state;

    t_vec3 a = {1.0, 0.0, 0.0};
    t_vec3 b = {0.0, 1.0, 0.0};

    double result = vec3_dot(a, b);

    assert_float_equal(result, 0.0, 1e-9);
}

static void test_dot_product_parallel(void **state) {
    (void) state;

    t_vec3 a = {2.0, 2.0, 2.0};
    t_vec3 b = {4.0, 4.0, 4.0};

    double result = vec3_dot(a, b);

    // dot = 2*4 + 2*4 + 2*4 = 24
    assert_float_equal(result, 24.0, 1e-9);
}


int main(void) {
    const struct CMUnitTest math[] = {
        cmocka_unit_test(test_normalize_positive_vector),
        cmocka_unit_test(test_normalize_negative_vector),
        cmocka_unit_test(test_normalize_zero_vector),
        cmocka_unit_test(test_normalize_mixed_vector),
        cmocka_unit_test(test_dot_product_basic),
        cmocka_unit_test(test_dot_product_with_zero_vector),
        cmocka_unit_test(test_dot_product_orthogonal),
        cmocka_unit_test(test_dot_product_parallel),
    };

    return cmocka_run_group_tests(math, NULL, NULL);
}