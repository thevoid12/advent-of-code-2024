#include <iostream>
#include <vector>
#include <fstream>
#include <set>
using namespace std;
int row, col;
unordered_map<char, vector<pair<int, int>>> parseInput()
{
  unordered_map<char, vector<pair<int, int>>> mpp;
  ifstream f("../input/8.txt");
  string s;
  int i = 0;
  while (getline(f, s))
  {
    row++;
    col = 0;
    for (int j = 0; j < s.size(); j++)
    {
      col++;
      if (s[j] != '.')
      {
        vector<pair<int, int>> v1 = mpp[s[j]];
        v1.push_back({i, j});
        mpp[s[j]] = v1;
      }
    }
    i++;
  }
  return mpp;
}

bool isboundary(int i, int j)
{
  if (i >= 0 && i < row && j >= 0 && j < col)
  {
    return true;
  }
  return false;
}
int partA(unordered_map<char, vector<pair<int, int>>> mpp)
{
  set<pair<int, int>> s1;

  for (auto i = mpp.begin(); i != mpp.end(); i++)
  {
    vector<pair<int, int>> v1 = i->second;
    for (int j = 0; j < v1.size() - 1; j++)
    {
      for (int k = j + 1; k < v1.size(); k++)
      {
        int xdiff = v1[j].first - v1[k].first;
        int ydiff = v1[j].second - v1[k].second;
        // we need to form 2 points here apart from the 2 points.

        // add from a point and subract from a point
        int x1 = v1[j].first - xdiff;
        int y1 = v1[j].second - ydiff;

        int x2 = v1[j].first + xdiff;
        int y2 = v1[j].second + ydiff;

        int x3 = v1[k].first - xdiff;
        int y3 = v1[k].second - ydiff;

        int x4 = v1[k].first + xdiff;
        int y4 = v1[k].second + ydiff;

        if (isboundary(x1, y1) && x1 != v1[k].first && y1 != v1[k].second)
        {
          s1.insert({x1, y1});
        }
        if (isboundary(x2, y2) && x2 != v1[k].first && y2 != v1[k].second)
        {
          s1.insert({x2, y2});
        }
        if (isboundary(x3, y3) && x3 != v1[j].first && y3 != v1[j].second)
        {
          s1.insert({x3, y3});
        }
        if (isboundary(x4, y4) && x4 != v1[j].first && y4 != v1[j].second)
        {
          s1.insert({x4, y4});
        }
      }
    }
  }

  return s1.size();
}

int partB(unordered_map<char, vector<pair<int, int>>> mpp)
{
  set<pair<int, int>> s1;

  for (auto i = mpp.begin(); i != mpp.end(); i++)
  {
    vector<pair<int, int>> v1 = i->second;
    for (int j = 0; j < v1.size() - 1; j++)
    {
      for (int k = j + 1; k < v1.size(); k++)
      {
        // point come from left to right so for left point we will subract and right point we will add
        int xdiff = v1[j].first - v1[k].first;
        int ydiff = v1[j].second - v1[k].second;
        // we need to form 2 points here apart from the 2 points.

        // add from a point and subract from a point
        s1.insert({v1[j].first, v1[j].second});
        s1.insert({v1[k].first, v1[k].second});
        int mul = 1;
        bool neg = true, positive = true;
        while (true)
        {
          int x1 = v1[j].first - (xdiff * mul);
          int y1 = v1[j].second - (ydiff * mul);

          int x2 = v1[k].first + (xdiff * mul);
          int y2 = v1[k].second + (ydiff * mul);

          if (isboundary(x1, y1))
          {
            s1.insert({x1, y1});
          }
          else
          {
            neg = false;
          }
          if (isboundary(x2, y2))
          {
            s1.insert({x2, y2});
          }
          else
          {
            positive = false;
          }
          if ((neg or positive) == false)
          {
            break;
          }
          mul++;
        }
      }
    }
  }

  return s1.size();
}
int main()
{
  unordered_map<char, vector<pair<int, int>>> mpp;

  mpp = parseInput();
  int ans = partA(mpp);
  cout << ans << endl;
  ans = partB(mpp);
  cout << ans << endl;
  return 0;
}
