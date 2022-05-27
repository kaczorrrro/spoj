#include <bits/stdc++.h>
#include <unordered_map>
using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'minimumMoves' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. STRING_ARRAY grid
 *  2. INTEGER startX
 *  3. INTEGER startY
 *  4. INTEGER goalX
 *  5. INTEGER goalY
 */

struct Point {
  int y;
  int x;
};

Point operator+(Point l, Point r) {
  return Point{l.y + r.y, l.x + r.x};
}
bool operator==(Point l, Point r) {
  return l.y == r.y && l.x == r.x;
}

namespace std {
template <>
struct hash<Point> {
  size_t operator()(const Point& p) const {
    return p.x + (p.y << 16);
  }
};
}

struct PointWithSteps {
  Point p;
  int steps;
};
bool operator<(const PointWithSteps& l, const PointWithSteps& r) {
  return l.steps > r.steps;
}


int minimumMoves(vector<string> grid, int startX, int startY, int goalX, int goalY) {
  int n = grid.size();
  auto ok = [&grid, n](Point p){
    if (p.y < 0 || p.y >= n || p.x < 0 || p.x >= n)
      return false;
    return grid[p.x][p.y] == '.';
  };
  Point goal {goalY, goalX};
  std::priority_queue<PointWithSteps> queue;
  auto schedule_moves = [&ok, &queue](PointWithSteps ps, Point d) {
    ps.steps++;
    while (ok(ps.p + d)) {
      ps.p = ps.p + d;
      queue.push(ps);
    }
  };

  std::unordered_set<Point> visited;
  queue.push(PointWithSteps{{startY, startX}, 0});
  while (!queue.empty()) {
    PointWithSteps ps = queue.top();
    queue.pop();
    if (visited.count(ps.p)) continue;
    else visited.insert(ps.p);
    std::cout << "Visiting " << ps.p.y << " " << ps.p.x << std::endl;

    if (ps.p == goal)
      return ps.steps;


    schedule_moves(ps, { 0, -1});
    schedule_moves(ps, { 0,  1});
    schedule_moves(ps, {-1,  0});
    schedule_moves(ps, { 1,  0});
  }
  *(int*)(1) = 1;
  return 0;
}

int main()
{
  string n_temp;
  getline(cin, n_temp);

  int n = stoi(ltrim(rtrim(n_temp)));

  vector<string> grid(n);

  for (int i = 0; i < n; i++) {
    string grid_item;
    getline(cin, grid_item);

    grid[i] = grid_item;
  }

  string first_multiple_input_temp;
  getline(cin, first_multiple_input_temp);

  vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

  int startX = stoi(first_multiple_input[0]);

  int startY = stoi(first_multiple_input[1]);

  int goalX = stoi(first_multiple_input[2]);

  int goalY = stoi(first_multiple_input[3]);

  int result = minimumMoves(grid, startX, startY, goalX, goalY);

  std::cout << result << std::endl;
  return 0;
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
