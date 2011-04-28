#ifndef KANOMI_BASISFUNCTION_HPP_
#define KANOMI_BASISFUNCTION_HPP_

#include <Kanomi_ScalarField.hpp>
#include <Kanomi_Factory.hpp>
#include <Kanomi_FieldNames.hpp>
#include <Kanomi_ModelNames.hpp>
#include <Kanomi_Tag.hpp>

namespace kanomi {

template <class STENCIL>
struct Factory<Tag<field::BASIS_FUNCTION,STENCIL> > {
  typedef field::BASIS_FUNCTION FieldT;
  typedef STENCIL StencilT;
  typedef Tag<FieldT,StencilT> TagT;
  // FIXME:
  typedef ScalarField<FieldT,model::FEM,StencilT> ProviderT;
};

template <class STENCIL>
struct Factory<Tag<field::GRAD_BASIS_FUNCTION,STENCIL> > {
  typedef field::GRAD_BASIS_FUNCTION FieldT;
  typedef STENCIL StencilT;
  typedef Tag<FieldT,StencilT> TagT;
  // FIXME:
  typedef ScalarField<FieldT,model::FEM,StencilT> ProviderT;
};

template <class STENCIL>
struct Factory<Tag<field::QUADRATURE_WEIGHTS,STENCIL> > {
  typedef field::QUADRATURE_WEIGHTS FieldT;
  typedef STENCIL StencilT;
  typedef Tag<FieldT,StencilT> TagT;
  // FIXME:
  typedef ScalarField<FieldT,model::FEM,StencilT> ProviderT;
};

template <class STENCIL>
struct Factory<Tag<field::DETJ,STENCIL> > {
  typedef field::DETJ FieldT;
  typedef STENCIL StencilT;
  typedef Tag<FieldT,StencilT> TagT;
  // FIXME:
  typedef ScalarField<FieldT,model::FEM,StencilT> ProviderT;
};

} // namespace kanomi

#endif /* KANOMI_BASISFUNCTION_HPP_ */
