#include <Kanomi_Demangle.hpp>
#include <stdlib.h>

#include <cxxabi.h>

namespace kanomi {

std::string demangle(const char *	symbol) {
  int	status;
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

} // namespace kanomi
