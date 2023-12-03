#ifndef DAY_T
#define DAY_T
#include <cstdlib>
#include <exception>
#include <iostream>
inline auto asserted(bool expr,
                     std::string_view msg,
                     int line = __LINE__,
                     std::string_view fname = __FILE_NAME__) -> void
{
  if (!expr) {
    std::abort();

    std::cerr << "Assertion has failed at: " << line << '\n' << '\t' << msg;
  } else {
    std::cout << "Test passed at [" << fname << ", " << line << ']' << '\n';
  }
}

inline void logged(std::string_view msg)
{
  std::cout << msg << "\r\n\t at: " << __LINE__ << " " << __FILE_NAME__ << '\n';
}

#endif
