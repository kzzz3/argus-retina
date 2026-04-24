# ARGUS RETINA KNOWLEDGE BASE

## OVERVIEW
`argus-retina` is the native C++ engine. It owns reusable low-level media and security primitives plus deterministic trusted outputs for other layers.

## STRUCTURE
```text
argus-retina/
├── CMakeLists.txt
├── CMakePresets.json
├── vcpkg.json
├── include/argus/retina/
├── src/
└── docs/
```

## WHERE TO LOOK
| Task | Location | Notes |
|------|----------|-------|
| Build entry | `CMakeLists.txt` | Defines `argus_retina_engine` static library |
| Configure/build presets | `CMakePresets.json` | `windows-debug`, `windows-release`, matching build presets |
| Public API | `include/argus/retina/retina_engine.hpp`, `include/argus/retina/retina_contract.hpp` | Header surface consumed externally |
| Implementation | `src/retina_engine.cpp` | Private engine implementation |
| Project intent/contracts | `docs/project-plan.md`, `docs/retina-cortex-contract.md` | Core-first and contract constraints |

## COMMANDS
```bash
# On Windows, run these from a Visual Studio Developer Command Prompt or after VsDevCmd.bat initializes MSVC/Windows SDK paths.
cmake --preset windows-debug
cmake --build --preset build-windows-debug
cmake --preset windows-release
cmake --build --preset build-windows-release
```

## CONVENTIONS
- Keep this project core-first: reusable native engine logic in C++, thin adapters outside.
- Public interface belongs under `include/argus/retina/`; implementation belongs under `src/`.
- Keep versioned request/result contract types in `retina_contract.hpp`; keep engine lifecycle/API entry points in `retina_engine.hpp`.
- Add dependencies only through `vcpkg.json` and only with concrete justification.
- Preserve deterministic, typed request/result boundaries described in the docs.
- Keep the native surface small and dependency-disciplined until a phase goal justifies expansion.

## ANTI-PATTERNS
- Do not turn this into a second Android app or a second cloud backend.
- Do not leak internal implementation details, unsafe buffers, or raw secret material across boundaries.
- Do not put Compose/UI logic, Spring web handlers, or business orchestration logic here.
- Do not blur the boundary between public API (`include/`) and implementation (`src/`).

## TESTING
- No explicit test target or test harness was found in the current CMake project.
- If adding tests later, document the harness clearly rather than implying one already exists.

## NOTES
- `docs/project-plan.md` specifies C++23, CMake, vcpkg manifest mode, Windows-first setup, and future Android NDK/server-host portability.
- `docs/retina-cortex-contract.md` is the authoritative contract guidance for versioned request/result schemas, error code rules, and security boundaries.
- Plain shells may fail to link on Windows if `kernel32.lib` and SDK paths are unavailable; initialize the Visual Studio build environment before configuring/building.
- Current source surface is small enough that project-root guidance is sufficient; do not split into deeper child guides yet.
