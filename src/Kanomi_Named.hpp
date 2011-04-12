#ifndef KANOMI_NAMED_HPP_
#define KANOMI_NAMED_HPP_

#include <Kanomi_Demangle.hpp>
#include <typeinfo>

namespace kanomi {

template <class T>
struct Named {
  static std::string name() {
    return demangle_no_scope( typeid(T).name() );
  }
};

#define KANOMI_NAMED_TAG(TYPE) struct TYPE : Named<TYPE> {}

} // namespace kanomi

#endif /* KANOMI_NAMED_HPP_ */
