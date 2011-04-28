#ifndef KANOMI_PROVIDER_HPP_
#define KANOMI_PROVIDER_HPP_

#include <Kanomi_mpl.hpp>

namespace kanomi {

template <class FIELD>
struct provides_field {
  template <class IMPL>
  struct apply {
    typedef typename is_same<typename IMPL::FieldT, FIELD>::type type;
  };
};

template <class M, class FieldT>
struct provider_of_field {
  typedef typename M::SequenceT S;
  typedef provides_field<FieldT> selector;
  typedef typename bf::result_of::find_if<S, selector >::type I_type;
  typedef typename bf::result_of::value_of<I_type>::type type;
};

template <class TAG>
struct provides_tag {
  template <class IMPL>
  struct apply {
    typedef typename is_same<typename IMPL::TagT, TAG>::type type;
  };
};

template <class M, class TagT>
struct provider_of_tag {
  typedef typename M::SequenceT S;
  typedef provides_tag<TagT> selector;
  typedef typename bf::result_of::find_if<S, selector >::type I_type;
  typedef typename bf::result_of::value_of<I_type>::type type;
};

} // namespace kanomi

#endif /* KANOMI_PROVIDER_HPP_ */
