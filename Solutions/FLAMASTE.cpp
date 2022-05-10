#include <iostream>
#include <sstream>

std::string compress_input(const std::string& input) {
  char last_c = '_';
  int count = 0;
  std::stringstream ss;
  auto flush_last = [&](){
    if (count == 0)      return;
    else if (count == 1) ss << last_c;
    else if (count == 2) ss << last_c << last_c;
    else                 ss << last_c << count;
  };
  for (char c : input) {
    if (c == last_c) {
      ++count;
    } else {
      flush_last();
      last_c = c;
      count = 1;
    }
  }
  flush_last();
  return ss.str();
}

int main() {
  { int n; std::cin >> n; }
  std::string input;
  while (std::cin >> input) {
    std::cout << compress_input(input) << std::endl;
  }
}