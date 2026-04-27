# Argus Retina

![C++](https://img.shields.io/badge/C%2B%2B-23-00599c)
![CMake](https://img.shields.io/badge/build-CMake-064f8c)
![CTest](https://img.shields.io/badge/tests-CTest-lightgrey)

Argus Retina is the native C++ engine for Argus. It owns deterministic media/security primitives, public native contracts, capability reporting, and trusted artifacts consumed by higher layers.

## Architecture at a Glance

Retina is core-first: public contracts live in `include/`, implementation lives in `src/`, and tests verify the stable contract surface without turning the repo into an Android app or backend.

```text
argus-retina/
├── include/argus/retina/  public engine and contract headers
├── src/                   private C++ implementation
├── tests/                 CTest-backed native contract checks
├── CMakeLists.txt         build/test target wiring
├── CMakePresets.json      configure/build/test presets
├── vcpkg.json             dependency manifest
└── docs/                  project and Cortex contract references
```

## Getting Started

### Requirements

- CMake 3.26 or newer for the preset flow; use a newer CMake if your installed Visual Studio generator requires it.
- A C++23-capable Windows/MSVC toolchain.
- Visual Studio Developer Command Prompt or initialized MSVC/Windows SDK paths.
- Ninja and `VCPKG_ROOT` for the preset flow.

### Configure, Build, and Test

```bash
cmake --preset windows-debug
cmake --build --preset build-windows-debug
ctest --preset test-windows-debug
```

Release preset:

```bash
cmake --preset windows-release
cmake --build --preset build-windows-release
ctest --preset test-windows-release
```

Plain-shell fallback when Ninja/vcpkg is unavailable but Visual Studio is installed. Replace the generator string with one listed by `cmake --help` on your machine if needed:

```bash
cmake -S . -B out/build/verification-vs -G "Visual Studio 18 2026" -A x64 -DBUILD_TESTING=ON
cmake --build out/build/verification-vs --config Debug --target argus_retina_contract_test
ctest --test-dir out/build/verification-vs -C Debug --output-on-failure
```

## Project Navigation

| Need | File / directory |
|---|---|
| Active work plan | `PLAN.md` |
| Local agent rules | `AGENTS.md` |
| Product/architecture plan | `docs/project-plan.md` |
| Retina/Cortex contract | `docs/retina-cortex-contract.md` |
| Public engine API | `include/argus/retina/retina_engine.hpp` |
| Versioned contract types | `include/argus/retina/retina_contract.hpp` |
| Implementation | `src/retina_engine.cpp` |
| Contract tests | `tests/retina_contract_test.cpp` |

## Technology Stack

- **C++23** for typed, deterministic native primitives.
- **CMake** for portable build orchestration.
- **vcpkg manifest mode** for dependency governance when dependencies become justified.
- **CTest** for build-system-native contract verification.

## Contribution Rules

- Read `PLAN.md` before multi-step native work and update it when scope or verification changes.
- Keep public API in `include/argus/retina/`; keep private implementation in `src/`.
- Add dependencies only through `vcpkg.json` with phase justification, license review, wrapper boundary, and testability plan.
- Do not put Android UI, Spring web handlers, business orchestration, raw secret exposure, or unsafe buffers here.
- Never commit `out/`, build trees, generated binaries, local IDE caches, or toolchain-specific temporary files.
