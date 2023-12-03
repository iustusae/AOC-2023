#include "lib.hpp"

auto main() -> int
{
  auto const lib = library {};

  return lib.name == "ttt" ? 0 : 1;
}
