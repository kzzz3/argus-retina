#pragma once

#include "argus/retina/retina_contract.hpp"

namespace argus::retina {

// Small public entry point for native capability discovery. Methods return
// process-owned values and are noexcept so adapters can probe Retina before
// enabling optional Lens/Cortex integrations.
class RetinaEngine {
public:
    [[nodiscard]] static const char* name() noexcept;
    [[nodiscard]] static const char* engineVersion() noexcept;
    [[nodiscard]] static const char* contractVersion() noexcept;
    [[nodiscard]] static CapabilityProbeResponse capabilityProbe() noexcept;
};

}  // namespace argus::retina
