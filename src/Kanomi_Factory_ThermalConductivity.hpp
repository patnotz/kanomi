#ifndef KANOMI_MODELS_THERMALCONDUCTIVITY_HPP_
#define KANOMI_MODELS_THERMALCONDUCTIVITY_HPP_

#include <Kanomi_Factory.hpp>
#include <Kanomi_FieldNames.hpp>
#include <Kanomi_ConstantScalar.hpp>
#include <Kanomi_ScalarField.hpp>
#include <Kanomi_ModelProvider.hpp>
#include <Kanomi_ScalarPolynomial.hpp>
#include <boost/fusion/container.hpp>

namespace bf = boost::fusion;

namespace kanomi {

template <class STENCIL>
struct Factory<field::THERMAL_CONDUCTIVITY, STENCIL> {
  typedef field::THERMAL_CONDUCTIVITY FieldT;
  typedef STENCIL StencilT;
  typedef bf::list<
      ScalarField<FieldT,model::FIELD_DATA,StencilT>,
      ConstantScalar<FieldT,model::CONSTANT,StencilT>,
      ScalarPolynomial<FieldT,model::POLYNOMIAL,StencilT,field::TEMPERATURE>
  > list;
  typedef typename ModelProvider<list, FieldT>::ProviderT ProviderT;
};

} // namespace kanomi

#endif /* KANOMI_MODELS_THERMALCONDUCTIVITY_HPP_ */
