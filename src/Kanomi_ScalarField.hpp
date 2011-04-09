#ifndef KANOMI_SCALARFIELD_HPP_
#define KANOMI_SCALARFIELD_HPP_

#include <Kanomi_Stencils.hpp>
#include <string>
#include <Teuchos_ParameterList.hpp>

namespace kanomi {

template <class PTS>
struct ScalarField {
  typedef PTS PointsT;
  ScalarField() : name("ScalarField") {
    for(int i=0; i < num_points; ++i)
      values[i] = 0;
  }
  ScalarField(const ScalarT val) : name("ScalarField") {
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
