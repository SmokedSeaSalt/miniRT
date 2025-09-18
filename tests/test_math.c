#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>
#include <inttypes.h>
#include <cmocka.h>

#include "math_inc.h"
#include <math.h>   // for fabs

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

int main(void) {
    const struct CMUnitTest math[] = {
        cmocka_unit_test(test_normalize_positive_vector),
        cmocka_unit_test(test_normalize_negative_vector),
        cmocka_unit_test(test_normalize_zero_vector),
        cmocka_unit_test(test_normalize_mixed_vector),
    };

    return cmocka_run_group_tests(math, NULL, NULL);
}