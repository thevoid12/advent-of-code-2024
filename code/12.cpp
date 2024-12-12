#include <iostream>
#include <vector>
#include <fstream>
#define lli long long
using namespace std;

vector<vector<char>> ip;      // Topographic map
vector<vector<bool>> visited; // Tracks visited positions
unordered_map<char, lli> mpp;
void parseInput()
{
  ifstream f("../input/12.txt");
  string s;
  while (getline(f, s))
  {
    vector<char> a;
    for (char c : s)
    {
      mpp[c] = mpp[c] + 1;
      a.push_back(c);
    }
    ip.push_back(a);
  }
  visited = vector<vector<bool>>(ip.size(), vector<bool>(ip[0].size(), false)); // we can avoid it by updating the same map for memory efficiency, but i dont care about memory:)
}

bool isboundary(lli i, lli j)
{
  if (i >= 0 && i < ip.size() && j >= 0 && j < ip[0].size())
    return true;
  return false;
}

// recurse helps in calculating the perimeter by doing dfs
lli recurse(lli i, lli j, char c, lli &count)
{

  if (!isboundary(i, j) || ip[i][j] != c)
  {
    return 1;
  }
  if (isboundary(i, j) && visited[i][j])
  {
    return 0;
  }
  count++;
  visited[i][j] = true;
  lli left = recurse(i, j - 1, c, count);
  lli right = recurse(i, j + 1, c, count);
  lli down = recurse(i + 1, j, c, count);
  lli up = recurse(i - 1, j, c, count);

  return left + right + down + up;
}

lli partA()
{
  lli total = 0;

  for (lli i = 0; i < ip.size(); i++)
  {
    for (lli j = 0; j < ip[i].size(); j++)
    {
      if (!visited[i][j])
      {
        lli count = 0;
        lli perimeter = recurse(i, j, ip[i][j], count);

        cout << ip[i][j] << " " << count << endl;
        total += perimeter * count;
      }
    }
  }
  // cout << "*********************";
  // for (auto i : total_p)
  // {
  //   lli area = mpp[i.first];
  //   total += i.second * area;
  //   cout << i.first << " " << i.second << endl;
  // }

  return total;
}
int main()
{
  parseInput();

  cout << partA() << endl;
  return 0;
}
