# miniRT 🌟

A ray tracer written in C using MiniLibX

## Showcase

![Spheres](screenshots/spheres.png)
*Basic spheres with lighting and shadows*

![Checkerboard Pattern](screenshots/checkerboard.png)
*Checkerboard texture mapping*

![Bump Mapping](screenshots/bump_map_texture.png)
*Bump mapping for surface detail*

![Multi-colored Lighting](screenshots/multi_colored_light.png)
*Multiple colored light sources*

## Features

- **3D Objects**: Spheres, planes, and cylinders
- **Lighting**: Full Phong lighting model with ambient, diffuse, and specular reflection
- **Camera**: Configurable position and orientation
- **Texture Mapping**: UV mapping, bump mapping, and checkerboard patterns
- **Lighting**: Multiple light sources with colored lighting support
- **Scene Files**: Parse `.rt` scene description files


# Setup

clone this repository\
cd into repository\
make

# Running

./miniRT [Filename].rt

# Setup unit testing

cd into root of repository
make setup_test