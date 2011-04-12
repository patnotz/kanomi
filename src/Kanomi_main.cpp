#include <iostream>
#include <Kanomi_FieldNames.hpp>
#include <Kanomi_Manager.hpp>
#include <Kanomi_Model.hpp>
#include <Kanomi_ScalarField.hpp>
#include <Kanomi_Stencils.hpp>
#include <User_Config.hpp>

using namespace kanomi;
using namespace std;
using namespace Teuchos;

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

int main(int argc, char * argv[]) {

  // This would be read from a user file
  RCP<ParameterList> plist = rcp(new ParameterList);
  plist->sublist("A").set<ScalarT>("value",9.13);
  plist->sublist("B").set<ScalarT>("value",2.5);
  plist->sublist("C").set<ScalarT>("value",7.3);
  plist->sublist("D").set<ScalarT>("value",10);
  plist->sublist("THERMAL_CONDUCTIVITY_CONSTANT").set<ScalarT>("value",10);
  plist->sublist("THERMAL_CONDUCTIVITY_FIELD_DATA").set<ScalarT>("value",15);
  plist->sublist("TEMPERATURE").set<ScalarT>("value",3.14159);

  typedef bf::cons<A, bf::cons<B, bf::cons<C> > > Seq;
  Manager<Seq> m(plist);
  m.run();

  typedef typename Model<field::THERMAL_CONDUCTIVITY,QUAD_Q4>::list TC_list;
  typedef enabled_pred<field::THERMAL_CONDUCTIVITY> selector;
  typedef bf::result_of::find_if<TC_list, selector >::type KI_type;
  typedef bf::result_of::value_of<KI_type>::type K_type;
  typedef bf::cons<K_type, Seq> Seq2;

  Manager<Seq2> m2(plist);
  m2.run();

  return 0;
}
