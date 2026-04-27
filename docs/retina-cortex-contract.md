# Argus Retina ↔ Argus Cortex Contract Draft

## 1. Purpose

This contract defines the stable boundary between **Argus Retina** and **Argus Cortex**.

- **Retina** exposes deterministic native primitives and trusted result artifacts.
- **Cortex** consumes those artifacts to make policy, orchestration, and persistence decisions.

This document exists so the two repositories can evolve separately without becoming loosely specified.

---

## 2. Design Rules

- Retina must expose **versioned, deterministic** request/result schemas.
- Retina must not leak internal implementation details, unsafe buffers, or raw secret material.
- Cortex owns business authorization and policy; Retina only returns structured native outputs.
- All Retina outputs must be suitable for storage in Cortex audit records.

---

## 3. Ownership Split

### Retina owns
- native media/security primitives
- deterministic request/result structs
- capability reporting
- secure artifact generation
- stable native error code emission

### Cortex owns
- orchestration and retries
- persistence and audit
- business authorization
- policy checks
- cloud workflow integration

---

## 4. Contract Categories

## 4.1 Capability Probe

### Response fields
- `engineVersion`
- `contractVersion`
- `supportedFeatures[]`
- `platform`
- `buildProfile`

Purpose: let Cortex negotiate what this Retina build can safely do.

---

## 4.2 QR / Visual Parse Job

### Request fields
- common envelope: `jobId`, `contractVersion`, `traceId`, `requestedAt`, `requester`
- `inputType`
- `assetReference`
- `expectedFormat`

### Response fields
- common envelope: `jobId`, `contractVersion`, `completedAt`, `status`, `errorCode`, `errorMessage`
- `parsedPayload`
- `confidence`
- `evidenceReferences[]`

---

## 4.3 Audio Preprocess / VAD Job

### Request fields
- common envelope: `jobId`, `contractVersion`, `traceId`, `requestedAt`, `requester`
- `assetReference`
- `sampleRateHz`
- `channelCount`
- `segmentPolicy`

### Response fields
- common envelope: `jobId`, `contractVersion`, `completedAt`, `status`, `errorCode`, `errorMessage`
- `segmentRanges[]`
- `vadScore`
- `recommendedUpload`

---

## 4.4 Secure Signing / Payment Support Job

### Request fields
- common envelope: `jobId`, `contractVersion`, `traceId`, `requestedAt`, `requester`
- `operationType`
- `canonicalPayload`
- `payloadHash`

### Response fields
- common envelope: `jobId`, `contractVersion`, `completedAt`, `status`, `errorCode`, `errorMessage`
- `artifactType`
- `artifactReference`
- `signatureMetadata`

Rules:
- return trusted artifacts only
- never return raw secret-bearing material

---

## 5. Required Common Envelope

Every Retina-facing contract should use the same top-level metadata envelope.

### Required request metadata
- `jobId`
- `contractVersion`
- `traceId`
- `requestedAt`
- `requester`

### Required response metadata
- `jobId`
- `contractVersion`
- `completedAt`
- `status`
- `errorCode`
- `errorMessage`

---

## 6. Error Code Rules

- emit stable machine-readable `errorCode`
- keep `errorMessage` human-readable but secondary
- never rely on free text alone

### Example families
- `CONTRACT_VERSION_UNSUPPORTED`
- `ASSET_NOT_FOUND`
- `UNSUPPORTED_INPUT_TYPE`
- `NATIVE_VALIDATION_FAILED`
- `SIGNING_ARTIFACT_UNAVAILABLE`

---

## 7. Versioning Rules

- every request/response family must carry `contractVersion`
- incompatible changes require a new version
- Cortex must be able to reject unsupported versions early

---

## 8. Security Rules

- raw keys never cross the boundary
- native secure artifacts must be typed and auditable
- high-risk outputs must be deterministic enough for Cortex-side audit storage

---

## 9. Near-Term Implementation Checklist

- [x] define shared envelope structs in Retina headers
- [x] define capability probe contract payload
- [x] define QR/visual parse request/result structs
- [x] define audio preprocess/VAD request/result structs
- [x] define secure signing artifact request/result structs
- [x] define shared error code families
- [x] define baseline contract version constants and early-rejection fields
- [ ] implement active runtime negotiation/rejection behavior in adapters

---

## 10. Non-Goals

- this document does not define Lens JNI transport details
- this document does not define cloud business policy
- this document does not make Retina responsible for orchestration
