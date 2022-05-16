// SkarbFinder
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>

constexpr int N = 0;
constexpr int S = 1;
constexpr int W = 2;
constexpr int E = 3;


void process_case() {
  int steps;
  std::cin >> steps;
  int x = 0;
  int y = 0;
  for (int i = 0; i < steps; i++) {
    int direction, magnitude;
    std::cin >> direction >> magnitude;
    int dx, dy;
    switch (direction) {
    case N: dx =  0; dy =  1; break;
    case S: dx =  0; dy = -1; break;
    case W: dx = -1; dy =  0; break;
    case E: dx =  1; dy =  0; break;
    }
    x += dx * magnitude;
    y += dy * magnitude;
  }

  if (x == 0 && y == 0) {
    std::cout << "studnia" << std::endl;
  } else {
    if (y != 0) std::cout << (y > 0 ? N : S) << " " << std::abs(y) << std::endl;
    if (x != 0) std::cout << (x > 0 ? E : W) << " " << std::abs(x) << std::endl;
  }
}

int main() {
  int n;
  std::cin >> n;
  for (int i = 0; i < n; i++)
    process_case();
}