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
	// Set camera struct
	mock_camera.coords.x = 0.0f;
	mock_camera.coords.y = 0.0f;
	mock_camera.coords.z = 0.0f;
	mock_camera.fov_rad = deg_to_rad(60);
	mock_camera.fov_scale = tanf(mock_camera.fov_rad / 2);
	mock_camera.window_info.height = HEIGHT;
	mock_camera.window_info.width = WIDTH;
	mock_camera.window_info.aspect_ratio = (float)WIDTH / (float)HEIGHT;
	mock_camera.orientation.x = 0.0f;
	mock_camera.orientation.y = 0.0f;
	mock_camera.orientation.z = -1.0f;

	t_ray ray1 = get_ray(0, 0, &mock_camera); // Top-left
	t_ray ray2 = get_ray(1, 0, &mock_camera); // Top-right
	t_ray ray3 = get_ray(0, 1, &mock_camera); // Bottom-left
	t_ray ray4 = get_ray(1, 1, &mock_camera); // Bottom-right

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

int main(void) {
	const struct CMUnitTest parsing[] = {
		cmocka_unit_test(test_pixel_vector),
	};
	return cmocka_run_group_tests(parsing, NULL, NULL);
}

