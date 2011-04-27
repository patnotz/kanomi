#ifndef KANOMI_DOEVALUATE_HPP_
#define KANOMI_DOEVALUATE_HPP_

#include <iostream>

namespace kanomi {

struct DoEvaluate {
  template <class T>
  void operator()(T & t) const {
    std::cout << "evaluate: " << t.name << std::endl;
    //t.evaluate();
  }
};

} // namespace kanomi

#endif /* KANOMI_DOEVALUATE_HPP_ */
