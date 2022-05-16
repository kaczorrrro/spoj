//StringMerge
#include <iostream>

int main() {
  {int n; std::cin >> n;}
  std::string a, b;
  while (std::cin >> a >> b) {
    std::string ret;
    for (int i = 0; i < a.size() && i < b.size(); i++) {
      ret.push_back(a[i]);
      ret.push_back(b[i]);
    }
    std::cout << ret << std::endl;
  }
}