#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

vector<vector<int>> ip;       // Topographic map
vector<vector<bool>> visited; // Tracks visited positions

void parseInput()
{
  ifstream f("../input/10.txt");
  string s;
  while (getline(f, s))
  {
    vector<int> a;
    for (char c : s)
    {
      if (isdigit(c))
      {
        a.push_back(c - '0');
      }
      else
      {
        a.push_back(-1); // Mark impassable tiles
      }
    }
    ip.push_back(a);
  }
  visited = vector<vector<bool>>(ip.size(), vector<bool>(ip[0].size(), false));
}

bool isBoundary(int i, int j)
{
  return i >= 0 && i < ip.size() && j >= 0 && j < ip[0].size();
}

int recurse(int i, int j, int cur)
{
  if (!isBoundary(i, j) || visited[i][j] || ip[i][j] != cur)
  {
    return 0;
  }
  visited[i][j] = true; // Mark position as visited

  if (ip[i][j] == 9)
  {
    return 1; // Found a valid hiking trail endpoint
  }

  // Explore all four directions
  int left = recurse(i, j - 1, cur + 1);
  int right = recurse(i, j + 1, cur + 1);
  int down = recurse(i + 1, j, cur + 1);
  int up = recurse(i - 1, j, cur + 1);

  return left + right + down + up;
}

int recurseB(int i, int j, int cur)
{
  if (!isBoundary(i, j) || visited[i][j] || ip[i][j] != cur)
  {
    return 0;
  }

  if (ip[i][j] == 9)
  {
    return 1; // Found a valid hiking trail endpoint
  }

  // Explore all four directions
  int left = recurseB(i, j - 1, cur + 1);
  int right = recurseB(i, j + 1, cur + 1);
  int down = recurseB(i + 1, j, cur + 1);
  int up = recurseB(i - 1, j, cur + 1);

  return left + right + down + up;
}

int partA()
{
  int res = 0;
  for (int i = 0; i < ip.size(); i++)
  {
    for (int j = 0; j < ip[i].size(); j++)
    {
      if (ip[i][j] == 0)
      { // Check if it's a trailhead
        // Reset the visited matrix for each trailhead
        fill(visited.begin(), visited.end(), vector<bool>(ip[0].size(), false));
        int ans = recurse(i, j, 0);
        cout << "Trailhead at (" << i << ", " << j << ") -> " << ans << endl;
        res += ans;
      }
    }
  }
  return res;
}

int partB()
{
  visited = vector<vector<bool>>(ip.size(), vector<bool>(ip[0].size(), false));

  int res = 0;
  for (int i = 0; i < ip.size(); i++)
  {
    for (int j = 0; j < ip[i].size(); j++)
    {
      if (ip[i][j] == 0)
      { // Check if it's a trailhead
        // Reset the visited matrix for each trailhead
        fill(visited.begin(), visited.end(), vector<bool>(ip[0].size(), false));
        int ans = recurseB(i, j, 0);
        cout << "Trailhead at (" << i << ", " << j << ") -> " << ans << endl;
        res += ans;
      }
    }
  }
  return res;
}

int main()
{
  parseInput();
  int ans = partA();
  cout << "Total Score: " << ans << endl;
  ans = partB();
  cout << "Total Score: " << ans << endl;

  return 0;
}
