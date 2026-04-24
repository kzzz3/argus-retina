#include "argus/retina/retina_engine.hpp"

namespace argus::retina {

const char* RetinaEngine::name() noexcept {
    return "argus-retina";
}

const char* RetinaEngine::engineVersion() noexcept {
    return "0.1.0";
}

const char* RetinaEngine::contractVersion() noexcept {
    return kRetinaContractVersion;
}

CapabilityProbeResponse RetinaEngine::capabilityProbe() noexcept {
    CapabilityProbeResponse response;
    response.engineVersion = engineVersion();
    response.envelope.contractVersion = contractVersion();
    response.platform = "windows";
#ifdef NDEBUG
    response.buildProfile = buildProfileName(BuildProfile::Release);
#else
    response.buildProfile = buildProfileName(BuildProfile::Debug);
#endif
    response.supportedFeatures = {
        capabilityFeatureName(CapabilityFeature::CapabilityProbe),
    };
    return response;
}

}  // namespace argus::retina
