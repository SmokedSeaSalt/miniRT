#include "math_inc.h"
#include <math.h>

t_vector3	normalize_vec3(t_vector3 vec3)
{
	float		length;
	t_vector3	result;

	length = sqrtf(vec3[0] * vec3[0] + vec3[1] * vec3[1] + vec3[2] * vec3[2]);
	if (length != 0.0f)
		result = vec3 / (t_vector3){length, length, length};
	else
		result = (t_vector3){0.0, 0.0, 0.0};
	return (result);
}
