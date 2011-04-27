#ifndef KANOMI_EQ_HPP_
#define KANOMI_EQ_HPP_

#include <Kanomi_ScalarField.hpp>
#include <Kanomi_ModelNames.hpp>

namespace kanomi {

template <class FIELD, class STENCIL>
struct ScalarEQ {
  typedef FIELD FieldT;
  typedef STENCIL StencilT;
  typedef ScalarField<FieldT,model::FIELD_DATA,StencilT> ProviderT;
};

} // namespace kanomi

#endif /* KANOMI_EQ_HPP_ */
