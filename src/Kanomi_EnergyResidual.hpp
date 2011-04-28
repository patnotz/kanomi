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
    typedef typename provider_of_field<M,ThermalCondT>::type ThermCondPT;
    typedef typename provider_of_field<M,GradTempT>::type GradTempPT;
    typedef typename provider_of_field<M,GradBasisFunctionT>::type GradBasisFunctionPT;
    typedef typename provider_of_field<M,QuadWeightT>::type QuadWeightPT;
    typedef typename provider_of_field<M,DetjT>::type DetjPT;

    thermCond = m.template get<ThermCondPT>().values;
    gradTemp = m.template get<GradTempPT>().values;
    gradBasisFunction = m.template get<GradBasisFunctionPT>().values;
    quadWeight = m.template get<QuadWeightPT>().values;
    detj = m.template get<DetjPT>().values;

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
