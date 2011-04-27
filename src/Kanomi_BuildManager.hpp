#ifndef KANOMI_BUILDMANAGER_HPP_
#define KANOMI_BUILDMANAGER_HPP_

#include <Kanomi_Manager.hpp>
#include <Kanomi_Factory.hpp>
#include <Kanomi_mpl.hpp>

namespace kanomi {

template <class ROOTS>
struct BuildManager {
private:
  template <class S, class R, class P> struct Build;

  // The end of recursion
  template <class S>
  struct Build<S, nil, nil> {
    typedef S SequenceT;
  };

  // Pull in another required type
  template <class S, class RH, class RT>
  struct Build<S, bf::cons<RH, RT>, nil> {
    typedef typename RH::PrereqsT PrereqsT;
    typedef typename unique_cons<RH, S>::type NextS;
    typedef typename Build<NextS, RT, PrereqsT>::SequenceT SequenceT;
  };

  // Process a prereq
  template <class S, class R, class PH, class PT>
  struct Build<S, R, bf::cons<PH,PT> > {

    // Pull off the top prereq
    typedef typename PH::first_type FieldT;
    typedef typename PH::second_type StencilT;

    // Find the type that supplies this prereq
    typedef typename Factory<FieldT, StencilT>::ProviderT PrereqProviderT;

    // add the prereq provider to the front of the list and recurse
    typedef typename unique_back_cons<PrereqProviderT, R>::type NextR;
    typedef typename Build<S, NextR, PT>::SequenceT SequenceT;
  };

public:
  typedef typename Build<nil,ROOTS,nil>::SequenceT SequenceT;
  typedef Manager<SequenceT> ManagerT;
};

} // namespace kanomi

#endif /* KANOMI_BUILDMANAGER_HPP_ */
