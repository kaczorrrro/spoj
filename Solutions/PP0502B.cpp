// PP0502B - Tablice
#include <iostream>
#include <vector>

int main() {
  int cases;
  std::cin >> cases;
  for (int c = 0; c < cases; c++) {
    int n;
    std::cin >> n;
    std::vector<int> vec;
    vec.reserve(100);
    for (int i = 0; i < n; i++) {
      vec.push_back(0);
      std::cin >> vec.back();
    }
    for (auto it = vec.rbegin(); it != vec.rend(); ++it) {
      std::cout << *it << " ";
    }
    std::cout << std::endl;
  }
}