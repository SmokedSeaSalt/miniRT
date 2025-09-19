#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <stdint.h>
#include <inttypes.h>
#include <cmocka.h>

#include "structs.h"
#include "parsing.h"
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
	char *args[] = {"c", "0","0","0", "0","1","0", "10.5", "20.2", "255","255","255", NULL};

	int res = new_cylinder_struct(&scene, args);
	assert_int_equal(res, 0);
	assert_non_null(scene.objects);
	t_object *obj = scene.objects;
	assert_int_equal(obj->type, CYLINDER);
	t_cylinder *cyl = (t_cylinder *)obj->data;
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
	char *args[] = {"c", "0","0","0", "0","0","0", "10", "20", "255","255","255", NULL};

	int res = new_cylinder_struct(&scene, args);
	assert_int_equal(res, 1);
	assert_null(scene.objects);
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
	};
	return cmocka_run_group_tests(parsing, NULL, NULL);
}

