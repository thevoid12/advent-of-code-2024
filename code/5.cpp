#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;
unordered_map<string, bool> mpp;
vector<vector<int>> ip;
vector<vector<int>> ip2;
void parseInput()
{
  ifstream f("../input/5.txt");

  if (!f)
  {
    cout << "coudn't open the text file";
    return;
  }

  string s;
  bool mapflag = false;
  while (getline(f, s))
  {
    if (s == "")
    {
      mapflag = true;
      continue;
    }
    if (!mapflag)
    {
      mpp[s] = true;
    }
    else
    {
      vector<int> a;
      string s1 = "";
      for (int i = 0; i < s.size(); i++)
      {
        if (s[i] == ',')
        {
          a.push_back(stoi(s1));
          s1 = "";
          continue;
        }
        s1 += s[i];
      }
      if (s1 != "")
      {
        a.push_back(stoi(s1));
      }
      ip.push_back(a);
    }
  }
}

int part2()
{
  int ans = 0;

  for (int i = 0; i < ip2.size(); i++)
  {
    //  bool flag = true;

    for (int j = 0; j < ip2[i].size() - 1; j++)
    {
      for (int k = j + 1; k < ip2[i].size(); k++)
      {
        string r = to_string(ip2[i][j]) + "|" + to_string(ip2[i][k]);
        if (!mpp[r])
        {
          swap(ip2[i][j], ip2[i][k]);
        }
      }
    }

    ans += ip2[i][(ip2[i].size()) / 2];
  }
  return ans;
}

int part1()
{
  int ans = 0;

  for (int i = 0; i < ip.size(); i++)
  {
    bool flag = true;

    for (int j = 0; j < ip[i].size() - 1; j++)
    {
      for (int k = j + 1; k < ip[i].size(); k++)
      {
        string r = to_string(ip[i][j]) + "|" + to_string(ip[i][k]);
        if (!mpp[r])
        {
          flag = false;
          break;
        }
      }
    }
    if (flag)
    {
      ans += ip[i][(ip[i].size()) / 2];
    }
    else
    {
      ip2.push_back(ip[i]);
    }
  }
  return ans;
}

int main()
{
  parseInput();
  int ans, ans1;
  ans = part1();
  cout << ans << endl;
  ans1 = part2();
  cout << ans1 << endl;
  return 0;
}
