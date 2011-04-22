#ifndef KANOMI_SCALARFIELD_HPP_
#define KANOMI_SCALARFIELD_HPP_

#include <Kanomi_ModelNames.hpp>
#include <Kanomi_Named.hpp>
#include <Kanomi_Stencils.hpp>
#include <string>
#include <Teuchos_ParameterList.hpp>

namespace kanomi {

template <class FIELD, class MODEL, class STENCIL>
struct ScalarField {
  typedef FIELD FieldT;
  typedef MODEL ModelT;
  typedef STENCIL StencilT;

  typedef bf::nil PrereqsT;

  ScalarField() : name(FieldT::name() + " (" + ModelT::name() + ")") {
    const ScalarT zero(0);
    for(int i=0; i < num_points; ++i)
      values[i] = zero;
  }

  template <class M>
  void setup(M & m, Teuchos::RCP<Teuchos::ParameterList> plist) {
    //const ScalarT val = plist->sublist(name,true).get<ScalarT>("value");
    const ScalarT val = 1.111;
    for(int i=0; i < num_points; ++i)
      values[i] = val;
    std::cout << "setup " << name << std::endl;
  }

  void evaluate() {
    std::cout << "Hello from " << name
        << " (model: " << ModelT::name() << ") "
        << " with value = " << values[0]
        << " x " << num_points
        << std::endl;
  }
  static const int num_points = StencilT::num_points;
  ScalarT values[num_points];
  std::string name;
};

} // namespace kanomi

#endif /* KANOMI_SCALARFIELD_HPP_ */
