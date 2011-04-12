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
