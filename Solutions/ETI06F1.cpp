// ETI06F1 - Pole pewnego koła
#include <iostream>
#include <math.h>

int main() {
  double r, d;
  std::cin >> r >> d;
  d = d/2;

  double angle = std::asin(d / r);
  double new_r = std::cos(angle) * r;
  std::cout << std::fixed << new_r * new_r * M_PI << std::endl;
}