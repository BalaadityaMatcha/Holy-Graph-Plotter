# C++ and OpenGL 8-Week Curriculum

This repository contains an intensive, progressive 8-week coding curriculum designed to build proficiency in modern C++, essential development tools, and 3D graphics programming using OpenGL. Currently completed till week 4.

## 📂 Project Structure

The project is split into separate directories for each week, each containing its own standalone `CMakeLists.txt` build configuration.

### Week 0: C++ Refresher (`week0_cpp_refresher`)
A foundational overview of modern C++ paradigms. 
* **Topics Covered:** References, RAII (Resource Acquisition Is Initialization), Smart Pointers (`std::unique_ptr`), Operator Overloading, Function Overloading, and Templates.
* **Explanation:** Ensures a solid grasp of memory management and modern C++ features necessary for handling complex OpenGL object states cleanly.

### Week 1: Essential Tools (`week1_tools`)
An introduction to the development toolchain used in C++ ecosystems.
* **Topics Covered:** Git, GDB, CMake, Make, and Sanitizers (AddressSanitizer).
* **Explanation:** Contains intentionally buggy code to practice finding out-of-bounds access and memory leaks using `gdb` and `-fsanitize=address`.

### Week 2: OpenGL Setup (`week2_opengl_setup`)
The classic "Hello Triangle" in the graphics world.
* **Topics Covered:** GLFW (Windowing), GLAD (Extension loading), GLM (Mathematics), and basic Shader generation (Vertex and Fragment shaders).
* **Explanation:** Sets up the core OpenGL context and graphics pipeline to render a single shape to the screen.

### Week 3: Transforms and Camera (`week3_transforms`)
Entering the 3D space.
* **Topics Covered:** Model/View/Projection matrices, 3D coordinates, and interactive camera systems.
* **Explanation:** Renders a 3D, multi-colored cube. Implements an `OrbitCamera` class that allows the user to rotate their perspective around the cube using the Arrow Keys.

### Week 4: Rubik's Cube (`week4_rubiks_cube`)
A culminating interactive 3D application.
* **Topics Covered:** Complex state management, hierarchical transformations, and keyboard input processing.
* **Explanation:** A visual Rubik's Cube composed of 27 individual "cubies". Users can orbit the camera around the structure and dynamically rotate individual faces (U, D, L, R, F, B).

---

## 🛠️ Building the Projects

All OpenGL-dependent projects (Weeks 2-4) utilize CMake's `FetchContent` to automatically download and link the required external libraries (`GLFW` and `GLM`). GLAD is pre-included in the `common/glad` directory.

### Prerequisites
* A modern C++ compiler supporting C++17 (e.g., GCC, Clang, or MSVC).
* [CMake](https://cmake.org/download/) (version 3.14 or higher).

### Build Instructions
To build any of the weekly projects, navigate to the specific week's directory and run CMake:

```bash
cd week3_transforms

# Configure the build and fetch dependencies
cmake -S . -B build

# Compile the project
cmake --build build
```

Once compiled, you can run the generated executable located inside the `build/` directory.

## 🎮 Controls
* **Week 3:** Use the **Arrow Keys** to orbit the camera around the cube. Press **ESC** to exit.
* **Week 4:** 
  * **Arrow Keys:** Orbit the camera around the Rubik's cube.
  * **Faces:** Press **U** (Up), **D** (Down), **L** (Left), **R** (Right), **F** (Front), and **B** (Back) to rotate the respective layers of the cube.
  * **ESC:** Exit the application.
