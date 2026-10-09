# Cuby Programming Language (v0.1)

Cuby is a modularized programming language architecture based on C, designed to provide a clean, CLI-driven environment that simplifies project creation, modular gem packaging, and cross-platform compilation across Unix, Linux, and Termux ecosystems.

## 🧬 Why Cuby? (The Architectural Concept)

Traditional C projects often suffer from naming conflicts, messy directory structures, and complex Makefiles that are hard to maintain. Cuby solves this by introducing:
- **The `ngen` Matrix (Nucleus of Gems)**: Organizes compilation layers and file extensions into a structured matrix (`.cgen`, `.hgen`, `.sgen`, and cross-combinations).
- **Directory Isolation**: Prevents file collisions by separating source workspaces cleanly using custom flags.
- **Unified Packaging**: Flattens modular gem files into a single optimized `codigo_gerado.c` for robust compilation via `clang`.

## 📂 Project Structure

- `cuby`: The official command-line interface (CLI) script.
- `build.sh`: Automated build and packaging engine.
- `install.sh`: Universal installation script for global system access.
- `ngen/`: Default directory housing core gem files.

## 🚀 Usage & CLI Help

### 1. Initializing and Building a Project
You can specify custom directories and gem files using the CLI flags:
```bash
./cuby -dir meu_projeto -name main.
Or use the automated build engine:
./build.sh -dir meu_projeto -name main.cgen
2. Global Installation
​To install the cuby command globally in your terminal (/usr/local/bin or Termux bin path):
./install.sh
Once installed, you can run cuby from anywhere in your system:
cuby -dir meu_projeto -name main.cgen

