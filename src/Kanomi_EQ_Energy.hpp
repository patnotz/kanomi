#ifndef KANOMI_EQ_ENERGY_HPP_
#define KANOMI_EQ_ENERGY_HPP_

#include <Kanomi_EQ.hpp>
#include <Kanomi_Factory.hpp>
#include <Kanomi_FieldNames.hpp>
#include <Kanomi_GradScalarField.hpp>
#include <Kanomi_EnergyResidual.hpp>
#include <Kanomi_BasisFunction.hpp>
#include <Kanomi_Tag.hpp>

namespace kanomi {

template <class STENCIL>
struct Factory<Tag<field::TEMPERATURE, STENCIL> > :
    ScalarEQ<field::TEMPERATURE, STENCIL> {};

template <class STENCIL>
struct Factory< Tag<field::GRAD_TEMPERATURE, STENCIL> > {
  typedef field::GRAD_TEMPERATURE FieldT;
  typedef field::TEMPERATURE CoeffsT;
  typedef STENCIL StencilT;
  typedef Tag<FieldT,StencilT> TagT;
  typedef GradScalarField<FieldT,CoeffsT,model::FIELD_DATA,StencilT> ProviderT;
};

template <class STENCIL>
struct Factory<Tag<field::ENERGY_RESIDUAL, STENCIL> > {
  typedef field::ENERGY_RESIDUAL FieldT;
  typedef STENCIL StencilT;
  typedef Tag<FieldT,StencilT> TagT;
  typedef EnergyResidual<StencilT> ProviderT;
};

} // namespace kanomi

#endif /* KANOMI_EQ_ENERGY_HPP_ */
