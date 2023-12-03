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

int main()
{
  auto lines = load_lines("d1.txt");

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
