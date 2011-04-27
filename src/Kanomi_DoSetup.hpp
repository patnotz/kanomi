#ifndef KANOMI_DOSETUP_HPP_
#define KANOMI_DOSETUP_HPP_

#include <iostream>
#include <Teuchos_ParameterList.hpp>

namespace kanomi {

template <class M>
struct DoSetup {
  typedef M ManagerT;
  DoSetup(
      ManagerT & m,
      Teuchos::RCP<Teuchos::ParameterList> p) :
        manager(m), plist(p) {}
  template<class T>
  void operator()(T & t) const {
    std::cout << "setup: "<< t.name << std::endl;
    //t.setup(manager, plist);
  }
  ManagerT & manager;
  Teuchos::RCP<Teuchos::ParameterList> plist;
};

} // namespace kanomi

#endif /* KANOMI_DOSETUP_HPP_ */
