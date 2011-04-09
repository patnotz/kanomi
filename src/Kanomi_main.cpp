#include <iostream>
#include <Kanomi_FieldNames.hpp>
#include <Kanomi_Manager.hpp>
#include <Kanomi_ScalarField.hpp>
#include <Kanomi_Stencils.hpp>

using namespace kanomi;
using namespace std;
using namespace Teuchos;
namespace fusion = boost::fusion;

struct Base {
  Base(const string name_arg) :
    value(0), name(name_arg) {
  }
  ScalarT value;
  string name;
  void evaluate() {
    cout << "Hello from " << name << " with value = " << value << endl;
  }
};

struct A : public Base{
  A() : Base("A") {}
  template <class M>
  void setup(M & m, RCP<ParameterList> plist) {
    value = plist->sublist(name,true).get<ScalarT>("value");
    cout << "setup " << name << endl;
  }
};

struct B : public Base {
  B() : Base("B"), b(0) {}
  ScalarT b;
  template <class M>
  void setup(M & m, RCP<ParameterList> plist) {
    ScalarT a = m.template get<A>().value;
    b = plist->sublist(name,true).get<ScalarT>("value");
    value = a * b;
    cout << "setup B, a = " << a << endl;
  }
};

struct C : public Base {
  C() : Base("C") {}
  template <class M>
  void setup(M & m, RCP<ParameterList> plist) {
    value = plist->sublist(name,true).get<ScalarT>("value");
    cout << "setup " << name << endl;
  }
};

struct D : public Base {
  D() : Base("D") {}
  template <class M>
  void setup(M & m, RCP<ParameterList> plist) {
    value = plist->sublist(name,true).get<ScalarT>("value");
    cout << "setup " << name << endl;
  }
};

typedef ScalarField<TEMPERATURE,QUAD_Q4> E;

struct X;
struct Y;
typedef fusion::map<
    fusion::pair<X, fusion::list<C> >,
    fusion::pair<Y, fusion::list<D> >,
    fusion::pair<Y, fusion::list<E> > > opt;
typedef fusion::list<C,D,E> K_M;
template <class X> struct enabled {
  typedef enabled<X> type;
  static const bool value = false; };
template <> struct enabled<E> {
  typedef enabled<E> type;
  static const bool value = true; };
struct enabled_pred { template <class X> struct apply : enabled<X> {}; };

int main(int argc, char * argv[]) {
  RCP<ParameterList> plist = rcp(new ParameterList);

  ParameterList & p_a = plist->sublist("A");
  p_a.set<ScalarT>("value",9.13);
  ParameterList & p_b = plist->sublist("B");
  p_b.set<ScalarT>("value",2.5);
  ParameterList & p_c = plist->sublist("C");
  p_c.set<ScalarT>("value",7.3);
  ParameterList & p_d = plist->sublist("D");
  p_d.set<ScalarT>("value",10);
  ParameterList & p_temperature = plist->sublist("TEMPERATURE");
  p_temperature.set<ScalarT>("value",3.14159);

  typedef fusion::cons<A, fusion::cons<B, fusion::cons<C> > > Seq;
  Manager<Seq> m(plist);
  m.run();

  //typedef fusion::result_of::value_at_key<opt,Y>::type ys;
  //typedef fusion::result_of::begin<ys>::type yi;
  //typedef fusion::result_of::value_of<yi>::type X_type;
  typedef fusion::result_of::find_if<K_M, enabled_pred>::type KI_type;
  typedef fusion::result_of::value_of<KI_type>::type K_type;
  typedef fusion::cons<K_type, Seq> Seq2;
  Manager<Seq2> m2(plist);
  m2.run();

  return 0;
}
