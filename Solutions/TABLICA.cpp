#include <iostream>
#include <vector>

int main() {
  std::vector<int> data;
  int n;
  while(std::cin >> n) data.push_back(n);
  for (auto it = data.rbegin(); it != data.rend(); ++it)
    std::cout << *it << ' ';
}
