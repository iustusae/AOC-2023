#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

using idx_t = std::ptrdiff_t;

struct coordinates {
  idx_t x{};
  idx_t y{};
  bool operator==(coordinates &rhs) const { return x == rhs.x && y == rhs.y; }
  bool operator!=(coordinates &rhs) const { return x != rhs.x || y != rhs.y; }
};

struct symbol_c {
  coordinates c{};
  int ct{};
  int num{};
};

bool is_symbol(char ch) {
  return (!std::isalnum(ch) && !std::isspace(ch) && ch != '.');
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

std::vector<std::pair<symbol_c, int>> gears{};

auto push_number(std::string &&oss, int x, int y) -> void {
  int digit{};
  std::istringstream(oss) >> digit;
  number found{
      .value = digit,
      .len = static_cast<int>(oss.size()),
      .coord{static_cast<idx_t>(x - oss.size()), y},
  };
  // printf("Found number %d, at: [%td, %td] with len: %d \n", found.value,
  //        found.coord.x, found.coord.y, found.len);
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

auto find_symbols_2(const std::string &line, int pos) -> void {
  char curr{};
  for (idx_t i = 0; i < line.size(); ++i) {
    curr = line[i];
    if (is_symbol(curr)) {
      // printf("Found symbol: %c at [%zu, %d] \n", curr, i, pos);
      coordinates curr_coords{i, pos};
      symbol symb{
          .value = curr,
          .coord = curr_coords,
      };

      // symbcoords c{.x = i, .y = pos};
      gears.push_back(std::make_pair(symbol_c{coordinates{i, pos}, 0, 1}, 1));
      symbs.push_back(symb);
    }
  }
}


auto adjacents_2() -> void {
  for (auto &coord : symbs) {
    for (auto &num : nums) {

      auto [sx, sy] = coord.coord;
      auto [start_x, start_y] = num.coord;
      auto end_x = start_x + num.len - 1;
      auto end_y = start_y;

      if (start_y == sy || std::abs(start_y - sy) == 1) {
        if ((sx >= start_x - 1) && (sx <= end_x + 1)) {
          // printf("Number: %d [%zu, %zu] is adj to a symbol %c [%zu, %zu] \n",
          //        num.value, num.coord.x, num.coord.y, coord.value, sx, sy);

          for (auto &[p, s] : gears) {
            coordinates c{sx, sy};
            // printf("curr coords. [%td, %td] and [%td, %td]\n", sx, sy, p.x,
            //        p.y);
            auto [px, py] = p.c;

            if (c != p.c || p.ct >= 2) {
              continue;
            } else {
              // printf("found a pair symbol at [%td, %td] that is adj to [%d] "
              //        "and [%td, %td]\n",
              //        sx, sy, num.value, px, py);

              p.num *= num.value;
              //  printf("Gear Ratio for [%td, %td] is: %d \n", px, py, p.num);
              ++p.ct;
            }
          }
        }
      }
    }
  }
}

auto sum_2() -> void {
  int sum{};
  for (const auto &[f, s] : gears) {
    if (f.ct < 2) {
      continue;
    } else {
      sum += f.num;
    }
  }

  printf("|> p2: %d\n", sum);
}
auto solve_2() -> void {
  auto v = load_lines("d3.txt");

  // Why is this bullshit the fucking fix...
  for (idx_t i = 0; i < v.size(); ++i) {

    v[i] += ' ';
  }
  for (idx_t i = 0; i < v.size(); ++i) {

    find_numbers(v[i], i);
    find_symbols_2(v[i], i);
  }

  adjacents_2();
  sum_2();
}

void p() {
  for (const auto &[a, b] : gears) {
    printf("[%td, %td] |> %d\n", a.c.x, a.c.y, a.num);
  }
}
auto main() -> int {
  solve_2();
  // p();
  //

  return 0;
}
