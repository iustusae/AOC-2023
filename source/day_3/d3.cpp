//
//  d3.cpp
//  adventofcode
//
//  Created by Ayman Ougri on 12/4/23.
//

#include <cctype>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using idx_t = std::ptrdiff_t;
int line_len{};
struct coordinates {
  idx_t x{};
  idx_t y{};
};

struct number {
  int value{};
  int len{};
  coordinates coord{};
  bool is_adjacent = false;
  bool is_visited = false;
};

struct symbol {
  char value{};
  coordinates coord{};
};

std::vector<number> nums{};
std::vector<symbol> symbs{};
std::vector<number> adjs{};

template <typename T> auto print_vec(std::vector<T> vec) -> void {
  printf("[");
  for (const auto &elt : vec) {
    std::cout << elt << ", ";
  }
  printf("]");
}

auto load_lines(std::string_view path) -> const std::vector<std::string> {
  std::ifstream fs(path);
  std::string line{};
  std::vector<std::string> lines{};

  while (std::getline(fs, line)) {
    lines.push_back(line);
  }

  return lines;
}

bool is_symbol(char ch) {
  return (!std::isalnum(ch) && !std::isspace(ch) && ch != '.');
}

auto push_number(std::string &&oss, int x, int y) -> void {
  int digit{};
  std::istringstream(oss) >> digit;
  number found{
      .value = digit,
      .len = static_cast<int>(oss.size()),
      .coord{static_cast<idx_t>(x - oss.size()), y},
  };
  printf("Found number %d, at: [%td, %td] with len: %d \n", found.value,
         found.coord.x, found.coord.y, found.len);
  nums.push_back(found);
}

auto find_numbers(const std::string &line, int pos) -> void {

  std::ostringstream oss{};

  int digit{};
  // Loop over every char
  for (int i = 0; i < line.size(); ++i) {
    char curr = line[i];
    // if its a period in the first char, we just reset the oss
    if (i == 0 && curr == '.') {
      oss = {};
    }

    // push the char to oss if its a digit
    if (std::isdigit(curr)) {
      oss << curr;
      // if its not a digit anymore, but the char before it was, oss gets
      // casted
      // into digit, new number created and pushed into the global scope
      // vector
      // with it's coords.
    } else if ((!std::isdigit(curr) && std::isdigit(line[i - 1]))) {
      push_number(oss.str(), i, pos);
      oss = {};
    }

    if (i + 1 >= line.size() && oss.str() != "") {
      push_number(oss.str(), i, pos);
      oss = {};
    }
  }
}

auto find_symbols(const std::string &line, int pos) -> void {
  char curr{};
  for (idx_t i = 0; i < line.size(); ++i) {
    curr = line[i];
    if (is_symbol(curr)) {
      printf("Found symbol: %c at [%zu, %d] \n", curr, i, pos);
      coordinates curr_coords{i, pos};
      symbol symb{
          .value = curr,
          .coord = curr_coords,
      };
      symbs.push_back(symb);
    }
  }
}

auto sum() -> void {
  int sum{};

  for (const auto &num : nums) {
    if (num.is_adjacent) {
      sum += num.value;
    }
  }

  printf("%d : count\n", sum);
}

auto in_range(int n, idx_t lo, idx_t hi) -> bool {
  return (lo <= n && n <= hi);
}

std::vector<coordinates> dirs{

    {0, 1}, {1, 0}, {-1, 0}, {0, -1}, {1, 1}, {1, -1}, {-1, -1}, {-1, -1},

};

auto adjacents() -> void {
  for (auto &coord : symbs) {
    for (auto &num : nums) {
      if (num.is_visited) {
        continue;
      }
      auto [sx, sy] = coord.coord;
      auto [start_x, start_y] = num.coord;
      auto end_x = start_x + num.len - 1;
      auto end_y = start_y;

      if (start_y == sy || std::abs(start_y - sy) == 1) {
        if ((sx >= start_x - 1) && (sx <= end_x + 1)) {
          printf("Number: %d [%zu, %zu] is adj to a symbol %c [%zu, %zu] \n",
                 num.value, num.coord.x, num.coord.y, coord.value, sx, sy);
          num.is_adjacent = true;
          num.is_visited = true;
        }
      }
    }
  }
}

auto solve() -> void {
  auto v = load_lines("d3.txt");
  line_len = v[0].size();

  for (auto &e : v) {
    e += ' ';
  }

  for (idx_t i = 0; i < v.size(); ++i) {

    find_numbers(v[i], i);
    find_symbols(v[i], i);
  }

  adjacents();
  sum();
}
auto main() -> int {

  solve();
  return 0;
}
