#ifndef KANOMI_GRADSCALARFIELD_HPP_
#define KANOMI_GRADSCALARFIELD_HPP_

#include <Kanomi_ModelNames.hpp>
#include <Kanomi_Named.hpp>
#include <Kanomi_Stencils.hpp>
#include <string>
#include <Teuchos_ParameterList.hpp>

namespace kanomi {

template <class FIELD, class COEFFS, class MODEL, class STENCIL>
struct GradScalarField {
  typedef FIELD FieldT;
  typedef COEFFS CoeffsT;
  typedef MODEL ModelT;
  typedef STENCIL StencilT;

  typedef bf::cons< bf::pair<CoeffsT,StencilT> > PrereqsT;

  GradScalarField() : name(FieldT::name() + " (" + ModelT::name() + ")") {
    const ScalarT zero(0);
    for(int i=0; i < size; ++i)
      values[i] = zero;
  }

  template <class M>
  void setup(M & m, Teuchos::RCP<Teuchos::ParameterList> plist) {
    typedef typename provider_of_field<M,CoeffsT>::type CoeffsPT;
    coeffs = m.template get<CoeffsPT>().values;
    const ScalarT val = 2.198;
    for(int i=0; i < size; ++i)
      values[i] = val;
    std::cout << "setup " << name << std::endl;
  }

  void evaluate() {
    std::cout << "Hello from " << name
        << " (model: " << ModelT::name() << ") "
        << " with value = " << values[0]
        << " x " << size
        << std::endl;
  }
  static const int num_points = StencilT::num_points;
  static const int spatial_dimension = StencilT::spatial_dimension;
  static const int size = num_points * spatial_dimension;
  ScalarT values[num_points*spatial_dimension];
  ScalarT * coeffs;
  std::string name;
};

} // namespace kanomi

#endif /* KANOMI_GRADSCALARFIELD_HPP_ */
