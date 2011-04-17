#ifndef KANOMI_EQ_ENERGY_HPP_
#define KANOMI_EQ_ENERGY_HPP_

#include <Kanomi_EQ.hpp>
#include <Kanomi_Factory.hpp>
#include <Kanomi_FieldNames.hpp>

namespace kanomi {

template <class STENCIL>
struct Factory<field::TEMPERATURE, STENCIL> :
    ScalarEQ<field::TEMPERATURE, STENCIL> {};

} // namespace kanomi

#endif /* KANOMI_EQ_ENERGY_HPP_ */
