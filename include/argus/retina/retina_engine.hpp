#pragma once

#include "argus/retina/retina_contract.hpp"

namespace argus::retina {

class RetinaEngine {
public:
    [[nodiscard]] static const char* name() noexcept;
    [[nodiscard]] static const char* engineVersion() noexcept;
    [[nodiscard]] static const char* contractVersion() noexcept;
    [[nodiscard]] static CapabilityProbeResponse capabilityProbe() noexcept;
};

}  // namespace argus::retina
