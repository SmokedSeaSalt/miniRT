
/// @brief union for adaptable vector operations
/// @param float v for +-*/ operations on vector	-> vec3_1.v - vec3_2.v
/// @param struct for x y z access					-> vec3.x
/// @param float array[4] for array like access 	-> vec3.array[1]
typedef union {
	float v __attribute__((vector_size(16)));
	struct { float x, y, z, w; };
	float array[4];
} t_vec3;

t_vec3	normalize_vec3(t_vec3 vec3);
