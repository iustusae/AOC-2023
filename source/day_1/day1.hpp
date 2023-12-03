#ifndef DAY1_HPP_
#define DAY1_HPP_
#include <cctype>
#include <fstream>
#include <functional>
#include <iostream>
#include <map>
#include <numeric>
#include <regex>
#include <string>
#include <string_view>
#include <vector>

////////// THIS IS DEPRECATED AS SHIT.

namespace data
{
// had to use this to store the values.
static std::vector<int> calibration_vals = {};
const static std::map<std::string_view, int> stringed_num {{"one", 1},
                                                           {"two", 2},
                                                           {"three", 3},
                                                           {"four", 4},
                                                           {"five", 5},
                                                           {"six", 6},
                                                           {"seven", 7},
                                                           {"eight", 8},
                                                           {"nine", 9}};
const static std::map<int, std::string_view> rev {{1, "one"},
                                                  {2, "two"},
                                                  {3, "three"},
                                                  {4, "four"},
                                                  {5, "five"},
                                                  {6, "six"},
                                                  {7, "seven"},
                                                  {8, "eight"},
                                                  {9, "nine"}};
}  // namespace data

class dayone_t
{
public:
  static auto solve() -> void { dayone_t::read_and_strip(); };
  [[nodiscard("")]] static auto replace(std::string_view line,
                                        std::string_view key,
                                        int val) -> std::string_view
  {
    std::cout << "replace: "
              << "\r\n\t " << line << " " << key << val << '\n';
    line = std::regex_replace(static_cast<std::string>(line),
                              std::regex(static_cast<std::string>(key)),
                              std::to_string(val));
    std::cout << "line result: " << line << '\n';
    return line;
  }
  static auto find_nums_strip(std::string_view calibration_line) -> void
  {
    // using namespace data;

    // for (auto curr = stringed_num.begin(); curr != stringed_num.end();
    // ++curr) {
    //   decltype(curr) inner {};
    //   std::string::size_type idx;
    //   auto curr_idx = calibration_line.find(curr->first);
    //   if (curr_idx == std::string::npos) {
    //     continue;
    //   }
    //   for (inner = stringed_num.begin(); inner != stringed_num.end();
    //   ++inner) {
    //     if (calibration_line.find(inner->first) != std::string::npos) {
    //       idx = calibration_line.find(inner->first);
    //     } else {
    //       continue;
    //     }
    //   }

    //   if (idx < curr_idx) {
    //     calibration_line =
    //         replace(calibration_line, inner->first, inner->second);
    //   } else {
    //     calibration_line = replace(calibration_line, curr->first,
    //     curr->second);
    //   }
    // }

    for (const auto& [key, val] : data::stringed_num) {
      auto idx = calibration_line.find(key);

      if (idx != std::string::npos) {
        replace(calibration_line, key, val);
      }
    }
    std::cout << "calibration_line: " << calibration_line << '\n';
    strip_digits(calibration_line);
  }

  static void print_vec(const std::vector<int>& vec)
  {
    std::cout << '[';
    for (const auto& item : vec) {
      std::cout << item << ' ';
    }
    std::cout << "]\n";
  }
  static auto strip_digits(std::string_view calibration_line) -> void
  {
    std::vector<int> nums {};

    std::cout << "calib: " << calibration_line << '\n';
    for (char tok : calibration_line) {
      std::cout << "Current token: " << tok << '\n';
      if (std::isdigit(tok) != 0) {
        print_vec(nums);
        nums.push_back(
            static_cast<int>(tok - '0'));  // remove 0 to make it an integer.
      }
    }

    int stripped = 10 * nums[0] + nums[nums.size() - 1];
    std::cout << stripped << '\n';
    data::calibration_vals.push_back(stripped);
  }

  static auto sum() -> int
  {
    return std::accumulate(data::calibration_vals.begin(),
                           data::calibration_vals.end(),
                           0,
                           std::plus<>());
  }

  static auto read_and_strip() -> void
  {
    std::ifstream reader("d1.txt");
    std::string line;
    while (std::getline(reader, line)) {
      std::cout << line << '\n';
      dayone_t::strip_digits(line);
    }
    std::cout << dayone_t::sum();
  }
};

#endif  // DAY1_HPP_
