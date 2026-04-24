#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace argus::retina {

inline constexpr const char* kRetinaContractVersion = "argus.retina.contract.v1";

enum class ContractStatus : std::uint8_t {
    Ok = 0,
    Error = 1,
};

enum class ErrorCode : std::uint8_t {
    None = 0,
    ContractVersionUnsupported = 1,
    AssetNotFound = 2,
    UnsupportedInputType = 3,
    NativeValidationFailed = 4,
    SigningArtifactUnavailable = 5,
};

enum class CapabilityFeature : std::uint8_t {
    CapabilityProbe = 0,
    VisualParse = 1,
    AudioPreprocess = 2,
    SecureSigning = 3,
};

enum class BuildProfile : std::uint8_t {
    Debug = 0,
    Release = 1,
};

[[nodiscard]] inline constexpr const char* contractStatusName(ContractStatus status) noexcept {
    switch (status) {
        case ContractStatus::Ok:
            return "OK";
        case ContractStatus::Error:
            return "ERROR";
    }
    return "ERROR";
}

[[nodiscard]] inline constexpr const char* errorCodeName(ErrorCode code) noexcept {
    switch (code) {
        case ErrorCode::None:
            return "NONE";
        case ErrorCode::ContractVersionUnsupported:
            return "CONTRACT_VERSION_UNSUPPORTED";
        case ErrorCode::AssetNotFound:
            return "ASSET_NOT_FOUND";
        case ErrorCode::UnsupportedInputType:
            return "UNSUPPORTED_INPUT_TYPE";
        case ErrorCode::NativeValidationFailed:
            return "NATIVE_VALIDATION_FAILED";
        case ErrorCode::SigningArtifactUnavailable:
            return "SIGNING_ARTIFACT_UNAVAILABLE";
    }
    return "NATIVE_VALIDATION_FAILED";
}

[[nodiscard]] inline constexpr const char* capabilityFeatureName(CapabilityFeature feature) noexcept {
    switch (feature) {
        case CapabilityFeature::CapabilityProbe:
            return "CAPABILITY_PROBE";
        case CapabilityFeature::VisualParse:
            return "VISUAL_PARSE";
        case CapabilityFeature::AudioPreprocess:
            return "AUDIO_PREPROCESS";
        case CapabilityFeature::SecureSigning:
            return "SECURE_SIGNING";
    }
    return "CAPABILITY_PROBE";
}

[[nodiscard]] inline constexpr const char* buildProfileName(BuildProfile profile) noexcept {
    switch (profile) {
        case BuildProfile::Debug:
            return "DEBUG";
        case BuildProfile::Release:
            return "RELEASE";
    }
    return "DEBUG";
}

struct RequestEnvelope {
    std::string jobId;
    std::string contractVersion = kRetinaContractVersion;
    std::string traceId;
    std::string requestedAt;
    std::string requester;
};

struct ResponseEnvelope {
    std::string jobId;
    std::string contractVersion = kRetinaContractVersion;
    std::string completedAt;
    std::string status = contractStatusName(ContractStatus::Ok);
    std::string errorCode = errorCodeName(ErrorCode::None);
    std::string errorMessage;
};

struct CapabilityProbeResponse {
    ResponseEnvelope envelope;
    std::string engineVersion;
    std::vector<std::string> supportedFeatures;
    std::string platform;
    std::string buildProfile = buildProfileName(BuildProfile::Debug);
};

struct VisualParseRequest {
    RequestEnvelope envelope;
    std::string inputType;
    std::string assetReference;
    std::string expectedFormat;
};

struct VisualParseResponse {
    ResponseEnvelope envelope;
    std::string parsedPayload;
    double confidence = 0.0;
    std::vector<std::string> evidenceReferences;
};

struct AudioSegmentRange {
    std::uint32_t startMs = 0;
    std::uint32_t endMs = 0;
};

struct AudioPreprocessRequest {
    RequestEnvelope envelope;
    std::string assetReference;
    std::uint32_t sampleRateHz = 0;
    std::uint32_t channelCount = 0;
    std::string segmentPolicy;
};

struct AudioPreprocessResponse {
    ResponseEnvelope envelope;
    std::vector<AudioSegmentRange> segmentRanges;
    double vadScore = 0.0;
    bool recommendedUpload = false;
};

struct SignatureMetadataEntry {
    std::string algorithm;
    std::string keyReference;
    std::string signatureFormat;
};

struct CanonicalPayload {
    std::string format = "transaction.canonical.v1";
    std::string content;
};

struct SecureSigningRequest {
    RequestEnvelope envelope;
    std::string operationType;
    CanonicalPayload canonicalPayload;
    std::string payloadHash;
};

struct SecureSigningResponse {
    ResponseEnvelope envelope;
    std::string artifactType;
    std::string artifactReference;
    std::vector<SignatureMetadataEntry> signatureMetadata;
};

}  // namespace argus::retina
