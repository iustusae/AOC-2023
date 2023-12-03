#include <algorithm>
#include <cctype>
#include <fstream>
#include <functional>
#include <ios>
#include <iostream>
#include <map>
#include <numeric>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>

/**
 * @brief Data structure modeling a game.
 *
 */
struct Game
{
  struct Triad
  {
    int r, g, b;
  };

  int id {};
  bool is_valid = true;
  Triad cube_cts = {};
};

/**
 * @brief Map containing maximum amount of cubes per color, according to the
 * game's spec.
 *
 */
const std::map<std::string_view, int> color_max {
    {"red", 12},
    {"green", 13},
    {"blue", 14},
};

/**
 * @brief Will contain all the valid games after processing. Used in the sum()
 * function to sum all the ids.
 *
 */
std::vector<int> valids {};

/**
 * @brief Loads the lines from a text file to an std::vector.
 *
 * @param file_path I could have hardcoded the path to the exercice file's, but
 * because testing, i chose to make it modular.
 * @return std::vector<std::string> vector of all the game lines.
 */
auto load_lines(std::string_view file_path) -> std::vector<std::string>;

/**
 * @brief Wrapper over the other functions, essentially will do multiple splits
 * to get the Game id, and the cube counts for each game_line. Instantiate a new
 * Game object.
 *
 * @param game_line
 */
auto parse(std::string& game_line) -> void;

auto extract_id(std::string& game_line) -> int;

auto parse_cube_count(std::string& game_line, Game& game) -> bool;

auto sum() -> int;

auto load_lines(std::string_view file_path) -> std::vector<std::string>
{
  std::ifstream fs(file_path);
  std::string line {};
  std::vector<std::string> lines {};
  while (std::getline(fs, line)) {
    lines.push_back(line);
  }

  return lines;
}

auto parse(std::string& game_line) -> void
{
  std::string cpy {game_line};
  Game game {};
  game.id = extract_id(cpy);
  parse_cube_count(cpy, game);
  if (game.is_valid) {
    valids.push_back(game.id);
  }
}

auto extract_id(std::string& game_line) -> int
{
  std::string cpy {game_line};
  cpy = cpy.substr(0, cpy.find(":"));
  cpy.erase(std::remove_if(cpy.begin(),
                           cpy.end(),
                           [](unsigned char ch) { return !std::isdigit(ch); }));
  cpy = cpy.substr(cpy.find(" ") + 1, cpy.size());

  int i = {};
  std::istringstream(cpy) >> i;
  return i;
}

auto validate_cube_count(std::string cube) -> bool
{
  int val {};

  std::istringstream(cube) >> val;
  cube.erase(
      std::remove_if(
          cube.begin(), cube.end(), [](char ch) { return !std::isalpha(ch); }),
      cube.end());

  return val <= color_max.at(cube);
}
auto parse_cube_count(std::string& game_line, Game& game) -> bool
{
  auto rounds {game_line.substr(game_line.find(":") + 1, game_line.size())};
  size_t pos {};
  std::string sub {};
  std::vector<std::string> tokenized {};
  std::vector<std::string> cubes_colors {};
  // Split the round string by sections
  while ((pos = rounds.find(";")) != std::string::npos) {
    sub = rounds.substr(0, pos);

    tokenized.push_back(sub);
    rounds.erase(0, pos + 1);
  }

  tokenized.push_back(rounds);
  sub = {};
  // Split each section by each cube color and count
  for (auto& str : tokenized) {
    while ((pos = str.find(",")) != std::string::npos) {
      sub = str.substr(0, pos);
      cubes_colors.push_back(sub);
      str.erase(0, pos + 1);
    }
    cubes_colors.push_back(str);
  }

  for (auto& a : cubes_colors) {
    // extracts int(num cubes) and string(cube color)
    bool valid = validate_cube_count(a);
    if (!valid) {
      game.is_valid = false;
      return false;
    }
  }

  return true;
}

auto sum() -> int
{
  return std::accumulate(valids.begin(), valids.end(), 0, std::plus<>());
}

auto min_cube(std::string& game_line, Game& game) -> int;
auto extract_cube_count(std::string cube) -> std::pair<std::string, int>;

std::vector<int> mults {};

auto parse_two(std::string& game_line) -> void
{
  std::string cpy {game_line};
  Game game {};
  game.id = extract_id(cpy);
  mults.push_back(min_cube(cpy, game));
}

auto min_cube(std::string& game_line, Game& game) -> int
{
  auto rounds {game_line.substr(game_line.find(":") + 1, game_line.size())};
  size_t pos {};
  std::string sub {};
  std::vector<std::string> tokenized {};
  std::vector<std::string> cubes_colors {};
  while ((pos = rounds.find(";")) != std::string::npos) {
    sub = rounds.substr(0, pos);

    tokenized.push_back(sub);
    rounds.erase(0, pos + 1);
  }

  tokenized.push_back(rounds);
  sub = {};
  for (auto& str : tokenized) {
    while ((pos = str.find(",")) != std::string::npos) {
      sub = str.substr(0, pos);
      cubes_colors.push_back(sub);
      str.erase(0, pos + 1);
    }
    cubes_colors.push_back(str);
  }

  std::vector<int> r {};
  std::vector<int> g {};
  std::vector<int> b {};
  for (auto& a : cubes_colors) {
    auto [color, count] = extract_cube_count(a);
    if (color == "red") {
      r.push_back(count);
    } else if (color == "green") {
      g.push_back(count);
    } else if (color == "blue") {
      b.push_back(count);
    }
  }

  int rm {*std::max_element(r.begin(), r.end())};
  int gm {*std::max_element(g.begin(), g.end())};
  int bm {*std::max_element(b.begin(), b.end())};

  std::cout << rm * gm * bm << '\n';
  return rm * gm * bm;
}

auto extract_cube_count(std::string cube) -> std::pair<std::string, int>
{
  int val {};

  std::istringstream(cube) >> val;
  cube.erase(
      std::remove_if(
          cube.begin(), cube.end(), [](char ch) { return !std::isalpha(ch); }),
      cube.end());

  return {cube, val};
}

auto sum_two() -> long
{
  return std::accumulate(mults.begin(), mults.end(), 0, std::plus<>());
}
auto main() -> int
{
  Game game {};
  for (auto& round : load_lines("d2.txt")) {
    parse_two(round);
  }

  std::cout << sum_two();
  return 0;
}
