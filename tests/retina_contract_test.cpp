#include "argus/retina/retina_engine.hpp"

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <string>
#include <string_view>

namespace {

void require(bool condition, std::string_view message) {
    if (!condition) {
        std::cerr << "Contract test failed: " << message << '\n';
        std::exit(1);
    }
}

void verifyEnumNames() {
    require(std::string(argus::retina::contractStatusName(argus::retina::ContractStatus::Ok)) == "OK", "OK status name");
    require(std::string(argus::retina::contractStatusName(argus::retina::ContractStatus::Error)) == "ERROR", "error status name");
    require(std::string(argus::retina::errorCodeName(argus::retina::ErrorCode::None)) == "NONE", "none error code name");
    require(std::string(argus::retina::errorCodeName(argus::retina::ErrorCode::ContractVersionUnsupported)) == "CONTRACT_VERSION_UNSUPPORTED", "contract version error code name");
    require(std::string(argus::retina::errorCodeName(argus::retina::ErrorCode::AssetNotFound)) == "ASSET_NOT_FOUND", "asset missing error code name");
    require(std::string(argus::retina::errorCodeName(argus::retina::ErrorCode::UnsupportedInputType)) == "UNSUPPORTED_INPUT_TYPE", "input type error code name");
    require(std::string(argus::retina::errorCodeName(argus::retina::ErrorCode::NativeValidationFailed)) == "NATIVE_VALIDATION_FAILED", "native validation error code name");
    require(std::string(argus::retina::errorCodeName(argus::retina::ErrorCode::SigningArtifactUnavailable)) == "SIGNING_ARTIFACT_UNAVAILABLE", "signing artifact error code name");
    require(std::string(argus::retina::capabilityFeatureName(argus::retina::CapabilityFeature::CapabilityProbe)) == "CAPABILITY_PROBE", "capability probe feature name");
    require(std::string(argus::retina::capabilityFeatureName(argus::retina::CapabilityFeature::VisualParse)) == "VISUAL_PARSE", "visual parse feature name");
    require(std::string(argus::retina::capabilityFeatureName(argus::retina::CapabilityFeature::AudioPreprocess)) == "AUDIO_PREPROCESS", "audio preprocess feature name");
    require(std::string(argus::retina::capabilityFeatureName(argus::retina::CapabilityFeature::SecureSigning)) == "SECURE_SIGNING", "secure signing feature name");
    require(std::string(argus::retina::buildProfileName(argus::retina::BuildProfile::Debug)) == "DEBUG", "debug build profile name");
    require(std::string(argus::retina::buildProfileName(argus::retina::BuildProfile::Release)) == "RELEASE", "release build profile name");
}

void verifyEnvelopeDefaults() {
    const argus::retina::RequestEnvelope request;
    require(request.contractVersion == argus::retina::kRetinaContractVersion, "request envelope contract version default");

    const argus::retina::ResponseEnvelope response;
    require(response.contractVersion == argus::retina::kRetinaContractVersion, "response envelope contract version default");
    require(response.status == argus::retina::contractStatusName(argus::retina::ContractStatus::Ok), "response envelope status default");
    require(response.errorCode == argus::retina::errorCodeName(argus::retina::ErrorCode::None), "response envelope error code default");
}

}  // namespace

int main() {
    verifyEnumNames();
    verifyEnvelopeDefaults();

    const auto probe = argus::retina::RetinaEngine::capabilityProbe();

    require(std::string(argus::retina::RetinaEngine::name()) == "argus-retina", "engine name");
    require(std::string(argus::retina::RetinaEngine::engineVersion()) == "0.1.0", "engine version");
    require(probe.envelope.contractVersion == argus::retina::kRetinaContractVersion, "capability probe contract version");
    require(probe.engineVersion == argus::retina::RetinaEngine::engineVersion(), "capability probe engine version");
    require(probe.envelope.status == argus::retina::contractStatusName(argus::retina::ContractStatus::Ok), "capability probe status");
    require(probe.envelope.errorCode == argus::retina::errorCodeName(argus::retina::ErrorCode::None), "capability probe error code");
    require(std::ranges::find(
                probe.supportedFeatures,
                argus::retina::capabilityFeatureName(argus::retina::CapabilityFeature::CapabilityProbe)
            ) != probe.supportedFeatures.end(), "capability probe feature is advertised");

    return 0;
}
