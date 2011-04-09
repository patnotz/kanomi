#include <iostream>
#include <Kanomi_Manager.hpp>
#include <Kanomi_Stencils.hpp>

using namespace std;
using namespace Teuchos;
namespace fusion = boost::fusion;

struct Base {
  Base(const int value_arg, const string name_arg) :
    value(value_arg), name(name_arg) {
  }
  Base(const Base & rhs) : value(rhs.value), name(rhs.name) {
    cout << "Base copy c-tor for " << name << endl;
  }
  int value;
  string name;
  void evaluate() {
    cout << "Hello from " << name << " with value = " << value << endl;
  }
};

struct A : public Base{
  A() : Base(0, "A") {}
  A(const int val) : Base(val, "A") {}
  template <class M>
  void setup(M & m, RCP<ParameterList> plist) {
    cout << "setup " << name << endl;
  }
};

struct B : public Base {
  B() : Base(0, "B"), b(0) {}
  B(const int val) : Base(val, "B"), b(val) {}
  int b;
  template <class M>
  void setup(M & m, RCP<ParameterList> plist) {
    int a = m.template get<A>().value;
    value = a * b;
    cout << "setup B, a = " << a << endl;
  }
};

struct C : public Base {
  C() : Base(0,"C") {}
  C(const int val) : Base(val, "C") {}
  template <class M>
  void setup(M & m, RCP<ParameterList> plist) {
    cout << "setup " << name << endl;
  }
};

struct D : public Base {
  D() : Base(0,"D") {}
  D(const int val) : Base(val, "D") {}
  template <class M>
  void setup(M & m, RCP<ParameterList> plist) {
    cout << "setup " << name << endl;
  }
};

template <class PTS>
struct E {
  typedef PTS PointsT;
  E() : name("E") {
    for(int i=0; i < num_points; ++i)
      values[i] = 0;
  }
  E(const ScalarT val) : name("E") {
    for(int i=0; i < num_points; ++i)
      values[i] = val;
  }
  template <class M>
  void setup(M & m, RCP<ParameterList> plist) {
    cout << "setup " << name << endl;
  }
  void evaluate() {
    cout << "Hello from " << name
        << " with value = " << values[0]
        << " x " << num_points
        << endl;
  }
  static const int num_points = PointsT::num_points;
  ScalarT values[num_points];
  string name;
};

struct X;
struct Y;
typedef fusion::map<
    fusion::pair<X, fusion::list<C> >,
    fusion::pair<Y, fusion::list<D> >,
    fusion::pair<Y, fusion::list<E<QUAD_Q4> > > > opt;
typedef fusion::list<C,D,E<QUAD_Q4> > K_M;
template <class X> struct enabled {
  typedef enabled<X> type;
  static const bool value = false; };
template <> struct enabled<E<QUAD_Q4> > {
  typedef enabled<E<QUAD_Q4> > type;
  static const bool value = true; };
struct enabled_pred { template <class X> struct apply : enabled<X> {}; };

int main(int argc, char * argv[]) {
  RCP<ParameterList> plist = rcp(new ParameterList);

  typedef fusion::cons<A, fusion::cons<B, fusion::cons<C> > > Seq;
  manager<Seq> m(plist);
  m.set(A(9))
      .set(B(2))
      .set(C(7))
      .run();

  //typedef fusion::result_of::value_at_key<opt,Y>::type ys;
  //typedef fusion::result_of::begin<ys>::type yi;
  //typedef fusion::result_of::value_of<yi>::type X_type;
  typedef fusion::result_of::find_if<K_M, enabled_pred>::type KI_type;
  typedef fusion::result_of::value_of<KI_type>::type K_type;
  typedef fusion::cons<K_type, Seq> Seq2;
  manager<Seq2> m2(plist);
  m2.set( m.get<A>() )
      .set( m.get<B>() )
      .set( m.get<C>() )
      .set( K_type(1) )
      .run();

  return 0;
}
