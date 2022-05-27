#include <bits/stdc++.h>

struct Int {
  int val;
  int steps;
};


int downToZero(int n) {
  auto cmp = [](Int a, Int b) { return a.steps > b.steps; };
  std::priority_queue<Int, std::vector<Int>, decltype(cmp)> queue (cmp);
  auto push_factorizations = [&queue](int n, int steps) {
    int max = (int)std::sqrt(n);
    for (int i = 2; i <= max; i++)
      if (n % i == 0) queue.push({n / i, steps+1});
  };

  std::unordered_set<int> seen;
  queue.push({n, 0});
  while (!queue.empty()) {
    Int n = queue.top();
    queue.pop();
    if (seen.count(n.val)) continue;
    else seen.insert(n.val);
    if (n.val == 0)
      return n.steps;
    push_factorizations(n.val, n.steps);
    queue.push({n.val - 1, n.steps + 1});
  }
  return -1;
}

int main() {
//  downToZero(16);
  for (int i = 0; i <= 32; i++)
    std::cout << i << " -> " << downToZero(i) << std::endl;
}