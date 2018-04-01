## Solar System
Project created within Computer Graphic laboratory at the MiNI Faculty (WUT). SolarSystem is an application that allows you to create and modificate your own Solar System. It is written in C++ and use OpenGL (GLFW). GUI written with [imgui](https://github.com/ocornut/imgui). [Icosahedron](https://github.com/caosdoar/spheres) algorithm is used to create sphere meshes. To simplify job with vectors and matrices was used [glm](https://glm.g-truc.net/0.9.8/index.html) library.

This project had several purposes:
* create `Sun` (luminous sphere at the center rotating on its axis) and `planets` (a few spheres rotating on its axis and revolves around the Sun)
* create `three cameras`: fixed; fixed, following planet; on planet
* functions which calculate `View Matrix`, `Projection Matrix` and `Perspective Matrix` could not be taken from OpenGL built-in functions
* implement `Gouraud` and `Phong` interpolation methods and `Phong` and `Blinn-Phong` reflection models



![qwe26](https://user-images.githubusercontent.com/29755810/38177051-61fdebe0-35fa-11e8-9bde-29717608c366.gif)

## Usage
**Camera:** 
* move with WASD
* change view direction: move mouse while holding down its right key
* zoom in and zoom out with mouse wheel

**Using GUI you can:** 
- add new planet
- delete planet
- change planet's colour, radius, velocity and scale


## Gallery
### Shading models
You can choose between [Gouraud shading](https://en.wikipedia.org/wiki/Gouraud_shading) (on the left) and [Phong shading](https://en.wikipedia.org/wiki/Phong_shading) (on the right). Both models are implemented using GLSL.
![gouraudphong_shading](https://user-images.githubusercontent.com/29755810/38175278-7d2523cc-35da-11e8-891c-f84385c6e82d.png)
Additionally [flat shading](https://en.wikipedia.org/wiki/Shading#Flat_shading) was implemented.
![flat](https://user-images.githubusercontent.com/29755810/38175911-f6d4d88e-35e4-11e8-9f02-4661decb97f7.png)

### Lighting models
You can switch between [Phong](https://en.wikipedia.org/wiki/Phong_reflection_model) (on the left) and [Blinn-Phong](https://en.wikipedia.org/wiki/Blinn%E2%80%93Phong_shading_model) (on the right) lighting models. Both these models you can combine with Gouraud shading and Phong shading.
![p_bp_lighting](https://user-images.githubusercontent.com/29755810/38175732-612ed350-35e1-11e8-9a21-9be36f11dfbe.png)
