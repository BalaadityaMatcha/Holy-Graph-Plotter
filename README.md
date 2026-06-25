# C++ and OpenGL 8-Week Curriculum

---

## Overview

This repository contains an intensive, progressive 8-week coding curriculum designed to build proficiency in modern C++, essential development tools, and 3D graphics programming using OpenGL. The project progresses from a C++ refresher and development toolchain setup to building a fully interactive 3D Graph Plotter. Currently, the curriculum is completed up to Week 4.

---

## Week 0: C++ Refresher

**Core Concepts**

* References, RAII (Resource Acquisition Is Initialization), and Smart Pointers (`std::unique_ptr`)
* Operator Overloading, Function Overloading, and Templates

**Explanation**

* Ensures a solid grasp of memory management and modern C++ features necessary for handling complex OpenGL object states cleanly.

---

## Week 1: Essential Tools

**Key Topics**

* Git, GDB, CMake, Make
* Sanitizers (AddressSanitizer)

**Implementation & Analysis**

* Contains intentionally buggy code to practice finding out-of-bounds access and memory leaks
* Uses `gdb` and `-fsanitize=address` for debugging and memory safety verification

---

## Week 2: OpenGL Setup

**Problem Setup**

* Objective: Render the classic "Hello Triangle" in the graphics world

**Libraries & Initialization**

* GLFW for windowing and context creation
* GLAD for loading OpenGL extensions
* GLM for mathematics

**Graphics Pipeline**

* Sets up the core OpenGL context
* Implements basic Shader generation (Vertex and Fragment shaders) to render a single shape to the screen

---

## Week 3: Transforms and Camera

**Core Concepts**

* Entering the 3D space with Model, View, and Projection matrices
* 3D coordinates and depth testing

**Implementation & Rendering**

* Renders a 3D, multi-colored cube
* Implements an `OrbitCamera` class that allows the user to rotate their perspective around the cube using the mouse (click and drag)

---

## Week 4: Rubik's Cube

**Problem Setup**

* Objective: Build a culminating interactive 3D application representing a visual Rubik's Cube composed of 27 individual "cubies".

**Strategy Design**

* Complex state management and hierarchical transformations
* Keyboard input processing for interactive gameplay

**Controls & Evaluation**

* Users can orbit the camera around the structure dynamically using the mouse
* Users can dynamically rotate individual faces (U, D, L, R, F, B), with the `Shift` key reversing the rotation direction
* Press `Space` to reset the cube and camera to their initial states

---

## Summary

* Week 0 established foundational knowledge in modern C++ paradigms and memory management
* Week 1 introduced the essential development toolchain for C++ ecosystems, focusing on debugging and sanitizers
* Week 2 set up the core OpenGL graphics pipeline and rendered the first shape
* Week 3 expanded into 3D rendering with transformations and an interactive trackball camera
* Week 4 integrated previous concepts to build a fully interactive, state-managed 3D Rubik's Cube

Together, these stages demonstrate a progression from basic C++ tooling to building interactive, state-driven 3D graphical applications.

---

## 🛠️ Building the Projects

All OpenGL-dependent projects (Weeks 2-4) utilize CMake's `FetchContent` to automatically download and link the required external libraries (`GLFW` and `GLM`). GLAD is pre-included in the `common/glad` directory.

### Prerequisites
* A modern C++ compiler supporting C++17 (e.g., GCC, Clang, or MSVC).
* [CMake](https://cmake.org/download/) (version 3.14 or higher).
***Operating System**: Windows or Linux (macOS is not natively supported due to OpenGL Compatibility Profile constraints).
*GPU with support for **OpenGL 4.5 (Compatibility Profile)** or higher.

### Build Instructions
To build any of the weekly projects, navigate to the specific week's directory and run CMake:

```bash
cd Week 3

# Configure the build and fetch dependencies
cmake -B build

# Compile the project
cmake --build build
```

Once compiled, you can run the generated executable located inside the `build/` directory in the week's directory.

```bash
cd Week 3

# Run the executable
./build/executable
```

## 🎮 Controls
* **Camera (Week 3 & 4):** **Click and drag the left mouse button** to orbit the camera freely around the cube.
* **Rubik's Cube (Week 4):** 
  * **Faces:** Press **U** (Up), **D** (Down), **L** (Left), **R** (Right), **F** (Front), and **B** (Back) to rotate the respective layers of the cube clockwise.
  * **Shift:** Hold **Shift** while pressing a face key to reverse the rotation (counter-clockwise).
  * **Space:** Reset the Rubik's cube and camera to the starting state.
  * **ESC:** Exit the application.
