#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'largestRectangle' function below.
 *
 * The function is expected to return a LONG_INTEGER.
 * The function accepts INTEGER_ARRAY h as parameter.
 */

template <typename Cmp = std::less<>>
struct Heap {
  Heap(Cmp cmp = Cmp{}): cmp(std::move(cmp)) { }
  void Insert(int value) {
    data.push_back(value);
    int pos = data.size() - 1;
    PropagateUp(pos);
  }

  void Delete(int value) {
    int pos = std::find(data.begin(), data.end(), value) - data.begin();
    if (pos == data.size() - 1) {
      data.pop_back();
      return;
    }
    while (pos) {
      std::swap(data[pos], data[up(pos)]);
      pos = up(pos);
    }

    data[pos] = data.back();
    data.pop_back();

    PropagateDown(pos);
  }

  int Top() {
    return data.front();
  }

  void PrintHeap() {
    auto is_pow_2 = [](int i){
      return (i & (i - 1)) == 0;
    };

    int num_levels = int(ceil(log2(data.size() + 2)));

    int width = 1 << (num_levels + 1);
    for (int i = 0; i < data.size(); i++) {
      std::cout << std::setw(width / 2) << data[i] << std::string(width/2, ' ');
      if (is_pow_2(i + 2)) {
        width /= 2;
        std::cout << std::endl;
      }
    }
  }

  void PropagateUp(int pos) {
    while (cmp(data[pos], data[up(pos)])) {
      std::swap(data[pos], data[up(pos)]);
      pos = up(pos);
    }
  }

  void PropagateDown(int pos) {
    while (true) {
      int l = down_l(pos);
      int r = down_r(pos);

      bool go_l = l < data.size() && cmp(data.at(l), data.at(pos));
      bool go_r = r < data.size() && cmp(data.at(r), data.at(pos));

      int target_pos = -1;
      if (go_l && go_r) target_pos = cmp(data.at(r), data.at(l)) ? r : l;
      else if (go_l)    target_pos = l;
      else if (go_r)    target_pos = r;
      else break;

      std::swap(data[pos], data[target_pos]);
      pos = target_pos;
    }
  }

  int up(int pos) { return (pos - 1) / 2; }
  int down_l(int pos) { return pos * 2 + 1; }
  int down_r(int pos) { return pos * 2 + 2; }

  std::vector<int> data;
  Cmp cmp;
};

std::vector<int> findClosestSmaller(const vector<int>& v) {
  std::vector<int> ret (v.size());
  for (int i = v.size() - 1; i >= 0; i--) {
    int cur = v[i];
    int candidate_index = i + 1;
    while (candidate_index < v.size()) {
      if (v[candidate_index] < cur) break;
      else candidate_index = ret[candidate_index];
    }
    ret[i] = candidate_index;
  }
  return ret;
}


long largestRectangle(vector<int> h) {
  std::vector<int> smaller_pos = findClosestSmaller(h);
  int n = h.size();
  int64_t max_area = 0;
  for (int start = 0; start < n; start++) {
//    if (start > 0 && h[start] < h[start - 1])
//      continue;
    int min_h = h[start];
    int tmp = start;
    while (true) {
      int end = smaller_pos[tmp];
      tmp = end;
      max_area = std::max((int64_t)min_h * (end - start), max_area);
      if (end == n) break;
      assert(min_h > h[end]);
      min_h = std::min(min_h, h[end]);
    }
  }
  return max_area;
}



void test_closest_smaller() {
  int test_size = 1000;
  std::mt19937 engine;
  std::uniform_int_distribution<int> dist(0, 1000);
  std::vector<int> test_data;
  for (int i = 0; i < test_size; i++)
    test_data.push_back(dist(engine));

  std::vector<int> smaller_pos = findClosestSmaller(test_data);
  for (int i = 0; i < test_size; i++) {
    for (int j = i + 1; j < test_size; j++) {
      if (test_data[j] < test_data[i]) {
        assert(smaller_pos[i] == j);
        break;
      }
    }
  }


}

int main()
{
//  test_closest_smaller();
  std::cout << largestRectangle({11, 11, 10, 10, 10}) << std::endl;
}

string ltrim(const string &str) {
  string s(str);

  s.erase(
      s.begin(),
      find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
  );

  return s;
}

string rtrim(const string &str) {
  string s(str);

  s.erase(
      find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
      s.end()
  );

  return s;
}

vector<string> split(const string &str) {
  vector<string> tokens;

  string::size_type start = 0;
  string::size_type end = 0;

  while ((end = str.find(" ", start)) != string::npos) {
    tokens.push_back(str.substr(start, end - start));

    start = end + 1;
  }

  tokens.push_back(str.substr(start));

  return tokens;
}
