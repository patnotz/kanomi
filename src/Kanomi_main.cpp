#include <iostream>
#include <fstream>
#include <Teuchos_ParameterList.hpp>
#include <Kanomi_BuildManager.hpp>
#include <Kanomi_version.hpp>
#include <User_Config.hpp>

using namespace kanomi;

int main(int argc, char * argv[]) {

  std::cout << "This is Kanomi " << version() << std::endl;

  // This would be read from a user file
  Teuchos::RCP<Teuchos::ParameterList> plist = Teuchos::rcp(new Teuchos::ParameterList);
  plist->sublist("THERMAL_CONDUCTIVITY_CONSTANT").set<ScalarT>("value",10);
  plist->sublist("TEMPERATURE_FIELD_DATA").set<ScalarT>("value",298);
  plist->sublist("THERMAL_CONDUCTIVITY_FIELD_DATA").set<ScalarT>("value",15);
  plist->sublist("THERMAL_CONDUCTIVITY_POLYNOMIAL").set<int>("order",2);
  plist->sublist("THERMAL_CONDUCTIVITY_POLYNOMIAL").set<ScalarT>("C_0",1);
  plist->sublist("THERMAL_CONDUCTIVITY_POLYNOMIAL").set<ScalarT>("C_2",0.001);
  plist->sublist("TEMPERATURE").set<ScalarT>("value",3.14159);

  typedef typename BuildManager<UserRootsT>::ManagerT ManagerT;
  ManagerT m(plist);
  m.run();
  std::ofstream os("kanomi.dot");
  m.dump_graph(os);

  return 0;
}
