#ifndef MANAGER_HPP_
#define MANAGER_HPP_

#include <boost/fusion/algorithm.hpp>
#include <boost/fusion/container.hpp>
#include <boost/fusion/sequence.hpp>
#include <Teuchos_ParameterList.hpp>
#include <typeinfo.hpp>

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
struct manager {
  typedef S SequenceT;
  typedef manager<SequenceT> ManagerT;

  manager(Teuchos::RCP<Teuchos::ParameterList> p) :
    seq(SequenceT()), plist(p) {}

  void run() {
    DoSetup<ManagerT> do_setup(*this,plist);
    DoEvaluate do_evaluate;
    boost::fusion::for_each(seq,do_setup);
    boost::fusion::for_each(seq,do_evaluate);
  }

  template <class T>
  manager<SequenceT> & set(T t) {
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

#endif /* MANAGER_HPP_ */
