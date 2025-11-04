#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>
#include <inttypes.h>
#include <cmocka.h>

#include "structs.h"
#include "parsing.h"
#include "math_inc.h"
#include <stdlib.h> //to use malloc, free

/******************************************************************************/
/*                                                                            */
/* add_object_to_back                                                         */
/*                                                                            */
/******************************************************************************/

// ---- Helpers for tests ----
static t_object *make_object(t_obj_type type)
{
	t_object *obj = malloc(sizeof(t_object));
	obj->type = type;
	obj->data = NULL;
	obj->next = NULL;
	return obj;
}

static void free_list(t_object *list)
{
	while (list)
	{
		t_object *next = list->next;
		free(list);
		list = next;
	}
}

// Test adding to NULL list pointer (should do nothing)
static void test_null_list_ptr(void **state) {
	(void)state;
	t_object *obj = make_object(SPHERE);
	add_object_to_back(NULL, obj);
	// The new object should remain unchanged
	assert_non_null(obj);
	assert_int_equal(obj->type, SPHERE);
	assert_null(obj->next);
	free(obj);
}

// Test adding to an empty list
static void test_add_to_empty_list(void **state) {
	(void)state;
	t_object *list = NULL;
	t_object *obj = make_object(PLANE);

	add_object_to_back(&list, obj);

	assert_ptr_equal(list, obj);
	assert_int_equal(list->type, PLANE);
	assert_null(list->next);
	free_list(list);
}


// Test adding one element to a non-empty list
static void test_add_to_non_empty_list(void **state) {
	(void)state;
	t_object *head = make_object(SPHERE);
	t_object *obj2 = make_object(PLANE);

	t_object *list = head;
	add_object_to_back(&list, obj2);

	assert_ptr_equal(list, head); // head unchanged
	assert_ptr_equal(head->next, obj2); // obj2 appended
	assert_null(obj2->next);

	free_list(list);
}


// Test adding multiple elements
static void test_add_multiple(void **state) {
	(void)state;
	t_object *head = make_object(SPHERE);
	t_object *obj2 = make_object(PLANE);
	t_object *obj3 = make_object(CYLINDER);

	t_object *list = head;
	add_object_to_back(&list, obj2);
	add_object_to_back(&list, obj3);

	assert_ptr_equal(list, head); // head preserved
	assert_ptr_equal(head->next, obj2);
	assert_ptr_equal(obj2->next, obj3);
	assert_null(obj3->next);

	free_list(list);
}

/******************************************************************************/
/*                                                                            */
/* new_cylinder_struct                                                        */
/*                                                                            */
/******************************************************************************/


static void test_new_cylinder_success(void **state) {
	(void)state;
	t_scene scene = {0};
	char *args[] = {"c", "50.0,0,20.6", "0,1,0", "10.5", "20.2", "255,255,255", NULL};

	int res = new_cylinder_struct(&scene, args);
	assert_int_equal(res, 0);
	assert_non_null(scene.objects);
	t_object *obj = scene.objects;
	assert_int_equal(obj->type, CYLINDER);
	t_cylinder *cyl = (t_cylinder *)obj->data;
	assert_float_equal(cyl->coords.x, 50.0, 1e-6);
	assert_float_equal(cyl->coords.y, 0.0, 1e-6);
	assert_float_equal(cyl->coords.z, 20.6, 1e-6);
	assert_float_equal(cyl->orientation.x, 0, 1e-6);
	assert_float_equal(cyl->orientation.y, 1, 1e-6);
	assert_float_equal(cyl->orientation.z, 0, 1e-6);
	assert_float_equal(cyl->diameter, 10.5, 1e-6);
	assert_float_equal(cyl->height, 20.2, 1e-6);
	assert_int_equal(cyl->color.r, 255);
	assert_int_equal(cyl->color.g, 255);
	assert_int_equal(cyl->color.b, 255);

	free(cyl);
	free(obj);
}


static void test_new_cylinder_invalid_args(void **state) {
	(void)state;
	t_scene scene = {0};
	char *args[] = {"c", "0","0","0", NULL};

	int res = new_cylinder_struct(&scene, args);
	assert_int_equal(res, 1);
	assert_null(scene.objects);
}


static void test_new_cylinder_orientation_zero(void **state) {
	(void)state;
	t_scene scene = {0};
	char *args[] = {"c", "0,0,0", "0,0,0", "10", "20", "255,255,255", NULL};

	int res = new_cylinder_struct(&scene, args);
	assert_int_equal(res, 1);
	assert_null(scene.objects);
}

/******************************************************************************/
/*                                                                            */
/* is_valid_extension                                                         */
/*                                                                            */
/******************************************************************************/

// Test cases
static void test_valid_extension(void **state) {
    (void)state; // unused
    assert_int_equal(is_valid_extension("file.rt"), 1);
}

static void test_invalid_extension(void **state) {
    (void)state;
    assert_int_equal(is_valid_extension("file.txt"), 0);
}

static void test_no_extension(void **state) {
    (void)state;
    assert_int_equal(is_valid_extension("file"), 0);
}

static void test_long_filename_with_rt(void **state) {
    (void)state;
    assert_int_equal(is_valid_extension("archive.tar.rt"), 1);
}

static void test_extension_rt_in_middle(void **state) {
    (void)state;
    assert_int_equal(is_valid_extension("file.rt.backup"), 0);
}

static void test_invalid_longer_extension(void **state) {
    (void)state;
    assert_int_equal(is_valid_extension("file.rtest"), 0);
}

static void test_invalid_longer_extension_rt_end(void **state) {
    (void)state;
    assert_int_equal(is_valid_extension("file.testrt"), 0);
}

static void test_only_extension(void **state) {
    (void)state;
    assert_int_equal(is_valid_extension(".rt"), 1);
}

/******************************************************************************/
/*                                                                            */
/* parse_file                                                                 */
/*                                                                            */
/******************************************************************************/

static void test_parse_file_normal(void **state) {
    (void)state;

	t_scene scene = {0};
    assert_int_equal(parse_file(&scene, "test_files/sample.rt"), 0);

	assert_non_null(scene.ambient);
	assert_float_equal(scene.ambient->ratio, 0.2, 1e-6);
	assert_int_equal(scene.ambient->color.r, 255);
	assert_int_equal(scene.ambient->color.g, 255);
	assert_int_equal(scene.ambient->color.b, 255);

	assert_non_null(scene.camera);
	assert_float_equal(scene.camera->coords.x, -50, 1e-6);
	assert_float_equal(scene.camera->coords.y, 0, 1e-6);
	assert_float_equal(scene.camera->coords.z, 20, 1e-6);
	assert_float_equal(scene.camera->orientation.x, 0, 1e-6);
	assert_float_equal(scene.camera->orientation.y, 0, 1e-6);
	assert_float_equal(scene.camera->orientation.z, 1, 1e-6);
	assert_float_equal(scene.camera->fov_rad, deg_to_rad(70), 1e-6);

	assert_non_null(scene.lights);
	assert_float_equal(scene.lights->coords.x, -40, 1e-6);
	assert_float_equal(scene.lights->coords.y, 0, 1e-6);
	assert_float_equal(scene.lights->coords.z, 30, 1e-6);
	assert_float_equal(scene.lights->brightness, 0.7, 1e-6);
	assert_int_equal(scene.lights->color.r, 255);
	assert_int_equal(scene.lights->color.g, 255);
	assert_int_equal(scene.lights->color.b, 255);

	assert_non_null(scene.objects);
	t_object *obj = scene.objects;
	assert_int_equal(obj->type, PLANE);
	t_plane *plane = obj->data;
	assert_float_equal(plane->coords.x, 0, 1e-6);
	assert_float_equal(plane->coords.y, 0, 1e-6);
	assert_float_equal(plane->coords.z, 0, 1e-6);
	assert_float_equal(plane->normal.x, 0, 1e-6);
	assert_float_equal(plane->normal.y, 1.0, 1e-6);
	assert_float_equal(plane->normal.z, 0, 1e-6);
	assert_int_equal(plane->color.r, 255);
	assert_int_equal(plane->color.g, 0);
	assert_int_equal(plane->color.b, 225);

	obj = obj->next;
	assert_int_equal(obj->type, SPHERE);
	t_sphere *sphere = obj->data;
	assert_float_equal(sphere->coords.x, 0, 1e-6);
	assert_float_equal(sphere->coords.y, 0, 1e-6);
	assert_float_equal(sphere->coords.z, 20, 1e-6);
	assert_float_equal(sphere->diameter, 20, 1e-6);
	assert_int_equal(sphere->color.r, 255);
	assert_int_equal(sphere->color.g, 0);
	assert_int_equal(sphere->color.b, 0);

	obj = obj->next;
	assert_int_equal(obj->type, CYLINDER);
	t_cylinder *cylinder = obj->data;
	assert_float_equal(cylinder->coords.x, 50.0, 1e-6);
	assert_float_equal(cylinder->coords.y, 0.0, 1e-6);
	assert_float_equal(cylinder->coords.z, 20.6, 1e-6);
	assert_float_equal(cylinder->orientation.x, 0, 1e-6);
	assert_float_equal(cylinder->orientation.y, 0, 1e-6);
	assert_float_equal(cylinder->orientation.z, 1.0, 1e-6);
	assert_float_equal(cylinder->diameter, 14.2, 1e-6);
	assert_float_equal(cylinder->height, 21.42, 1e-6);
	assert_int_equal(cylinder->color.r, 10);
	assert_int_equal(cylinder->color.g, 0);
	assert_int_equal(cylinder->color.b, 255);

	obj = obj->next;
	assert_int_equal(obj->type, ENDCAP);
	t_endcap *endcap1 = obj->data;
	assert_float_equal(endcap1->coords.x, 50.0, 1e-6);
	assert_float_equal(endcap1->coords.y, 0.0, 1e-6);
	assert_float_equal(endcap1->coords.z, 31.31, 1e-6);
	assert_float_equal(endcap1->normal.x, 0, 1e-6);
	assert_float_equal(endcap1->normal.y, 0, 1e-6);
	assert_float_equal(endcap1->normal.z, 1.0, 1e-6);
	assert_float_equal(endcap1->diameter, 14.2, 1e-6);
	assert_int_equal(endcap1->color.r, 10);
	assert_int_equal(endcap1->color.g, 0);
	assert_int_equal(endcap1->color.b, 255);

	obj = obj->next;
	assert_int_equal(obj->type, ENDCAP);
	t_endcap *endcap2 = obj->data;
	assert_float_equal(endcap2->coords.x, 50.0, 1e-6);
	assert_float_equal(endcap2->coords.y, 0.0, 1e-6);
	assert_float_equal(endcap2->coords.z, 9.89, 1e-6);
	assert_float_equal(endcap2->normal.x, 0, 1e-6);
	assert_float_equal(endcap2->normal.y, 0, 1e-6);
	assert_float_equal(endcap2->normal.z, -1.0, 1e-6);
	assert_float_equal(endcap2->diameter, 14.2, 1e-6);
	assert_int_equal(endcap2->color.r, 10);
	assert_int_equal(endcap2->color.g, 0);
	assert_int_equal(endcap2->color.b, 255);

	assert_null(obj->next);

	free(scene.ambient);
	free(scene.camera);
	free(scene.lights);
	free(plane);
	free(sphere);
	free(cylinder);
	free(endcap1);
	free(endcap2);
	free(scene.objects->next->next->next->next);
	free(scene.objects->next->next->next);
	free(scene.objects->next->next);
	free(scene.objects->next);
	free(scene.objects);
}

static void test_parse_file_comments(void **state) {
    (void)state;

	t_scene scene = {0};
    assert_int_equal(parse_file(&scene, "test_files/sample_with_comments.rt"), 0);

	assert_non_null(scene.ambient);
	assert_float_equal(scene.ambient->ratio, 0.2, 1e-6);
	assert_int_equal(scene.ambient->color.r, 255);
	assert_int_equal(scene.ambient->color.g, 255);
	assert_int_equal(scene.ambient->color.b, 255);

	assert_non_null(scene.camera);
	assert_float_equal(scene.camera->coords.x, -50, 1e-6);
	assert_float_equal(scene.camera->coords.y, 0, 1e-6);
	assert_float_equal(scene.camera->coords.z, 20, 1e-6);
	assert_float_equal(scene.camera->orientation.x, 0, 1e-6);
	assert_float_equal(scene.camera->orientation.y, 0, 1e-6);
	assert_float_equal(scene.camera->orientation.z, 1, 1e-6);
	assert_float_equal(scene.camera->fov_rad, deg_to_rad(70), 1e-6);

	assert_non_null(scene.lights);
	assert_float_equal(scene.lights->coords.x, -40, 1e-6);
	assert_float_equal(scene.lights->coords.y, 0, 1e-6);
	assert_float_equal(scene.lights->coords.z, 30, 1e-6);
	assert_float_equal(scene.lights->brightness, 0.7, 1e-6);
	assert_int_equal(scene.lights->color.r, 255);
	assert_int_equal(scene.lights->color.g, 255);
	assert_int_equal(scene.lights->color.b, 255);

	assert_non_null(scene.objects);
	t_object *obj = scene.objects;
	assert_int_equal(obj->type, PLANE);
	t_plane *plane = obj->data;
	assert_float_equal(plane->coords.x, 0, 1e-6);
	assert_float_equal(plane->coords.y, 0, 1e-6);
	assert_float_equal(plane->coords.z, 0, 1e-6);
	assert_float_equal(plane->normal.x, 0, 1e-6);
	assert_float_equal(plane->normal.y, 1.0, 1e-6);
	assert_float_equal(plane->normal.z, 0, 1e-6);
	assert_int_equal(plane->color.r, 255);
	assert_int_equal(plane->color.g, 0);
	assert_int_equal(plane->color.b, 225);

	obj = obj->next;
	assert_int_equal(obj->type, SPHERE);
	t_sphere *sphere = obj->data;
	assert_float_equal(sphere->coords.x, 0, 1e-6);
	assert_float_equal(sphere->coords.y, 0, 1e-6);
	assert_float_equal(sphere->coords.z, 20, 1e-6);
	assert_float_equal(sphere->diameter, 20, 1e-6);
	assert_int_equal(sphere->color.r, 255);
	assert_int_equal(sphere->color.g, 0);
	assert_int_equal(sphere->color.b, 0);

	obj = obj->next;
	assert_int_equal(obj->type, CYLINDER);
	t_cylinder *cylinder = obj->data;
	assert_float_equal(cylinder->coords.x, 50.0, 1e-6);
	assert_float_equal(cylinder->coords.y, 0.0, 1e-6);
	assert_float_equal(cylinder->coords.z, 20.6, 1e-6);
	assert_float_equal(cylinder->orientation.x, 0, 1e-6);
	assert_float_equal(cylinder->orientation.y, 0, 1e-6);
	assert_float_equal(cylinder->orientation.z, 1.0, 1e-6);
	assert_float_equal(cylinder->diameter, 14.2, 1e-6);
	assert_float_equal(cylinder->height, 21.42, 1e-6);
	assert_int_equal(cylinder->color.r, 10);
	assert_int_equal(cylinder->color.g, 0);
	assert_int_equal(cylinder->color.b, 255);

	obj = obj->next;
	assert_int_equal(obj->type, ENDCAP);
	t_endcap *endcap1 = obj->data;
	assert_float_equal(endcap1->coords.x, 50.0, 1e-6);
	assert_float_equal(endcap1->coords.y, 0.0, 1e-6);
	assert_float_equal(endcap1->coords.z, 31.31, 1e-6);
	assert_float_equal(endcap1->normal.x, 0, 1e-6);
	assert_float_equal(endcap1->normal.y, 0, 1e-6);
	assert_float_equal(endcap1->normal.z, 1.0, 1e-6);
	assert_float_equal(endcap1->diameter, 14.2, 1e-6);
	assert_int_equal(endcap1->color.r, 10);
	assert_int_equal(endcap1->color.g, 0);
	assert_int_equal(endcap1->color.b, 255);

	obj = obj->next;
	assert_int_equal(obj->type, ENDCAP);
	t_endcap *endcap2 = obj->data;
	assert_float_equal(endcap2->coords.x, 50.0, 1e-6);
	assert_float_equal(endcap2->coords.y, 0.0, 1e-6);
	assert_float_equal(endcap2->coords.z, 9.89, 1e-6);
	assert_float_equal(endcap2->normal.x, 0, 1e-6);
	assert_float_equal(endcap2->normal.y, 0, 1e-6);
	assert_float_equal(endcap2->normal.z, -1.0, 1e-6);
	assert_float_equal(endcap2->diameter, 14.2, 1e-6);
	assert_int_equal(endcap2->color.r, 10);
	assert_int_equal(endcap2->color.g, 0);
	assert_int_equal(endcap2->color.b, 255);

	assert_null(obj->next);

	free(scene.ambient);
	free(scene.camera);
	free(scene.lights);
	free(plane);
	free(sphere);
	free(cylinder);
	free(endcap1);
	free(endcap2);
	free(scene.objects->next->next->next->next);
	free(scene.objects->next->next->next);
	free(scene.objects->next->next);
	free(scene.objects->next);
	free(scene.objects);
}

// ---- Runner ----
int main(void) {
	const struct CMUnitTest parsing[] = {
		cmocka_unit_test(test_null_list_ptr),
		cmocka_unit_test(test_add_to_empty_list),
		cmocka_unit_test(test_add_to_non_empty_list),
		cmocka_unit_test(test_add_multiple),
		cmocka_unit_test(test_new_cylinder_success),
		cmocka_unit_test(test_new_cylinder_invalid_args),
		cmocka_unit_test(test_new_cylinder_orientation_zero),
		cmocka_unit_test(test_valid_extension),
		cmocka_unit_test(test_invalid_extension),
		cmocka_unit_test(test_no_extension),
		cmocka_unit_test(test_long_filename_with_rt),
		cmocka_unit_test(test_extension_rt_in_middle),
		cmocka_unit_test(test_invalid_longer_extension),
		cmocka_unit_test(test_invalid_longer_extension_rt_end),
		cmocka_unit_test(test_only_extension),
		cmocka_unit_test(test_parse_file_normal),
		cmocka_unit_test(test_parse_file_comments),
	};
	return cmocka_run_group_tests(parsing, NULL, NULL);
}

