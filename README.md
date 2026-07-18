# GED Engine

> A lightweight, modular 2D game engine built in C++ using OpenGL 3.3.

---

## 📌 Overview

**GED (Game Engine Development)** is an experimental real-time rendering engine focused on learning graphics programming, engine architecture, and systems design.

The goal is to build a clean, extensible foundation for 2D (and later 3D) applications while understanding how real game engines are structured internally.

---

## 🧭 Development Roadmap (12 Months)

### 🟢 Phase 1 — Foundation (Window + Loop + Rendering Setup)

**Goal:** Get a stable runtime window with a functioning render loop.

- Window creation (SDL / GLFW) ✅
- OpenGL context setup (3.3 core profile) ✅
- Main game loop ✅
- Event handling (keyboard, mouse, window close) ✅
- Delta time system (frame timing) ✅
- Screen clearing (render pipeline start) ✅
- Basic rendering (triangle / quad) ✅

**Result:**  
A running application that updates every frame and renders basic geometry.

---

### 🔵 Phase 2 — Rendering System

**Goal:** Build a reusable rendering abstraction layer.

- Shader compilation system (vertex/fragment) ⚠️ (50%)
- Texture loading (stb_image) ⚠️ (10%)
- Sprite rendering (2D quads) ⚠️ (25%)
- Transform system (position, rotation, scale) ❌
- 2D camera system (view/projection) ❌

**Result:**  
Engine can render textured, transformed objects in 2D space.

---

### 🟡 Phase 3 — Engine Architecture

**Goal:** Refactor into a modular engine core.

- Core Engine class (Init / Update / Shutdown) ❌
- Renderer module abstraction ⚠️ (5%)
- Input system wrapper ⚠️ (20%)
- Entity system (basic ECS or object model) ❌
- Scene management system ❌

**Result:**  
Clean separation between engine systems and application logic.

---

### 🟠 Phase 4 — Gameplay Systems

**Goal:** Enable real game development inside the engine.

- AABB collision detection ❌
- Basic physics (velocity, acceleration) ❌
- Asset management system (texture caching) ❌
- Sprite animation system ❌
- Simple UI system (buttons / text rendering) ❌

**Result:**  
Fully playable 2D prototypes (e.g., platformer or top-down game).

---

### 🔴 Phase 5 — Polish & Optimization

**Goal:** Improve performance and usability.

- Scene transitions ❌
- Debug overlay (FPS, logging) ❌
- Serialization (save/load system) ❌
- Particle system (optional) ❌
- Rendering optimization (batching, draw calls) ❌

**Result:**  
Stable engine capable of running complete small games.

---

### 🟣 Phase 6 — Final Application

**Goal:** Build a complete game using the engine.

Example project:
- doom 1993 ❌
- cookie clicker ❌

**Result:**  
End-to-end demonstration of the engine.

---

## ⚙️ Build Instructions

### Requirements

- C++17 or higher
- CMake 3.15+
- OpenGL 3.3 compatible GPU & drivers
- SDL2 or GLFW
- Windows / Linux (havent tested on mac)

---

### Build (Linux / Windows)

```bash
git clone https://github.com/LinuxGamerYT/GED_Construction-status.git
cd GED_Construction-status

mkdir build
cd build

make
make run
```

---

## 🚀 Project Goals

This engine is built to explore:

- Real-time rendering pipelines
- Low-level graphics programming
- Engine architecture patterns
- Memory and performance considerations
- Modular system design

---

## 🧠 Design Philosophy

GED is intentionally minimal and learning-focused.

It avoids:
- Over-engineering
- External abstraction layers that hide OpenGL
- Premature optimization

It prioritizes:
- Clarity
- Control
- Understanding core systems

---

## ⚠️ Status

This project is actively under development.

Expect frequent changes, refactors, and incomplete systems.

---

## 📄 License

This project is for educational purposes and portfolio development.
