#include <iostream>
#include <vector>
#include <fstream>
#include <set>
using namespace std;

pair<int, int> parseInput(vector<vector<char>> &ip)
{
  pair<int, int> start = {0, 0};
  ifstream f("../input/6.txt");

  if (!f)
  {
    cout << "coudn't open the text file";
    return start;
  }

  string s;
  int row = 0;
  while (getline(f, s))
  {

    vector<char> a;
    for (int i = 0; i < s.size(); i++)
    {
      if (s[i] == '^')
      {
        start.first = row;
        start.second = i;
      }
      a.push_back(s[i]);
    }
    row++;
    ip.push_back(a);
  }
  return start;
}

bool IsExit(int i, int j, vector<vector<char>> ip)
{ // isExit checks if the number exits the boundary

  int row = ip.size();
  int col = ip[0].size();

  if (i >= 0 && i < row && j >= 0 && j < col)
  {
    return false;
  }

  return true;
}

string NewDir(string curdir)
{
  if (curdir == "up")
  {
    return "right";
  }
  if (curdir == "right")
  {
    return "down";
  }
  if (curdir == "down")
  {
    return "left";
  }

  return "up";
}
int calcmatrix(vector<vector<char>> ip)
{
  int count = 0;
  for (int i = 0; i < ip.size(); i++)
  {
    for (int j = 0; j < ip[i].size(); j++)
    {
      //  cout << ip[i][j] << " ";
      if (ip[i][j] == 'x')
      {

        count++;
      }
    }
    //  cout << endl;
  }
  return count;
}
void partA(vector<vector<char>> &ip, pair<int, int> start)
{
  int icurpos = start.first;
  int jcurpos = start.second;
  string curDir = "up";
  while (!IsExit(icurpos, jcurpos, ip))
  {
    if (ip[icurpos][jcurpos] == '#')
    {
      if (curDir == "up")
      {
        curDir = NewDir(curDir);
        icurpos++;
        calcmatrix(ip);
        continue;
      }
      else if (curDir == "down")
      {
        curDir = NewDir(curDir);
        icurpos--;
        calcmatrix(ip);
        continue;
      }
      else if (curDir == "left")
      {
        curDir = NewDir(curDir);
        jcurpos++;
        calcmatrix(ip);
        continue;
      }
      else if (curDir == "right")
      {
        curDir = NewDir(curDir);
        jcurpos--;
        calcmatrix(ip);
        continue;
      }
    }
    ip[icurpos][jcurpos] = 'x';
    if (curDir == "up")
    {
      icurpos--;
      continue;
    }
    if (curDir == "down")
    {
      icurpos++;
      continue;
    }
    if (curDir == "left")
    {
      jcurpos--;
      continue;
    }
    if (curDir == "right")
    {
      jcurpos++;
      continue;
    }
  }
}

int partB(vector<vector<char>> ip, pair<int, int> start)
{
  int ans = 0;

  for (int b1 = 0; b1 < ip.size(); b1++)
  {
    bool f = false;
    int pos1, pos2 = -1;
    for (int b2 = 0; b2 < ip[b1].size(); b2++)
    {
      if (b1 == start.first && b2 == start.second)
        continue;

      if (ip[b1][b2] == 'x')
      {
        pos1 = b1;
        pos2 = b2;
        ip[b1][b2] = '#';
        f = true;
      }

      if (!f)
      {
        continue;
      }
      int icurpos = start.first;
      int jcurpos = start.second;
      set<pair<pair<int, int>, string>> st;
      string curDir = "up";
      while (!IsExit(icurpos, jcurpos, ip))
      {
        auto it = st.find({{icurpos, jcurpos}, curDir});
        if (it != st.end())
        {
          ans++;
          break;
        }
        if (ip[icurpos][jcurpos] == '#')
        {
          if (curDir == "up")
          {
            curDir = NewDir(curDir);
            icurpos++;
            //  calcmatrix(ip);
            continue;
          }
          else if (curDir == "down")
          {
            curDir = NewDir(curDir);
            icurpos--;
            // calcmatrix(ip);
            continue;
          }
          else if (curDir == "left")
          {
            curDir = NewDir(curDir);
            jcurpos++;
            // calcmatrix(ip);
            continue;
          }
          else if (curDir == "right")
          {
            curDir = NewDir(curDir);
            jcurpos--;
            // calcmatrix(ip);
            continue;
          }
        }
        ip[icurpos][jcurpos] = 'x';
        st.insert({{icurpos, jcurpos}, curDir});
        if (curDir == "up")
        {
          icurpos--;
          continue;
        }
        if (curDir == "down")
        {
          icurpos++;
          continue;
        }
        if (curDir == "left")
        {
          jcurpos--;
          continue;
        }
        if (curDir == "right")
        {
          jcurpos++;
          continue;
        }
      }
      ip[pos1][pos2] = 'x';
    }
  }
  return ans;
}

int main()
{
  int ans;
  vector<vector<char>> ip;
  pair<int, int> start = parseInput(ip);
  partA(ip, start);
  ans = calcmatrix(ip);
  cout << ans << endl;
  ans = partB(ip, start);
  cout << ans << endl;
  return 0;
}
