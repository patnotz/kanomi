#ifndef KANOMI_MANAGER_HPP_
#define KANOMI_MANAGER_HPP_

#include <boost/fusion/algorithm.hpp>
#include <boost/fusion/container.hpp>
#include <Teuchos_ParameterList.hpp>
#include <Kanomi_mpl.hpp>
#include <Kanomi_DoSetup.hpp>
#include <Kanomi_DoEvaluate.hpp>
#include <Kanomi_Factory.hpp>
#include <Kanomi_provider.hpp>
#include <Kanomi_OutputGraphviz.hpp>
#include <Kanomi_TypeInfo.hpp>

namespace bf = boost::fusion;

namespace kanomi {

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

  void dump_graph(std::ostream & os) {
    OutputGraphviz<ManagerT> output_graphviz(os);
    bf::for_each(seq,output_graphviz);
  }

  template <class IMPL>
  IMPL & get() {
    return *bf::find<IMPL>(seq);
  }

  template <class FIELD>
  ScalarT * get_values() {
    typedef typename provider_of_field<ManagerT,FIELD>::type ImplT;
    return *bf::find<ImplT>(seq).values;
  }

  SequenceT seq;
  Teuchos::RCP<Teuchos::ParameterList> plist;
};

} // namespace kanomi

#endif /* KANOMI_MANAGER_HPP_ */
