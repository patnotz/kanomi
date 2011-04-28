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
  typedef typename StencilT::TopologyT TopologyT;

  typedef field::THERMAL_CONDUCTIVITY ThermalCondT;
  typedef field::GRAD_TEMPERATURE GradTempT;
  typedef field::GRAD_BASIS_FUNCTION GradBasisFunctionT;
  typedef field::QUADRATURE_WEIGHTS QuadWeightT;
  typedef field::DETJ DetjT;

  typedef
      bf::cons< Tag<ThermalCondT,StencilT>,
      bf::cons< Tag<GradTempT,StencilT>,
      bf::cons< Tag<GradBasisFunctionT,StencilT>,
      bf::cons< Tag<QuadWeightT,StencilT>,
      bf::cons< Tag<DetjT,StencilT> > > > > > PrereqsT;

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
