#include <bits/stdc++.h>

using namespace std;

vector<string> split_string(string);

int solve_n2(vector<int> t) {
  const int n = t.size();
  auto t_at = [n, &t](int i){ return i >= n ? t[i - n] : t[i]; };
  int best_x = 0;
  int best_sum = 0;
  for (int x = 0; x < n; x++) {
    int sum = 0;
    int smallest_margin = INT32_MAX;
    for (int i = 0; i < n; i++) {
      int additional_time = t_at(x + i) - i;
      sum += additional_time >= 0;
    }
    if (sum > best_sum) {
      best_sum = sum;
      best_x = x;
    }
  }
  return best_x; // results are 1-based
}

int solve_fast(vector<int> t) {
  const int n = t.size();
  // make sure 0 extra time are not double accounted
  std::multiset<int> x_deadlines;
  int max_extra_time = n-1;
  // x = 0, base case
  for (int i = 0; i < n; i++) {
    int additional_time = i - t[i];
    if (additional_time >= 0)
      x_deadlines.insert(additional_time + 1);
  }

  int best_x = 0;
  int best_sum = x_deadlines.size();

  int dropped_count = 0;
  for (int x = 1; x < n; x++) {
    dropped_count += x_deadlines.count(x);
    int additional_time_for_lucky_one = max_extra_time - t[x - 1];
    if (additional_time_for_lucky_one >= 0)
      x_deadlines.insert(x + additional_time_for_lucky_one + 1);
    int sum = x_deadlines.size() - dropped_count;
    if (sum > best_sum) {
      best_sum = sum;
      best_x = x;
    }
  }
  return best_x; // results are 1-based
}


int solve_faster(vector<int> t) {
  const int n = t.size();
  std::vector<int> x_changes (t.size());
  // define 2 times per studet : when he passes and when he fails
  int max_extra_time = n-1;
  // x = 0, base case
  for (int i = 0; i < n; i++) {
    int additional_time = i - t[i];
    if (additional_time >= 0)
      x_deadlines.insert(additional_time + 1);
  }

  int best_x = 0;
  int best_sum = x_deadlines.size();

  int dropped_count = 0;
  for (int x = 1; x < n; x++) {
    dropped_count += x_deadlines.count(x);
    int additional_time_for_lucky_one = max_extra_time - t[x - 1];
    if (additional_time_for_lucky_one >= 0)
      x_deadlines.insert(x + additional_time_for_lucky_one + 1);
    int sum = x_deadlines.size() - dropped_count;
    if (sum > best_sum) {
      best_sum = sum;
      best_x = x;
    }
  }
  return best_x; // results are 1-based
}

void test_solve_fast() {
  for (int test_i = 0; test_i < 1000; test_i++) {
    std::mt19937 engine (test_i);
    std::uniform_int_distribution<int> dist (0, 100);
    std::vector<int> data (test_i / 10 + 2);
    int ref = solve_n2(data);
    int test = solve_fast(data);
    if (ref != test) {
      std::cout << "Error at " << test_i << " got " << test << " extpected " << ref << std::endl;
      for (int i : data) std::cout << i << " ";
      std::cout << std::endl;
      std::cout << solve_fast(data) << std::endl; // for debugging
      break;
    }
  }
}

int main() {
  test_solve_fast();
}
