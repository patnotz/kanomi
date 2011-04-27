#ifndef KANOMI_OUTPUTGRAPHVIZ_HPP_
#define KANOMI_OUTPUTGRAPHVIZ_HPP_

#include <iosfwd>

namespace bf = boost::fusion;

namespace kanomi {

template <class M>
struct OutputGraphviz {
  typedef M ManagerT;
private:
  template <class MANAGER, class FROM, class PREREQ_LIST>
  struct OutputGraphvizEdge;
  template <class MANAGER, class FROM, class FieldT, class StencilT, class TAIL>
  struct OutputGraphvizEdge<MANAGER, FROM, bf::cons< bf::pair<FieldT, StencilT>, TAIL> > {
    static void write(std::ostream & os) {
      os << "  " << FROM::name() << " -> " << FieldT::name() << ";" << std::endl;
      OutputGraphvizEdge<MANAGER,FROM,TAIL>::write(os);
    }
  };
  template <class MANAGER, class FROM>
  struct OutputGraphvizEdge<MANAGER,FROM,nil> {
    static void write(std::ostream & os) {}
  };
  std::ostream & ostream;
public:
  OutputGraphviz(std::ostream & os) : ostream(os) {}
  template<class T>
  void operator()(T & t) const {
    typedef typename T::FieldT FieldT;
    typedef typename T::PrereqsT PrereqsT;
    ostream << "  " << FieldT::name() << " [shape=box,style=filled];" << std::endl;
    OutputGraphvizEdge<M,FieldT,PrereqsT>::write(ostream);
  }
};

} // namespace kanomi

#endif /* KANOMI_OUTPUTGRAPHVIZ_HPP_ */
