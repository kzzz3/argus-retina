#include "argus/retina/retina_engine.hpp"

#include <algorithm>
#include <cstdlib>
#include <string>

namespace {

void require(bool condition) {
    if (!condition) {
        std::exit(1);
    }
}

}  // namespace

int main() {
    const auto probe = argus::retina::RetinaEngine::capabilityProbe();

    require(std::string(argus::retina::RetinaEngine::name()) == "argus-retina");
    require(std::string(argus::retina::RetinaEngine::engineVersion()) == "0.1.0");
    require(probe.envelope.contractVersion == argus::retina::kRetinaContractVersion);
    require(probe.engineVersion == argus::retina::RetinaEngine::engineVersion());
    require(probe.envelope.status == argus::retina::contractStatusName(argus::retina::ContractStatus::Ok));
    require(probe.envelope.errorCode == argus::retina::errorCodeName(argus::retina::ErrorCode::None));
    require(std::ranges::find(
                probe.supportedFeatures,
                argus::retina::capabilityFeatureName(argus::retina::CapabilityFeature::CapabilityProbe)
            ) != probe.supportedFeatures.end());

    return 0;
}
