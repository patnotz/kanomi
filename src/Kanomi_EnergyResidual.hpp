#ifndef KANOMI_ENERGYRESIDUAL_HPP_
#define KANOMI_ENERGYRESIDUAL_HPP_

#include <Kanomi_FieldNames.hpp>
#include <Kanomi_mpl.hpp>
#include <Kanomi_Tag.hpp>

namespace kanomi {

template <class STENCIL>
struct EnergyResidual {
  typedef field::ENERGY_RESIDUAL FieldT;
  typedef STENCIL StencilT;
  typedef Tag<FieldT,StencilT> TagT;

  typedef typename StencilT::TopologyT TopologyT;

  typedef Tag<field::THERMAL_CONDUCTIVITY,StencilT> ThermalCondT;
  typedef Tag<field::GRAD_TEMPERATURE,StencilT> GradTempT;
  typedef Tag<field::GRAD_BASIS_FUNCTION,StencilT> GradBasisFunctionT;
  typedef Tag<field::QUADRATURE_WEIGHTS,StencilT> QuadWeightT;
  typedef Tag<field::DETJ,StencilT> DetjT;

  typedef
      bf::cons< ThermalCondT,
      bf::cons< GradTempT,
      bf::cons< GradBasisFunctionT,
      bf::cons< QuadWeightT,
      bf::cons< DetjT > > > > > PrereqsT;

  EnergyResidual() : name(FieldT::name()) {
    const ScalarT zero(0);
    for(int i=0; i < num_nodes; ++i)
      values[i] = zero;
  }

  template <class M>
  void setup(M & m, Teuchos::RCP<Teuchos::ParameterList> plist) {

    thermCond = m.template get_values<ThermalCondT>();
    gradTemp = m.template get_values<GradTempT>();
    gradBasisFunction = m.template get_values<GradBasisFunctionT>();
    quadWeight = m.template get_values<QuadWeightT>();
    detj = m.template get_values<DetjT>();

    for(int i=0; i < num_nodes; ++i) {
      values[i] = 3.14159;
    }
    std::cout << "setup " << name << std::endl;
  }

  void evaluate() {
    std::cout << "Hello from " << name
        << " with value = " << values[0]
        << " x " << num_nodes
        << std::endl;
  }
  static const int num_nodes = TopologyT::num_nodes;
  static const int num_points = StencilT::num_points;
  static const int spatial_dimension = StencilT::spatial_dimension;
  ScalarT values[num_nodes];
  ScalarT * thermCond;
  ScalarT * gradTemp;
  ScalarT * gradBasisFunction;
  ScalarT * quadWeight;
  ScalarT * detj;
  std::string name;
};

} // namespace kanomi

#endif /* KANOMI_ENERGYRESIDUAL_HPP_ */
