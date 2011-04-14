#ifndef USER_CONFIG_HPP_
#define USER_CONFIG_HPP_

#include <Kanomi_Factory.hpp>

// Example user "input file" used to select components at compile time

// Choose which collections of models to include
#include <Kanomi_Factory_ThermalConductivity.hpp>

namespace kanomi {

// Enable selected models
ENABLE_MODEL(field::THERMAL_CONDUCTIVITY,model::POLYNOMIAL);

} // namespace kanomi

#endif /* USER_CONFIG_HPP_ */
