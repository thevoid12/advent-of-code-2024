#include <iostream>
#include <string>
#include <fstream>
#include <cctype>
using namespace std;

vector<vector<char>> parseInput()
{
  vector<vector<char>> input;
  ifstream f("../input/4.txt");
  if (!f)
  {
    cerr << "Unable to open file." << endl;
    return input;
  }

  string ip = "";
  while (getline(f, ip))
  {
    vector<char> row;
    for (int i = 0; i < ip.size(); i++)
    {
      row.push_back(ip[i]);
    }
    input.push_back(row);
  }
  return input;
}

// bool isboundary(int i, int j, int row, int col, string dir)
// {
//   if (dir == "left" && i - 3 >= 0)
//   {
//     return true;
//   }
//   else if (dir == "right" && i + 3 <= row - 1)
//   {
//     return true;
//   }
//   else if (dir == "up" && j - 3 >= 0)
//   {
//     return true;
//   }
//   else if (dir == "down" && j + 3 <= col - 1)
//   {
//     return true;
//   }
//   else if (dir == "d1" && i + 3 <= row - 1 && j + 3 <= col - 1)
//   {
//     return true;
//   }
//   else if (dir == "d2" && i - 3 >= 0 && j - 3 >= 0)
//   {
//     return true;
//   }
//   else if (dir == "d3" && i - 3 >= 0 && j + 3 <= col - 1)
//   {
//     return true;
//   }
//   else if (dir == "d4" && i + 3 <= row - 1 && j - 3 >= 0)
//   {
//     return true;
//   }
//   return false;
// }

bool validBoundary(int i, int j, int row, int col)
{
  if (i >= 0 && i <= row - 1 && j >= 0 && j <= col - 1)
  {
    return true;
  }
  return false;
}

bool isXmas(vector<vector<char>> ip, int iold, int inew, int jold, int jnew)
{
  string s = "";
  // Traverse 4 steps
  for (int step = 0; step < 4; step++)
  {
    int ni = iold + step * (inew - iold) / 3;
    int nj = jold + step * (jnew - jold) / 3;

    if (!validBoundary(ni, nj, ip.size(), ip[0].size()))
    {
      return false;
    }
    s += ip[ni][nj];
  }

  return s == "XMAS";
}

int part1(vector<vector<char>> ip, vector<pair<int, int>> dir)
{
  int ans = 0;
  for (int i = 0; i < ip.size(); i++)
  {
    for (int j = 0; j < ip[i].size(); j++)
    {
      if (ip[i][j] == 'X')
      {
        // traverse all 8 direction
        for (int k = 0; k < dir.size(); k++)
        {

          if (validBoundary(dir[k].first + i, dir[k].second + j, ip.size(), ip[i].size()))
          {
            // cout << " the dir is:" << dir[k].first << "," << dir[k].second << endl;
            // cout << "iold:" << i << "inew:" << dir[k].first + i << "jold:" << j << "jnew:" << dir[k].second + j << endl;
            if (isXmas(ip, i, dir[k].first + i, j, dir[k].second + j))
            {
              ans++;
            }
          }
        }
      }
    }
  }
  return ans;
}
int main()
{
  vector<vector<char>> ip;

  vector<pair<int, int>> dir{
      {-3, 0}, {3, 0}, {0, -3}, {0, 3}, {3, 3}, {-3, -3}, {3, -3}, {-3, 3}};

  ip = parseInput();
  int result;
  result = part1(ip, dir);
  cout << result;
  return 0;
}
