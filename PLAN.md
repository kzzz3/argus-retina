# Argus Retina Active Plan

## Project Goal

Argus Retina provides a small, deterministic C++ engine surface for native media/security primitives and trusted contract artifacts used by Lens and Cortex.

## Core Feature Breakdown

- [x] C++23 CMake project baseline with public headers and private implementation.
- [x] Engine capability probe and baseline contract version constants.
- [x] Shared request/result envelope structs for Retina-facing contracts.
- [x] QR/visual parse, audio preprocess/VAD, and secure signing request/result schemas.
- [x] CTest-backed native contract smoke and enum/envelope regression coverage.
- [ ] Active runtime negotiation and rejection behavior in adapters.
- [ ] Expanded contract tests for visual parse defaults, audio preprocess defaults, and secure signing artifacts.
- [ ] JNI bridge shape for Lens without leaking engine internals.
- [ ] Server-host adapter shape for Cortex verification or batch tasks.
- [ ] Dependency introduction rules for future OpenCV/WebRTC/crypto libraries.

## Technology Stack and Architecture Decisions

- **C++23**: expressive typed contracts and deterministic native implementation.
- **CMake 3.26+**: conventional native build/test orchestration.
- **vcpkg manifest mode**: explicit dependency governance.
- **CTest**: native tests are discoverable through CMake presets and fallback build directories.

Dependencies remain empty until a phase requires them and the plan records justification, license, wrapper, and testing impact.

## Project Structure Plan

```text
argus-retina/
├── include/argus/retina/  public contract/API surface
├── src/                   private engine implementation
├── tests/                 contract tests
├── docs/                  architecture and Cortex contract references
├── CMakeLists.txt         target/test wiring
├── CMakePresets.json      preset workflows
└── vcpkg.json             dependency manifest
```

## Development Phases and Milestones

### Phase 1 — MVCV: Native Contract Core
- [x] Static library target exists.
- [x] Public headers define engine and contract surfaces.
- [x] CTest contract executable runs.

### Phase 2 — Stage 1 Native Support
- [x] Capability probe and deterministic contract defaults.
- [x] Request/result schemas for visual, audio, and secure signing job families.
- [ ] Adapter negotiation/rejection behavior.
- [ ] Expanded contract default tests.

### Phase 3 — Bridge Readiness
- [ ] JNI-safe Lens bridge design.
- [ ] Cortex server-host adapter design.
- [ ] Stable versioning and error-code compatibility policy.

### Phase 4 — Stage 2 Native Primitives
- [ ] Frame quality/visual parse primitives.
- [ ] VAD/audio slicing primitives.
- [ ] Secure signing artifact implementation with secret-safe boundaries.

## Mandatory M-R-E-A Cycle

1. **Modify**: make the smallest native-scope change.
2. **Review/Evaluate**: check public/private boundary, determinism, error codes, memory safety, and contract versioning.
3. **Document**: update this plan plus README/docs when APIs, presets, dependencies, or contract semantics change.
4. **Cleanup**: remove stale build artifacts from source control and run CMake/CTest verification.

## Verification Gates

| Change type | Required verification |
|---|---|
| Public headers or contract types | Configure, build `argus_retina_contract_test`, run CTest |
| CMake/preset changes | `cmake --list-presets`, configure/build/test the affected preset or documented fallback |
| Implementation changes | Build and run CTest for Debug; add Release when optimization behavior matters |
| Dependency changes | Verify `vcpkg.json`, configure through preset, document phase/license/wrapper/testability rationale |
| Docs-only | Read changed docs and verify commands against `CMakePresets.json` / `CMakeLists.txt` |

## Risk Register

- Presets require Ninja and `VCPKG_ROOT`; plain shells may need the Visual Studio generator fallback.
- Windows linking can fail without initialized MSVC/Windows SDK paths.
- Premature dependencies can bloat build complexity before contracts justify them.
- JNI/server adapters can leak implementation details if public contracts are not kept narrow.
- Secret-bearing workflows must never expose raw material across Lens/Cortex boundaries.

## Documentation Rules

- `README.md` explains how to onboard, configure, build, and test Retina.
- `PLAN.md` tracks active native work and verification gates.
- `docs/project-plan.md` remains the long-form product/architecture blueprint.
- `docs/retina-cortex-contract.md` remains the authoritative cross-repo contract explanation.

## Verification Log

| Date | Scope | Command / method | Result |
|---|---|---|---|
| 2026-04-27 | Documentation workflow refresh | Read `AGENTS.md`, `docs/project-plan.md`, `docs/retina-cortex-contract.md`, `CMakePresets.json`, `vcpkg.json`, and verified referenced paths exist | PASS for this documentation pass |
