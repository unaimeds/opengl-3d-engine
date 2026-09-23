# OpenGL 3D Engine

3D rendering engine written in C++ using OpenGL 4.6.

## Features

- OBJ and other model loading with Assimp
- Textured 3D models
- Entity transformations
- Procedurally generated terrain mesh
- First-person camera controls
- GLSL shader management
- Multi-texture rendering

## Building

> [!IMPORTANT]  
> C++23-compatible compiler is required.

```
git clone --recurse-submodules https://github.com/unaimeds/opengl-3d-engine.git
cd opengl-3d-engine
```
```
cmake -S . -B build
cmake --build build
```
```
cd build
./opengl_3d_engine
```

## License

Project is licensed under GPL-3.0
