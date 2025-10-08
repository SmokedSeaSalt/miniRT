#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>
#include <inttypes.h>
#include <cmocka.h>

#include "math_inc.h"
#include "structs.h"
#include <math.h>   // for fabs

/******************************************************************************/
/*                                                                            */
/* intersect_sphere                                                           */
/*                                                                            */
/******************************************************************************/
#include <stdio.h>
static void test_sphere_intersects_hit(void **state) {
    (void) state;

    t_ray ray;
	ray.orig = vec3_new(3.34,2,2);
	ray.vec3 = vec3_normalize(vec3_new(-3,-0.46,-0.9));
    t_sphere sphere;
	sphere.coords = vec3_new(0,0,0);
	sphere.radius = 2;

    float result = sphere_intersects(&ray, &sphere);

    assert_true(result > 0.0f);
}

static void test_sphere_intersects_signle_point_hit(void **state) {
    (void) state;

    t_ray ray;
	ray.orig = vec3_new(2,2,2);
	ray.vec3 = vec3_normalize(vec3_new(-2,-2,0));
    t_sphere sphere;
	sphere.coords = vec3_new(0,0,0);
	sphere.radius = 2;

    float result = sphere_intersects(&ray, &sphere);

    assert_float_equal(result, 0,  1e-6);
}

static void test_sphere_intersects_no_hit(void **state) {
    (void) state;

    t_ray ray;
	ray.orig = vec3_new(2,2,2);
	ray.vec3 = vec3_normalize(vec3_new(-2,-2,1));
    t_sphere sphere;
	sphere.coords = vec3_new(0,0,0);
	sphere.radius = 1.5;

    float result = sphere_intersects(&ray, &sphere);

    assert_true(result < 0.0f);
}

static void test_nearest_hit_distance_both_positive(void **state) {
    (void) state;

    float dist1 = 1.0f;
    float dist2 = 2.0f;

    float result = decide_closest_distance(dist1, dist2);
    assert_true(result == dist1);
    result = decide_closest_distance(dist2, dist1);
    assert_true(result == dist1);
}

static void test_nearest_hit_distance_one_positive(void **state) {
    (void) state;

    float dist1 = 1.0f;
    float dist2 = -2.0f;

    float result = decide_closest_distance(dist1, dist2);
    assert_true(result == dist1);
    result = decide_closest_distance(dist2, dist1);
    assert_true(result == dist1);
}

static void test_nearest_hit_distance_none_positive(void **state) {
    (void) state;

    float dist1 = -1.0f;
    float dist2 = -2.0f;

    float result = decide_closest_distance(dist1, dist2);
    assert_true(result < 0.0f);
    result = decide_closest_distance(dist2, dist1);
    assert_true(result < 0.0f);
}

static void test_sphere_intersects_distance(void **state) {
    (void) state;

    t_ray ray;
	ray.orig = vec3_new(3.34,2,2);
	ray.vec3 = vec3_normalize(vec3_new(-3,-0.46,-0.9));
    t_sphere sphere;
	sphere.coords = vec3_new(0,0,0);
	sphere.radius = 2;

    float result = get_hit_dist_sphere(&ray, &sphere);
    assert_float_equal(result, 3.004506f, 1e-4);
}

static void test_sphere_intersects_normal(void **state) {
    (void) state;

    t_ray ray;
	ray.orig = vec3_new(3.34,2,2);
	ray.vec3 = vec3_normalize(vec3_new(-3,-0.46,-0.9));
    ray.results.hit_dist = 3.004506f;
    t_sphere sphere;
	sphere.coords = vec3_new(0,0,0);
	sphere.radius = 2;

    t_vec3 result = sphere_normal_at(&ray, &sphere);
    assert_float_equal(result.x, 0.246373f, 1e-4);
    assert_float_equal(result.y, 0.781719f, 1e-4);
    assert_float_equal(result.z, 0.572912f, 1e-4);

}

static void test_sphere_intersects_normal_inside(void **state) {
    (void) state;

    t_ray ray;
	ray.orig = vec3_new(0.44,2,2);
	ray.vec3 = vec3_normalize(vec3_new(-3,-1.5,-1.9));
    ray.results.hit_dist = 6.715488f;
    t_sphere sphere;
	sphere.coords = vec3_new(0,0,0);
	sphere.radius = 5;

    t_vec3 result = sphere_normal_at(&ray, &sphere);
    assert_float_equal(result.x, 0.957248f, 1e-4);
    assert_float_equal(result.y, 0.122624f, 1e-4);
    assert_float_equal(result.z, 0.261990f, 1e-4);
}


int main(void) {
    const struct CMUnitTest intersects[] = {
        cmocka_unit_test(test_sphere_intersects_hit),
        cmocka_unit_test(test_sphere_intersects_signle_point_hit),
        cmocka_unit_test(test_sphere_intersects_no_hit),
        cmocka_unit_test(test_nearest_hit_distance_both_positive),
        cmocka_unit_test(test_nearest_hit_distance_one_positive),
        cmocka_unit_test(test_nearest_hit_distance_none_positive),
        cmocka_unit_test(test_sphere_intersects_distance),
        cmocka_unit_test(test_sphere_intersects_normal),
        cmocka_unit_test(test_sphere_intersects_normal_inside),

    };

    return cmocka_run_group_tests(intersects, NULL, NULL);
}