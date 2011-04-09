#ifndef KANOMI_SCALARFIELD_HPP_
#define KANOMI_SCALARFIELD_HPP_

#include <Kanomi_Stencils.hpp>
#include <string>
#include <Teuchos_ParameterList.hpp>

namespace kanomi {

template <class FN, class PTS>
struct ScalarField {
  typedef FN FieldNameT;
  typedef PTS PointsT;

  ScalarField() : name(FieldNameT::name()) {
    const ScalarT zero(0);
    for(int i=0; i < num_points; ++i)
      values[i] = zero;
  }

  ScalarField(const ScalarT val) : name(FieldNameT::name()) {
    for(int i=0; i < num_points; ++i)
      values[i] = val;
  }

  template <class M>
  void setup(M & m, Teuchos::RCP<Teuchos::ParameterList> plist) {
    std::cout << "setup " << name << std::endl;
  }

  void evaluate() {
    std::cout << "Hello from " << name
        << " with value = " << values[0]
        << " x " << num_points
        << std::endl;
  }
  static const int num_points = PointsT::num_points;
  ScalarT values[num_points];
  std::string name;
};



} // namespace kanomi

#endif /* KANOMI_SCALARFIELD_HPP_ */
