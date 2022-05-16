// Sort 1
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>

struct Point {
  int x;
  int y;
  // Short string optimization should make this quite cheap to move around
  std::string name;

  int dist2() const {
    return x*x + y*y;
  }
};
std::ostream& operator<<(std::ostream& out, const Point& p) {
  return out << p.name << " " << p.x << " " << p.y;
}

void process_case() {
  std::vector<Point> data;
  int n_points;
  std::cin >> n_points;
  for (int i = 0; i < n_points; i++) {
    Point p;
    std::cin >> p.name >> p.x >> p.y;
    data.push_back(std::move(p));
  }
  std::sort(data.begin(), data.end(), [](const Point& a, const Point& b) {
    return a.dist2() < b.dist2();
  });
  for (const Point& p : data)
    std::cout << p << std::endl;
}

int main() {
  int n;
  std::cin >> n;
  for (int i = 0; i < n; i++)
    process_case();
}