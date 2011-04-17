#include <iostream>
#include <Kanomi_FieldNames.hpp>
#include <Kanomi_Manager.hpp>
#include <Kanomi_Factory.hpp>
#include <Kanomi_ScalarField.hpp>
#include <Kanomi_Stencils.hpp>
#include <Kanomi_version.hpp>
#include <Kanomi_EQ_Energy.hpp>
#include <User_Config.hpp>

using namespace std;
using namespace Teuchos;

namespace kanomi {

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
  typedef field::FIELD_A FieldT;
  A() : Base("A") {}
  template <class M>
  void setup(M & m, RCP<ParameterList> plist) {
    value = plist->sublist(name,true).get<ScalarT>("value");
    cout << "setup " << name << endl;
  }
};

struct B : public Base {
  typedef field::FIELD_B FieldT;
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
  typedef field::FIELD_C FieldT;
  C() : Base("C") {}
  template <class M>
  void setup(M & m, RCP<ParameterList> plist) {
    value = plist->sublist(name,true).get<ScalarT>("value");
    cout << "setup " << name << endl;
  }
};

struct D : public Base {
  typedef field::FIELD_D FieldT;
  D() : Base("D") {}
  template <class M>
  void setup(M & m, RCP<ParameterList> plist) {
    value = plist->sublist(name,true).get<ScalarT>("value");
    cout << "setup " << name << endl;
  }
};

} // namespace kanomi

using namespace kanomi;
int main(int argc, char * argv[]) {

  cout << "This is Kanomi " << version() << endl;

  // This would be read from a user file
  RCP<ParameterList> plist = rcp(new ParameterList);
  plist->sublist("A").set<ScalarT>("value",9.13);
  plist->sublist("B").set<ScalarT>("value",2.5);
  plist->sublist("C").set<ScalarT>("value",7.3);
  plist->sublist("D").set<ScalarT>("value",10);
  plist->sublist("THERMAL_CONDUCTIVITY_CONSTANT").set<ScalarT>("value",10);
  plist->sublist("TEMPERATURE_FIELD_DATA").set<ScalarT>("value",298);
  plist->sublist("THERMAL_CONDUCTIVITY_FIELD_DATA").set<ScalarT>("value",15);
  plist->sublist("THERMAL_CONDUCTIVITY_POLYNOMIAL").set<int>("order",2);
  plist->sublist("THERMAL_CONDUCTIVITY_POLYNOMIAL").set<ScalarT>("C_0",1);
  plist->sublist("THERMAL_CONDUCTIVITY_POLYNOMIAL").set<ScalarT>("C_2",0.001);
  plist->sublist("TEMPERATURE").set<ScalarT>("value",3.14159);

  typedef bf::cons<A, bf::cons<B, bf::cons<C> > > Seq;
  Manager<Seq> m(plist);
  m.run();

  //typedef ScalarField<field::TEMPERATURE,model::FIELD_DATA,QUAD_Q4> TempT;
  typedef typename Factory<field::TEMPERATURE,QUAD_Q4>::ProviderT TempT;
  typedef typename Factory<field::THERMAL_CONDUCTIVITY,QUAD_Q4>::ProviderT K_type;
  typedef bf::cons<TempT, bf::cons<K_type, Seq> > Seq2;

  Manager<Seq2> m2(plist);
  m2.run();

  return 0;
}
