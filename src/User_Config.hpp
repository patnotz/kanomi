#ifndef USER_CONFIG_HPP_
#define USER_CONFIG_HPP_

#include <Kanomi_Factory.hpp>
#include <Kanomi_Build.hpp>

// Example user "input file" used to select components at compile time

namespace kanomi {
// Declare selected models
ENABLE_MODEL(field::THERMAL_CONDUCTIVITY,model::POLYNOMIAL);
} // namespace kanomi

// Choose which collections of models to include
#include <Kanomi_Factory_ThermalConductivity.hpp>
#include <Kanomi_EQ_Energy.hpp>

namespace kanomi {

// For now, use this as a root-level dependency...
typedef typename Factory<field::ENERGY_RESIDUAL, QUAD_Q4>::ProviderT ResidP;
typedef bf::cons<ResidP> UserRootsT;

} // namespace kanomi

#endif /* USER_CONFIG_HPP_ */
