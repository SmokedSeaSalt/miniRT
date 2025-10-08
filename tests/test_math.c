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
/* vec3_normalize                                                             */
/*                                                                            */
/******************************************************************************/


static void test_normalize_positive_vector(void **state) {
    (void) state;

    t_vec3 v = {3.0f, 4.0f, 0.0f, 0.0f}; // length = 5
    t_vec3 result = vec3_normalize(v);

    assert_float_equal(result.x, 0.6f, 1e-6);
    assert_float_equal(result.y, 0.8f, 1e-6);
    assert_float_equal(result.z, 0.0f, 1e-6);

    float magnitude = sqrtf(result.x*result.x + result.y*result.y + result.z*result.z);
    assert_float_equal(magnitude, 1.0f, 1e-6);
}

static void test_normalize_negative_vector(void **state) {
    (void) state;

    t_vec3 v = {-2.0f, -3.0f, -6.0f, 0.0f};
    t_vec3 result = vec3_normalize(v);

    float magnitude = sqrtf(result.x*result.x + result.y*result.y + result.z*result.z);
    assert_float_equal(magnitude, 1.0f, 1e-6);
}

static void test_normalize_zero_vector(void **state) {
    (void) state;

    t_vec3 v = {0.0f, 0.0f, 0.0f, 0.0f};
    t_vec3 result = vec3_normalize(v);

    assert_float_equal(result.x, 0.0f, 1e-6);
    assert_float_equal(result.y, 0.0f, 1e-6);
    assert_float_equal(result.z, 0.0f, 1e-6);
}

static void test_normalize_mixed_vector(void **state) {
    (void) state;

    t_vec3 v = {-3.0f, 4.0f, -12.0f, 0.0f};
    t_vec3 result = vec3_normalize(v);

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

/******************************************************************************/
/*                                                                            */
/* vec3_cross                                                                 */
/*                                                                            */
/******************************************************************************/

static void test_cross_product_basic(void **state) {
    (void) state;

    t_vec3 a = {1.0, 2.0, 3.0};
    t_vec3 b = {4.0, 5.0, 6.0};

    t_vec3 result = vec3_cross(a, b);

    // expected = (-3, 6, -3)
    assert_float_equal(result.x, -3.0, 1e-9);
    assert_float_equal(result.y,  6.0, 1e-9);
    assert_float_equal(result.z, -3.0, 1e-9);
}

static void test_cross_product_orthogonal(void **state) {
    (void) state;

    t_vec3 x = {1.0, 0.0, 0.0};
    t_vec3 y = {0.0, 1.0, 0.0};

    t_vec3 result = vec3_cross(x, y);

    // expected = (0, 0, 1)
    assert_float_equal(result.x, 0.0, 1e-9);
    assert_float_equal(result.y, 0.0, 1e-9);
    assert_float_equal(result.z, 1.0, 1e-9);
}

static void test_cross_product_parallel(void **state) {
    (void) state;

    t_vec3 a = {2.0, 2.0, 2.0};
    t_vec3 b = {4.0, 4.0, 4.0};

    t_vec3 result = vec3_cross(a, b);

    // expected = (0, 0, 0)
    assert_float_equal(result.x, 0.0, 1e-9);
    assert_float_equal(result.y, 0.0, 1e-9);
    assert_float_equal(result.z, 0.0, 1e-9);
}

static void test_cross_product_anti_commutative(void **state) {
    (void) state;

    t_vec3 a = {1.0, 0.0, 0.0};
    t_vec3 b = {0.0, 1.0, 0.0};

    t_vec3 ab = vec3_cross(a, b);
    t_vec3 ba = vec3_cross(b, a);

    // ab = (0, 0, 1)
    assert_float_equal(ab.x, 0.0, 1e-9);
    assert_float_equal(ab.y, 0.0, 1e-9);
    assert_float_equal(ab.z, 1.0, 1e-9);

    // ba = (0, 0, -1)
    assert_float_equal(ba.x, 0.0, 1e-9);
    assert_float_equal(ba.y, 0.0, 1e-9);
    assert_float_equal(ba.z, -1.0, 1e-9);
}

/******************************************************************************/
/*                                                                            */
/* get_angle_between_vec3                                                     */
/*                                                                            */
/******************************************************************************/

static void test_angle_parallel_vectors(void **state) {
    (void) state;

    t_vec3 a = {1.0f, 0.0f, 0.0f, 0.0f};
    t_vec3 b = {2.0f, 0.0f, 0.0f, 0.0f}; // Same direction, different magnitude

    float result = get_angle_between_vec3(&a, &b);

    // Parallel vectors should have 0 radians angle
    assert_float_equal(result, 0.0f, 1e-6);
}

static void test_angle_antiparallel_vectors(void **state) {
    (void) state;

    t_vec3 a = {1.0f, 0.0f, 0.0f, 0.0f};
    t_vec3 b = {-1.0f, 0.0f, 0.0f, 0.0f}; // Opposite direction

    float result = get_angle_between_vec3(&a, &b);

    // Antiparallel vectors should have π radians angle
    assert_float_equal(result, M_PI, 1e-6);
}

static void test_angle_orthogonal_vectors(void **state) {
    (void) state;

    t_vec3 a = {1.0f, 0.0f, 0.0f, 0.0f};
    t_vec3 b = {0.0f, 1.0f, 0.0f, 0.0f}; // 90 degrees apart

    float result = get_angle_between_vec3(&a, &b);

    // Orthogonal vectors should have π/2 radians angle
    assert_float_equal(result, M_PI / 2.0f, 1e-6);
}

static void test_angle_45_degrees(void **state) {
    (void) state;

    t_vec3 a = {1.0f, 0.0f, 0.0f, 0.0f};
    t_vec3 b = {1.0f, 1.0f, 0.0f, 0.0f}; // 45 degrees apart

    float result = get_angle_between_vec3(&a, &b);

    // Should be π/4 radians (45 degrees)
    assert_float_equal(result, M_PI / 4.0f, 1e-6);
}

static void test_angle_60_degrees(void **state) {
    (void) state;

    t_vec3 a = {1.0f, 0.0f, 0.0f, 0.0f};
    t_vec3 b = {0.5f, sqrtf(3.0f)/2.0f, 0.0f, 0.0f}; // 60 degrees apart

    float result = get_angle_between_vec3(&a, &b);

    // Should be π/3 radians (60 degrees)
    assert_float_equal(result, M_PI / 3.0f, 1e-5);
}

static void test_angle_3d_vectors(void **state) {
    (void) state;

    t_vec3 a = {1.0f, 1.0f, 1.0f, 0.0f};
    t_vec3 b = {1.0f, 0.0f, 0.0f, 0.0f};

    float result = get_angle_between_vec3(&a, &b);

    // Calculate expected angle manually
    // cos(θ) = (1*1 + 1*0 + 1*0) / (sqrt(3) * 1) = 1/sqrt(3)
    float expected = acosf(1.0f / sqrtf(3.0f));
    
    assert_float_equal(result, expected, 1e-6);
}

static void test_angle_normalized_vectors(void **state) {
    (void) state;

    t_vec3 a = {1.0f, 0.0f, 0.0f, 0.0f}; // Already normalized
    t_vec3 b = {0.0f, 1.0f, 0.0f, 0.0f}; // Already normalized

    float result = get_angle_between_vec3(&a, &b);

    assert_float_equal(result, M_PI / 2.0f, 1e-6);
}

static void test_angle_identical_vectors(void **state) {
    (void) state;

    t_vec3 a = {3.5f, -2.1f, 7.8f, 0.0f};
    t_vec3 b = {3.5f, -2.1f, 7.8f, 0.0f}; // Identical

    float result = get_angle_between_vec3(&a, &b);

    // Identical vectors should have 0 angle
    assert_float_equal(result, 0.0f, 1e-6);
}

static void test_angle_very_small_vectors(void **state) {
    (void) state;

    t_vec3 a = {1e-6f, 0.0f, 0.0f, 0.0f};
    t_vec3 b = {0.0f, 1e-6f, 0.0f, 0.0f};

    float result = get_angle_between_vec3(&a, &b);

    // Should still be π/2 even for very small vectors
    assert_float_equal(result, M_PI / 2.0f, 1e-5);
}

static void test_angle_large_vectors(void **state) {
    (void) state;

    t_vec3 a = {1000.0f, 0.0f, 0.0f, 0.0f};
    t_vec3 b = {0.0f, 1000.0f, 0.0f, 0.0f};

    float result = get_angle_between_vec3(&a, &b);

    // Should still be π/2 even for large vectors
    assert_float_equal(result, M_PI / 2.0f, 1e-6);
}

// Edge case: This would cause division by zero in your current implementation
static void test_angle_zero_vector(void **state) {
    (void) state;

    t_vec3 a = {1.0f, 0.0f, 0.0f, 0.0f};
    t_vec3 b = {0.0f, 0.0f, 0.0f, 0.0f}; // Zero vector

    // This test exposes a potential bug - your function doesn't handle zero vectors
    // The result will be undefined (NaN) due to division by zero
    float result = get_angle_between_vec3(&a, &b);
    
    // Check if result is NaN (which indicates the bug)
    assert_true(isnan(result));
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
		cmocka_unit_test(test_cross_product_basic),
		cmocka_unit_test(test_cross_product_orthogonal),
		cmocka_unit_test(test_cross_product_parallel),
		cmocka_unit_test(test_cross_product_anti_commutative),
		cmocka_unit_test(test_angle_parallel_vectors),
		cmocka_unit_test(test_angle_antiparallel_vectors),
		cmocka_unit_test(test_angle_orthogonal_vectors),
		cmocka_unit_test(test_angle_45_degrees),
		cmocka_unit_test(test_angle_60_degrees),
		cmocka_unit_test(test_angle_3d_vectors),
		cmocka_unit_test(test_angle_normalized_vectors),
		cmocka_unit_test(test_angle_identical_vectors),
		cmocka_unit_test(test_angle_very_small_vectors),
		cmocka_unit_test(test_angle_large_vectors),
		cmocka_unit_test(test_angle_zero_vector),
    };

    return cmocka_run_group_tests(math, NULL, NULL);
}

