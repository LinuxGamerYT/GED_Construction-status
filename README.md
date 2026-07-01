# Game Engine Dev DoomGamer edition

A custom game engine built from scratch to learn graphics programming, engine architecture, and game development fundamentals.

> **Current Status:** 🚧 Early Development

## Features

### Current
- ✅ Project setup
- ✅ Window creation
- ✅ Application loop

### Planned
- Rendering system
- Input handling
- Event system
- Entity Component System (ECS)
- Asset manager
- Camera system
- Physics
- Audio
- UI system
- Scene management
- Scripting support

---

## Project Goals

This project is a learning-focused game engine created to better understand how modern game engines work internally.

The engine will be developed incrementally, starting with:
1. Opening a window
2. Rendering graphics
3. Handling user input
4. Managing scenes and entities
5. Building a complete rendering pipeline

---

## Project Structure

```
GameEngine/
├── src/
│   ├── main.cpp
│   └── ...
├── include/
├── assets/
├── build/
├── CMakeLists.txt
└── README.md
```

---

## Building

### Requirements

- C++20 (or your chosen standard)
- CMake 3.20+
- A C++ compiler
  - MSVC
  - GCC
  - Clang

### Build

```bash
git clone <repository-url>
cd GameEngine

mkdir build
cd build

cmake ..
cmake --build .
```

---

## Current Progress

- [x] Initialize project
- [ ] Open a window
- [ ] Handle window events
- [ ] Clear screen
- [ ] Render a triangle
- [ ] Load shaders
- [ ] Draw meshes
- [ ] Camera system
- [ ] Scene system

---

## Roadmap

### Phase 1
- Window creation
- Game loop
- Logging
- Timing

### Phase 2
- Graphics API integration
- Renderer
- Shader system
- Texture loading

### Phase 3
- ECS
- Asset manager
- Input system

### Phase 4
- Physics
- Audio
- UI
- Editor

---

## Technologies

- C++
- CMake
- (Graphics API: OpenGL)
- GLFW / SDL (if used)

---

## Learning Objectives

This project is intended to explore:

- Engine architecture
- Graphics programming
- Memory management
- Rendering pipelines
- Multithreading
- Resource management
- Mathematics for graphics

---

## License

This project is licensed under the MIT License.
