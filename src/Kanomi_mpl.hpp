#ifndef KANOMI_MPL_HPP_
#define KANOMI_MPL_HPP_

#include <boost/fusion/container.hpp>

namespace bf = boost::fusion;

namespace kanomi {

typedef bf::nil nil;

template <class SEQ, class TYPE>
struct contains;

template <class TYPE, class TAIL>
struct contains<bf::cons<TYPE, TAIL>, TYPE > {
  typedef boost::mpl::true_ type;
};

template <class HEAD, class TAIL, class TYPE>
struct contains<bf::cons<HEAD,TAIL>, TYPE> {
  typedef typename contains<TAIL, TYPE>::type type;
};

template <class TYPE>
struct contains<bf::nil, TYPE> {
  typedef boost::mpl::false_ type;
};

template <class T, class S>
struct unique_cons {
  template <class SS, class TT, class exists> struct unique_cons_impl;
  template <class SS, class TT>
  struct unique_cons_impl<SS,TT,boost::mpl::true_> {
    typedef SS type;
  };
  template <class SS, class TT>
  struct unique_cons_impl<SS,TT,boost::mpl::false_> {
    typedef bf::cons<TT, SS> type;
  };

  typedef typename contains<S, T>::type S_has_T;
  typedef typename unique_cons_impl<S,T,S_has_T>::type type;
};

} // namespace kanomi

#endif /* KANOMI_MPL_HPP_ */
