#ifndef KANOMI_NAMED_HPP_
#define KANOMI_NAMED_HPP_

#include <Kanomi_Demangle.hpp>
#include <typeinfo>

namespace kanomi {

template <class T>
struct Named {
  static std::string name() {
    std::string s = demangle( typeid(T).name() );
    const char * s1 = s.c_str();
    const char * s0 = s1;
    while (*s1) {
      if (*s1 == ':')
        s0 = s1 + 1;
      ++s1;
    }
    return std::string(s0, s1);
  }
};

#define KANOMI_NAMED_TAG(TYPE) struct TYPE : Named<TYPE> {}

} // namespace kanomi

#endif /* KANOMI_NAMED_HPP_ */
