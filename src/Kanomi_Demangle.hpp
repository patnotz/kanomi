#ifndef KANOMI_DEMANGLE_HPP_
#define KANOMI_DEMANGLE_HPP_

#include <string>

namespace kanomi {

std::string demangle(const char * symbol);
std::string demangle_no_scope(const char * symbol);

} // namespace kanomi

#endif // KANOMI_DEMANGLE_HPP_
