# Argus Retina Technical Plan

## 1. Repository Positioning

Argus Retina is the native engine of the system. It exists to hold the low-level C++ capabilities that are too performance-sensitive, too security-sensitive, or too platform-specific to live safely in Kotlin or Spring Boot.

This repository must stay **core-first**: the engine owns reusable media and security primitives, while JNI glue and backend-host adapters stay thin. Retina should never become a second Android app or a second cloud backend.

## 2. Product Strategy Split

Retina also follows the same two-stage evolution, but its responsibilities are different from Cortex and Lens.

### Stage 1 — WeChat-like Baseline Support
Retina supports baseline messaging, media, and payment features only where native performance or isolation is justified:

- voice pipeline helpers
- media quality checks and normalization primitives
- QR or image parsing support primitives
- secure payment token preparation and signing substrate
- realtime media engine foundations for WebRTC integration

### Stage 2 — AI Glasses Enhancement Engine
Retina becomes the hard realtime and zero-trust engine behind wearable features:

- FPV frame filtering and quality gates
- VAD-based audio slicing
- sensor-adjacent local decision support hooks
- zero-trust visual payment signing flow
- native bridge for first-person RTC and local perception assists

## 3. Why Retina Exists

### Kotlin should not own
- zero-copy media processing
- low-level codec-adjacent pipelines
- secure key material workflows
- high-frequency frame rejection and audio gating
- reusable native routines that must also serve cloud-hosted adapters

### Spring Boot should not own
- device-local secure signing execution
- Android-side realtime camera/audio cleanup
- native realtime media primitives

## 4. Build and Tooling Direction

- **language**: C++23
- **build**: CMake
- **package/dependency management**: vcpkg manifest mode
- **Windows IDE target**: Visual Studio 2026
- **future portability target**: Android NDK bridge and optional server-side embedding

The repository should remain small and dependency-disciplined until each native dependency is justified by a concrete phase goal.

## 5. Internal Layering

### 5.1 Core types layer
- request/result structs
- version and capability reporting
- error categories and status codes
- deterministic payload schemas for Kotlin/Java and backend callers

### 5.2 Media primitives layer
- frame quality checks
- blur/shake heuristics
- QR/image parsing helpers
- sample/frame normalization hooks

### 5.3 Audio primitives layer
- audio segment windowing
- VAD integration and silence rejection
- encoding handoff boundaries

### 5.4 Security primitives layer
- transaction payload canonicalization
- signing request preparation
- secure buffer handling
- key access abstraction for platform keystore/TEE-backed flows

### 5.5 Bridge layer
- JNI adapter for Lens
- service-host adapter for Cortex-side native jobs
- test harness or CLI driver only for development validation later

## 6. Stage-Oriented Responsibility Split

## 6.1 Stage 1 — Baseline Native Support

Retina should help baseline WeChat-like features without taking over business logic.

### Primary Stage 1 concerns
- efficient voice-note preprocessing boundaries
- camera frame utility functions for scan-pay and media upload quality checks
- WebRTC-oriented native media foundation planning
- secure payment signing substrate for future scan-pay isolation

### Stage 1 boundaries
- message routing stays in Cortex
- payment orchestration stays in Cortex
- user confirmation UX stays in Lens
- Retina returns deterministic results and signatures only

## 6.2 Stage 2 — Wearable Enhancement Engine

### Primary Stage 2 concerns
- FPV frame filtering before network upload
- VAD-based speech fragment extraction
- QR and visual target detection support primitives
- native support for first-person stream source and realtime media path
- zero-trust visual payment token assembly after local user confirmation

### Stage 2 boundaries
- Retina may provide local decisions and scores, but policy still lives in Cortex
- Retina may generate secure artifacts, but user-visible flow remains in Lens
- Retina must not expose secret-bearing internals directly to Kotlin or cloud layers

## 7. Interface Contracts

### 7.1 Retina <-> Lens
- capability probe API
- image/frame analysis request/result schema
- audio segment preprocess request/result schema
- secure payment signing request/result schema
- JNI-safe status and error model

### 7.2 Retina <-> Cortex
- versioned job schema for server-hosted native tasks
- deterministic result payloads suitable for audit storage
- optional verification routines for signed device-side artifacts

## 8. Global Phase Mapping From Retina Perspective

### Pair A — Phase 1 / Phase 2
- **Phase 1 minimal support**: no heavy ownership yet; define engine surface and future contracts
- **Phase 2 primary support**: voice and image preprocessing primitives for baseline media messaging

### Pair B — Phase 3 / Phase 4
- **Phase 3 primary support**: native WebRTC/media engine foundation and bridge planning
- **Phase 4 primary**: FPV source handling, stream-path helpers, annotation-support metadata primitives

### Pair C — Phase 5 / Phase 6
- **Phase 5 primary**: OpenCV-like frame filtering, blur/shake rejection, VAD slicing, upload gating outputs
- **Phase 6 support**: provide structured edge outputs that improve cloud multimodal intent parsing

### Pair D — Phase 7 / Phase 8
- **Phase 7 support**: baseline scan-pay native parsing and secure payload preparation
- **Phase 8 primary**: zero-trust visual payment signing, biometric-gated secure operation bridge, deterministic token output

## 9. Dependency Strategy

Add dependencies only when a phase requires them and only through `vcpkg.json`.

Likely future candidates by purpose:

- **OpenCV** or similar for image/frame quality analysis
- **WebRTC native stack** for realtime media support
- **mbedtls** or equivalent for secure signing primitives

Each dependency must have:
- phase justification
- license review
- wrapper boundary
- testability plan

## 10. Security Model

- no raw secret exposure to Kotlin/UI layer
- secure buffers for sensitive material
- platform keystore / TEE abstraction instead of hardcoding a single environment
- signed outputs must be deterministic, timestamped, and contract-versioned
- all bridge APIs must use explicit typed request/result structures

## 11. Risks and Constraints

- WebRTC and image-processing dependencies can bloat native build complexity quickly
- Android bridge stability can be damaged by poor ABI/version governance
- zero-trust payment design fails if signing and UI confirmation are not cleanly separated
- Windows-first setup must remain compatible with future Android NDK integration

## 12. Non-Goals

- no business orchestration logic here
- no Compose or Android screen logic here
- no Spring Boot web handlers here
- no direct persistence of social graph or conversation state here

## 13. Immediate Next Design Tasks

1. define public capability and version structs in `include/`
2. define request/result contracts for frame filtering, audio slicing, and secure signing
3. define JNI bridge shape for Lens without leaking engine internals
4. define server-host adapter shape for Cortex verification or batch tasks
5. record the first dependency-introduction rules and approval checklist in docs
