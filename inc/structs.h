//generics

typedef struct s_vector3
{
	float x;
	float y;
	float z;
} t_vector3;

typedef struct s_color
{
	int r;
	int g;
	int b;
} t_color;

//scene objects

typedef struct s_ambient
{
	float ratio;
	t_color color;
} t_ambient;

typedef struct s_camera
{
	t_vector3	coords;
	t_vector3	orientation;
	int			fov;
} t_camera;

typedef struct s_light
{
	t_vector3	coords;
	float		brightness;
	t_color		color;
} t_light;

typedef struct s_sphere
{
	t_vector3	coords;
	float		diameter;
	t_color		color;
} t_sphere;

typedef struct s_plane
{
	t_vector3	coords;
	t_vector3	orientation;
	t_color		color;
} t_plane;

typedef struct s_cylinder
{
	t_vector3	coords;
	t_vector3	orientation;
	float		diameter;
	float		height;
	t_color		color;
} t_cylinder;