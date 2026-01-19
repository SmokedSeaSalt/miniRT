# miniRT 🌟

A ray tracer written in C using MLX42 - exploring the fundamentals of computer graphics and 3D rendering.

**Authors:** Mathijs Van Rijn & Edsard Grisel

## Showcase

![Spheres](screenshots/spheres.png)
*Basic spheres with lighting and shadows*

![Bump Mapping](screenshots/bump_map_texture.png)
*Bump mapping for surface detail*

![Multi-colored Lighting](screenshots/multi_colored_light.png)
*Multiple colored light sources*

![Checkerboard Pattern](screenshots/checkerboard.png)
*Checkerboard texture mapping*

## Features

- **3D Objects**: Spheres, planes, and cylinders
- **Lighting**: Full Phong lighting model with ambient, diffuse, and specular reflection
- **Camera**: Configurable position and orientation
- **Texture Mapping**: UV mapping, bump mapping, and checkerboard patterns
- **Lighting**: Multiple light sources with colored lighting support
- **Scene Files**: Parse `.rt` scene description files


# Setup

## Ubuntu/Linux

```bash
git clone <repository-url>
cd miniRT
make
```

## macOS (Apple Silicon)

```bash
git clone <repository-url>
cd miniRT
git checkout macos_demo
make
```

# Running
- Scenes can be found in the scenes folder
```bash
./miniRT [Filename].rt
```

# Key bindings
-	Arrow keys: Camera rotation
-	WASD: Camera translation

---
*Part of the 42 School curriculum*