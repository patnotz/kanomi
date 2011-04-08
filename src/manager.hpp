#ifndef MANAGER_HPP_
#define MANAGER_HPP_

#include <boost/fusion/algorithm.hpp>
#include <boost/fusion/container.hpp>
#include <boost/fusion/sequence.hpp>
#include <typeinfo.hpp>

template <class M>
struct DoSetup {
  typedef M ManagerT;
  DoSetup(ManagerT & m) : manager(m) {}
  template<class T>
  void operator()(T & t) const {
    t.setup(manager);
  }
  ManagerT & manager;
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

  manager() : seq(SequenceT()) {}

  void run() {
    DoSetup<ManagerT> do_setup(*this);
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
};

#endif /* MANAGER_HPP_ */
