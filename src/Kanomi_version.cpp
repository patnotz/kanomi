#include <Kanomi_version.hpp>
#include <Kanomi_autoversion.hpp>

namespace kanomi {

std::string version() {
  std::string v = "v";
  return v + KANOMI_VERSION;
}

} // namespace kanomi
