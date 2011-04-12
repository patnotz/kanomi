#ifndef KANOMI_MODELS_THERMALCONDUCTIVITY_HPP_
#define KANOMI_MODELS_THERMALCONDUCTIVITY_HPP_

#include <Kanomi_Model.hpp>
#include <Kanomi_FieldNames.hpp>
#include <Kanomi_ConstantScalar.hpp>
#include <Kanomi_ScalarField.hpp>
#include <boost/fusion/container.hpp>

namespace bf = boost::fusion;

namespace kanomi {

template <class STENCIL>
struct Model<field::THERMAL_CONDUCTIVITY, STENCIL> {
  typedef field::THERMAL_CONDUCTIVITY FieldT;
  typedef STENCIL StencilT;
  typedef bf::list<
      ScalarField<field::THERMAL_CONDUCTIVITY,model::FIELD_DATA,StencilT>,
      ConstantScalar<field::THERMAL_CONDUCTIVITY,model::CONSTANT,StencilT>
  > list;
};



} // namespace kanomi

#endif /* KANOMI_MODELS_THERMALCONDUCTIVITY_HPP_ */
