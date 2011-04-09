#ifndef KANOMI_MANAGER_HPP_
#define KANOMI_MANAGER_HPP_

#include <boost/fusion/algorithm.hpp>
#include <boost/fusion/container.hpp>
#include <boost/fusion/sequence.hpp>
#include <Teuchos_ParameterList.hpp>
#include <Kanomi_TypeInfo.hpp>

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
    boost::fusion::for_each(seq,do_setup);
    boost::fusion::for_each(seq,do_evaluate);
  }

  template <class T>
  Manager<SequenceT> & set(T t) {
    *boost::fusion::find<T>(seq) = t;
    return *this;
  }

  template <class T>
  T & get() {
    return *boost::fusion::find<T>(seq);
  }
  SequenceT seq;
  Teuchos::RCP<Teuchos::ParameterList> plist;
};

#endif /* KANOMI_MANAGER_HPP_ */
