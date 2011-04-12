#include <Kanomi_Demangle.hpp>
#include <stdlib.h>

#include <cxxabi.h>

namespace kanomi {

std::string demangle(const char * symbol) {
  int status;
  char * demangled_symbol = __cxxabiv1::__cxa_demangle(symbol, 0, 0, &status);
  std::string result;
  if (demangled_symbol) {
    result = std::string(demangled_symbol);
    free(demangled_symbol);
  }
  if (status != 0)
    result = std::string(symbol);
  return result;
}

std::string demangle_no_scope(const char * symbol) {
  std::string s = demangle( symbol );
  const char * s1 = s.c_str();
  const char * s0 = s1;
  while (*s1) {
    if (*s1 == ':')
      s0 = s1 + 1;
    ++s1;
  }
  return std::string(s0, s1);
}

} // namespace kanomi
