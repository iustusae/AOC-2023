#ifndef D1_P2_HPP_
#define D1_P2_HPP_
#include <cctype>
#include <cstddef>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <map>
#include <numeric>
#include <regex>
#include <sstream>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>

#include "day_t.hpp"

inline static auto sliding_window(std::string& str) -> void;

static auto strip_digits(std::string_view calibration_line) -> void;

const static std::map<std::string_view, int> stringed_num {{"two", 2},
                                                           {"three", 3},
                                                           {"four", 4},
                                                           {"five", 5},
                                                           {"six", 6},
                                                           {"seven", 7},
                                                           {"eight", 8},
                                                           {"nine", 9},
                                                           {"one", 1}};
inline const static std::map<int, std::string> rev {{1, "one"},
                                                    {2, "two"},
                                                    {3, "three"},
                                                    {4, "four"},
                                                    {5, "five"},
                                                    {6, "six"},
                                                    {7, "seven"},
                                                    {8, "eight"},
                                                    {9, "nine"}};
static std::vector<int> calibration_vals = {};
inline auto extract_digits(std::string_view sv) -> std::string
{
  std::string str {sv};
  printf("Current string: %s\n", sv);
  std::ostringstream oss {};

  for (auto i = 0; i < sv.size(); ++i) {
    for (auto j = i; j < sv.size(); ++j) {
      oss << sv[j];
      if (std::isdigit(sv[j])) {
        continue;
      }
      if (stringed_num.find(oss.str()) != stringed_num.end()) {
        std::cout << stringed_num.at(oss.str()) << '\n';
        str = std::regex_replace(static_cast<std::string>(sv),
                                 std::regex(oss.str()),
                                 std::to_string(stringed_num.at(oss.str())));
      }

      if (oss.str().size() > 5) {
        oss = {};
      }
    }
    oss = {};
  }

  return str;
}

inline std::string replace_all(const std::string& input)
{
  // Define a mapping of digit names to their corresponding numerical values
  std::unordered_map<std::string, std::string> digitMap = {{"one", "1"},
                                                           {"two", "2"},
                                                           {"three", "3"},
                                                           {"four", "4"},
                                                           {"five", "5"},
                                                           {"six", "6"},
                                                           {"seven", "7"},
                                                           {"eight", "8"},
                                                           {"nine", "9"}};

  std::string result = input;

  // Iterate through the digitMap and replace occurrences in the string
  for (const auto& entry : digitMap) {
    size_t found = result.find(entry.first);
    if (found != std::string::npos) {
      result.replace(found, entry.first.length(), entry.second);
      // Break after the first occurrence of each digit
    }
  }

  return result;
}

static auto strip_digits(std::string_view calibration_line) -> void
{
  std::cout << "Stripping: " << calibration_line << '\n';
  std::vector<int> nums {};

  for (char tok : calibration_line) {
    if (std::isdigit(tok) != 0) {
      nums.push_back(
          static_cast<int>(tok - '0'));  // remove 0 to make it an integer.
    }
  }

  int stripped = 10 * nums[0] + nums[nums.size() - 1];
  std::cout << "Result: " << stripped << "\n\n";
  calibration_vals.push_back(stripped);
}

static auto sum() -> int
{
  return std::accumulate(
      calibration_vals.begin(), calibration_vals.end(), 0, std::plus<>());
};

/**
 * @brief check a the line by chunks of 5 (5 is the longest char ct (ie s e v e
 * n || e i g h t)) and see if it translates into a word,
 *
 *
 * @return std::string, the modified string.
 */

inline static auto wordtodigit(std::string& str) -> std::string
{
  std::ostringstream oss {};
  std::string stringed {str};
  for (const auto& ch : str) {
    if (isdigit(ch)) {
      continue;
    }
    std::cout << ch << ' ';
    oss << ch;
    std::cout << oss.str() << '\n';
    if (stringed_num.find(oss.str()) != stringed_num.end()) {
      stringed = std::regex_replace(stringed,
                                    std::regex(oss.str()),
                                    std::to_string(stringed_num.at(oss.str())));
      oss = {};
    }
  }

  return stringed;
}

inline auto is_in(std::string& sub) -> std::pair<int, int>
{
  for (const auto& [key, value] : stringed_num) {
    if (sub.find(key) != std::string::npos) {
      return {key.size(), value};
    }
  }

  return {0, 0};
}

inline static void print_vec(std::vector<int>& vec)
{
  std::cout << '[';
  for (const auto& v : vec) {
    std::cout << v << ", ";
  }
  std::cout << ']';
}
inline static void print_vec(std::vector<std::pair<int, int>>& vec)
{
  std::cout << '[';
  for (const auto& p : vec) {
    std::cout << '(' << p.first << ',' << p.second << "), ";
  }
  std::cout << ']';
}
inline static void rem_str(std::string& s, std::string ext)
{
  s = std::regex_replace(s, std::regex(ext), "");
}

// inline static auto sliding_window(std::string& str) -> void
// {
//   std::cout << "using string: " << str << '\n';
//   std::vector<int> calibers {};
//   std::string sub;
//   int pos {};
//   for (auto i = 0; i < str.size(); ++i) {
//     if (i + 5 < str.size()) {
//       pos = 5;
//     } else {
//       pos = str.size() - i;
//     }

//     sub = str.substr(i, pos);

//     // std::cout << sub << '\n';
//     auto [in, val] = is_in(sub);

//     for (const auto& ch : sub) {
//       if (isdigit(ch)) {
//         calibers.push_back(static_cast<int>(ch - '0'));
//       }
//     }

//     if (in != 0) {
//       str.erase(i, in);
//       rem_str(sub, rev.at(val));
//       std::cout << "This is the sub " << sub << '\n';

//       calibers.push_back(val);
//     } else {
//     }
//   }
//   print_vec(calibers);
//   std::cout << calibers[0] * 10 + calibers[calibers.size() - 1];
// }
inline std::vector<int> calibers {};

inline static auto sliding_window(std::string& str) -> void
{
  std::string cpy {str};

  std::vector<std::pair<int, int>> d {};

  for (auto i = 0; i < str.size(); ++i) {
    int pos = 5;
    if (i + pos > str.size()) {
      pos = str.size() - i;
    }

    std::string sub = str.substr(i, pos);

    auto [in, val] = is_in(sub);

    for (const auto& ch : sub) {
      if (isdigit(ch)) {
        d.push_back({static_cast<int>(ch - '0'), cpy.find(ch)});
      }
    }

    if (in != 0) {
      d.push_back({val, cpy.find(rev.at(val))});
      str.erase(i, in);
    }
  }

  std::sort(d.begin(),
            d.end(),
            [](auto& left, auto& right) { return left.second < right.second; });
  int res = d[0].first * 10 + d[d.size() - 1].first;
  calibers.push_back(res);
  logged(std::to_string(res));
}

inline void kill_me(std::string& str)
{
  std::vector<std::pair<int, int>> d {};
  for (const auto& [key, value] : stringed_num) {
    if (str.find(key) != std::string::npos) {
      d.push_back({value, str.find(key)});
    }
  }

  for (std::string::size_type i = 0; i < str.size(); ++i) {
    if (std::isdigit(str[i])) {
      d.push_back({str[i] - '0', i});
    }
  }

  print_vec(d);
  std::sort(d.begin(),
            d.end(),
            [](auto& left, auto& right) { return left.second < right.second; });
  int res = d[0].first * 10 + d[d.size() - 1].first;
  calibers.push_back(res);
}

inline int summed()
{
  return std::accumulate(calibers.begin(), calibers.end(), 0, std::plus<>());
}
static auto read_and_strip() -> void
{
  std::ifstream reader("/Users/iustus/aoc/ttt/source/day_1/d1.txt");
  std::string line;
  while (std::getline(reader, line)) {
    kill_me(line);
  }
  std::cout << summed();
}

#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

std::vector<std::string> load_lines(std::string file)
{
  std::ifstream f(file);

  std::vector<std::string> lines;
  std::string line;

  while (std::getline(f, line)) {
    lines.push_back(line);
  }

  return lines;
}

int check(const char ch)
{
  switch (ch) {
    case '1':
      return 1;
    case '2':
      return 2;
    case '3':
      return 3;
    case '4':
      return 4;
    case '5':
      return 5;
    case '6':
      return 6;
    case '7':
      return 7;
    case '8':
      return 8;
    case '9':
      return 9;
    default:
      return 0;
  }
}

// part 2
std::unordered_map<std::string, std::string> number_map = {{"one", "o1e"},
                                                           {"two", "t2o"},
                                                           {"three", "t3e"},
                                                           {"four", "f4r"},
                                                           {"five", "f5e"},
                                                           {"six", "s6x"},
                                                           {"seven", "s7n"},
                                                           {"eight", "e8t"},
                                                           {"nine", "n9e"}};

inline int correct()
{
  auto lines = load_lines("/Users/iustus/aoc/ttt/source/day_1/d1.txt");

  // part 2
  for (auto& line : lines) {
    for (const auto& number : number_map) {
      size_t pos = line.find(number.first);
      while (pos != std::string::npos) {
        line.replace(pos, number.first.length(), number.second);
        pos = line.find(number.first, pos + number.second.length());
      }
    }
  }

  int out = 0;

  for (const auto line : lines) {
    int digits[2] = {0, 0};

    for (int i = 0; i < line.length(); i++) {
      int digit = check(line[i]);

      if (digit == 0) {
        continue;
      } else {
        digits[0] = digit;
        break;
      }
    }

    for (int i = line.length(); i >= 0; i--) {
      int digit = check(line[i]);

      if (digit == 0) {
        continue;
      } else {
        digits[1] = digit;
        break;
      }
    }

    out += (digits[0] * 10) + digits[1];
  }

  std::cout << out << std::endl;

  return 0;
}

#endif  // D1_P2_HPP_
