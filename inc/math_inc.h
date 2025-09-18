//could be changed to:
//typedef struct __attribute__((aligned(16))) s_vector3
//add extra padding float and now able to do SIMD
typedef float	t_vector3 __attribute__((ext_vector_type(3)));

t_vector3	normalize_vec3(t_vector3 vec3);
