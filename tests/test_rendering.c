#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>
#include <inttypes.h>
#include <cmocka.h>

#define WIDTH 2
#define HEIGHT 2
#include "consts.h"
#include "structs.h"
#include "parsing.h"
#include <stdlib.h> //to use malloc, free
#include "rendering.h"
#include <stdio.h>
#include <math.h>
#include "math_inc.h"


///////helpers
//////////

void print_vec3(const t_vec3 *vec) {
	printf("x: %f, y: %f, z: %f\n", vec->x, vec->y, vec->z);
}


/******************************************************************************/
/*                                                                            */
/* get_ray                                                                    */
/*                                                                            */
/******************************************************************************/

static void test_pixel_vector(void **state) {
	(void) state;
	// Create mock camera
	t_camera mock_camera;
	// Create mock window_info
	t_window_info window_info;

	// Set camera struct
	mock_camera.coords.x = 0.0f;
	mock_camera.coords.y = 0.0f;
	mock_camera.coords.z = 0.0f;
	mock_camera.fov_rad = deg_to_rad(60);
	mock_camera.orientation.x = 0.0f;
	mock_camera.orientation.y = 0.0f;
	mock_camera.orientation.z = -1.0f;
	// Set window_info
	window_info.fov_scale = tanf(mock_camera.fov_rad / 2);
	window_info.height = HEIGHT;
	window_info.width = WIDTH;
	window_info.aspect_ratio = (float)WIDTH / (float)HEIGHT;

	t_ray ray1 = get_ray(0, 0, &mock_camera, &window_info); // Top-left
	t_ray ray2 = get_ray(1, 0, &mock_camera, &window_info); // Top-right
	t_ray ray3 = get_ray(0, 1, &mock_camera, &window_info); // Bottom-left
	t_ray ray4 = get_ray(1, 1, &mock_camera, &window_info); // Bottom-right

	//////////////
	//Assertions//
	//////////////
	// assert_non_null(ray);
	// assert_float_equal(ray->orig.x, 0.0f, 0.001f);
	// assert_float_equal(ray->orig.y, 0.0f, 0.001f);
	// assert_float_equal(ray->orig.z, 0.0f, 0.001f);


	// PRINT RESULT

	print_vec3(&ray1.vec3);
	print_vec3(&ray2.vec3);
	print_vec3(&ray3.vec3);
	print_vec3(&ray4.vec3);



	// Clean up


}

static void test_cylinder(void **state) {
	(void) state;

	t_ray ray;
	t_cylinder cylinder;

	ray.orig.x = 0;
	ray.orig.y = 0;
	ray.orig.z = 5;
	ray.vec3.x = 0.05823434;
	ray.vec3.y = 0;
	ray.vec3.z = -0.99830294;
	cylinder.coords.x = 0;
	cylinder.coords.y = 0;
	cylinder.coords.z = -3.9;
	cylinder.orientation.x = 1;
	cylinder.orientation.y = 0;
	cylinder.orientation.z = 0;
	cylinder.diameter = 0.8;
	cylinder.radius = 0.4;
	cylinder.height = 5;

	printf("is hit = %d\n", is_hit_cylinder(&ray, &cylinder));
	printf("hit dist= %f\n", get_hit_dist_cylinder(&ray, &cylinder));


}




int main(void) {
	const struct CMUnitTest parsing[] = {
		cmocka_unit_test(test_pixel_vector),
		cmocka_unit_test(test_cylinder),
	};
	return cmocka_run_group_tests(parsing, NULL, NULL);
}

