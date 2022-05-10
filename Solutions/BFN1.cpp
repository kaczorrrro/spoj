#include <iostream>

struct Result {
  int value;
  int steps;
};

Result iterate_for_palindrome(int value) {
  int steps = 0;
  while (true) {
    std::string val_str = std::to_string(value);
    std::string val_rev (val_str.rbegin(), val_str.rend());
    if (val_str == val_rev) {
      return Result{value, steps};
    }
    value += std::stoi(val_rev);
    steps++;
  }
}

int main() {
  {int n; std::cin >> n;}
  int val;
  while (std::cin >> val) {
    Result r = iterate_for_palindrome(val);
    std::cout << r.value << " " << r.steps << std::endl;
  }
}