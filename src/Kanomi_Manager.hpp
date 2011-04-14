#ifndef KANOMI_MANAGER_HPP_
#define KANOMI_MANAGER_HPP_

#include <boost/fusion/algorithm.hpp>
#include <boost/fusion/container.hpp>
#include <boost/fusion/sequence.hpp>
#include <Teuchos_ParameterList.hpp>
#include <Kanomi_TypeInfo.hpp>

namespace bf = boost::fusion;

namespace kanomi {

template <class M>
struct DoSetup {
  typedef M ManagerT;
  DoSetup(
      ManagerT & m,
      Teuchos::RCP<Teuchos::ParameterList> p) :
        manager(m), plist(p) {}
  template<class T>
  void operator()(T & t) const {
    t.setup(manager, plist);
  }
  ManagerT & manager;
  Teuchos::RCP<Teuchos::ParameterList> plist;
};

struct DoEvaluate {
  template <class T>
  void operator()(T & t) const {
    t.evaluate();
  }
};

template <class A, class B>
struct is_same {
  typedef boost::mpl::false_ type;
};
template <class A>
struct is_same<A,A> {
  typedef boost::mpl::true_ type;
};
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

template <class S>
struct Manager {
  typedef S SequenceT;
  typedef Manager<SequenceT> ManagerT;

  Manager(Teuchos::RCP<Teuchos::ParameterList> p) :
    seq(SequenceT()), plist(p) {}

  void run() {
    DoSetup<ManagerT> do_setup(*this,plist);
    DoEvaluate do_evaluate;
    bf::for_each(seq,do_setup);
    bf::for_each(seq,do_evaluate);
  }

  template <class T>
  Manager<SequenceT> & set(T t) {
    *bf::find<T>(seq) = t;
    return *this;
  }

  template <class T>
  T & get() {
    return *bf::find<T>(seq);
  }

  SequenceT seq;
  Teuchos::RCP<Teuchos::ParameterList> plist;
};

} // namespace kanomi

#endif /* KANOMI_MANAGER_HPP_ */
