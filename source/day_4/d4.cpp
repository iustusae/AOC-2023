
#include <algorithm>
#include <array>
#include <cctype>
#include <cmath>
#include <cstddef>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <iterator>
#include <set>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>

template<typename T>
auto print_vec(std::vector<T> vec) -> void
{
  printf("[");
  for (const auto& elt : vec) {
    std::cout << elt << ", ";
  }
  printf("]");
}

auto load_lines(std::string_view path) -> std::vector<std::string>
{
  std::vector<std::string> lines {};
  std::string line {};
  std::ifstream fs(path);

  while (std::getline(fs, line)) {
    line += ' ';
    lines.push_back(line);
  }

  return lines;
}

int parse_int(std::string l)
{
  std::ostringstream oss {};
  int ret {};
  for (int i = 0; i < l.size(); ++i) {
    char curr = l[i];
    if (std::isdigit(curr)) {
      oss << curr;
    }
  }

  std::istringstream(oss.str()) >> ret;
  oss = {};
  return ret;
}
int extract_id(std::string line)
{
  int id {};
  line = line.substr(0, line.find(':'));

  id = parse_int(line);

  return id;
}

auto split_cards(std::string line, std::array<std::string, 2>& arr) -> void
{
  line = line.substr(line.find(':') + 1);
  // line.erase(std::remove_if(
  // line.begin(), line.end(), [](char ch) { return isspace(ch); }));

  if (line.find('|') == std::string::npos) {
    std::cerr << "Invalid string: " << line << '\n';
    std::exit(-1);
  } else {
    arr[0] = line.substr(0, line.find('|'));
    arr[1] = line.substr(line.find('|') + 1);
  }
}

auto parse_game(std::vector<int>& vec, std::string& res) -> void
{
  std::ostringstream oss {};

  for (std::ptrdiff_t i = 0; i < res.size(); ++i) {
    char ch = res[i];

    if (std::isdigit(ch)) {
      oss << ch;
    } else if ((!std::isdigit(ch)) && std::isdigit(res[i - 1])) {
      int i {};
      std::istringstream(oss.str()) >> i;
      vec.push_back(i);
      oss = {};
    }
  }
}

auto extract_numbers(std::array<std::string, 2>& lines,
                     std::array<std::vector<int>, 2>& winnscratch) -> void
{
  parse_game(winnscratch[0], lines[0]);
  parse_game(winnscratch[1], lines[1]);
}

auto parse_line(std::string& line) -> std::array<std::vector<int>, 2>
{
  int id = extract_id(line);
  // printf("[%d]: %s\n", id, line.c_str());
  std::array<std::string, 2> lines {};
  split_cards(line, lines);
  std::array<std::vector<int>, 2> winnscratch {};
  extract_numbers(lines, winnscratch);

  return winnscratch;
}

auto sum_pts(const std::vector<int>& w, const std::vector<int>& g) -> int
{
  // to remove all duplicates, :D
  std::set<int> ws {w.begin(), w.end()};
  std::set<int> gw {g.begin(), g.end()};
  std::set<int> intersect {};
  std::set_intersection(ws.begin(),
                        ws.end(),
                        gw.begin(),
                        gw.end(),
                        std::inserter(intersect, intersect.begin()));

  printf("intersect.size(): %zu\n", intersect.size());
  return intersect.size();
}

auto p1() -> int
{
  auto v = load_lines("test.txt");
  int sum {};

  for (auto& e : v) {
    auto [winning, curr] = parse_line(e);
    sum += std::pow(2, sum_pts(winning, curr) - 1);
  }

  printf("%d\n", sum);
  return 0;
}

// struct Card
// {
//   int id {};
//   std::vector<int> w {};
//   std::vector<int> c {};
// };

// std::map<int, int> ct {};
// std::map<int, int> nmatches {};
// template<typename T, typename U>
// void print_map(std::map<T, U>& m)
// {
//   printf("[");
//   for (auto& [k, v] : m) {
//     std::cout << "{" << k << ", " << v << "}"
//               << " ";
//   }
//   printf("]\n");
// }

// auto main() -> int
// {
//   auto v = load_lines("test.txt");

//   std::vector<Card> cards {};
//   int sum {};

//   for (auto& s : v) {
//     int id = extract_id(s);
//     ct.insert({id, 1});
//   }

//   print_map(ct);

//   for (auto& s : v) {
//     int id = extract_id(s);
//     auto [winning, curr] = parse_line(s);
//     auto d = sum_pts(winning, curr);
//     nmatches.insert({id, d});
//     int i = id + 1;
//     while ((i) <= id + d) {
//       ++ct.at(i);
//       ++i;
//     }
//   }

//   // print_map(ct);
//   // print_map(nmatches);

//   for (auto& [k, v] : ct) {
//     printf("id: %d - %d\n", k, v);
//     int dupes = v - 1;
//     if (dupes <= 0) {
//       continue;
//     };
//     printf("id: %d - %d\n", k, v);
//     for (int e = k + 1; e <= k + dupes; ++e) {
//       printf("%d -> %d\n", e, k + dupes);
//       ++ct[e];
//     }
//   }
//   print_map(ct);
//   return 0;
// }

// auto increment(int start, int end)
// {
//   int s = start;
//   while (s <= end) {
//     ++ct[start];
//   }
// }
