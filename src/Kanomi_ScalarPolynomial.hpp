#ifndef KANOMI_SCALARPOLYNOMIAL_HPP_
#define KANOMI_SCALARPOLYNOMIAL_HPP_

#include <Kanomi_ModelNames.hpp>
#include <Kanomi_Named.hpp>
#include <Kanomi_Manager.hpp>
#include <Kanomi_Stencils.hpp>
#include <string>
#include <vector>
#include <sstream>
#include <Teuchos_ParameterList.hpp>

namespace kanomi {

template <class FIELD, class MODEL, class STENCIL, class VARIABLE>
struct ScalarPolynomial {
  typedef FIELD FieldT;
  typedef MODEL ModelT;
  typedef STENCIL StencilT;
  typedef VARIABLE VariableT;

  typedef bf::cons<
      bf::pair<VariableT, StencilT>
  > PrereqsT;

  ScalarPolynomial() :
    name(FieldT::name() + " (" + ModelT::name() + ")"), order(0) {
    const ScalarT zero(0);
    for(int i=0; i < num_points; ++i)
      values[i] = zero;
  }

  template <class M>
  void setup(M & m, Teuchos::RCP<Teuchos::ParameterList> plist) {
    std::cout << "setup " << name << std::endl;

    typedef typename provider_of_field<M,VariableT>::type ProviderT;
    variable = m.template get<ProviderT>().values;

    Teuchos::ParameterList & my_plist = plist->sublist(name,true);
    order = my_plist.get<int>("order");
    c.resize(order);
    const ScalarT default_of_zero = 0;
    for(int i=0; i < order+1; ++i) {
      std::ostringstream os;
      os << "C_" << i;
      std::string c_i = os.str();
      c[i] = my_plist.get<ScalarT>(c_i, default_of_zero);
      std::cout << "C[" << i << "] = " << c[i] << std::endl;
    }
  }

  void evaluate() {
    for(int point=0; point < num_points; ++point) {
      ScalarT val = c[order];
      const ScalarT var = variable[point];
      for(int n=order-1; n >= 0; --n) {
        val = var * val + c[n];
      }
      values[point] = val;
    }
    std::cout << "Hello from " << name
        << " (model: " << ModelT::name() << ") "
        << " with value = " << values[0]
        << " with var = " << variable[0]
        << " x " << num_points
        << std::endl;
  }
  static const int num_points = StencilT::num_points;
  ScalarT values[num_points];
  ScalarT * variable;
  int order;
  std::string name;
  std::vector<ScalarT> c;
};

} // namespace kanomi

#endif /* KANOMI_SCALARPOLYNOMIAL_HPP_ */
