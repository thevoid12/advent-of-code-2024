#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#define lli long long
using namespace std;

vector<pair<int, int>> ip;
vector<pair<int, int>> v;
unordered_map<string, int> mpp;
int iedge = 11;
int jedge = 7;
void parseInput()
{
  ifstream f("../input/14.txt");
  string line;
  while (getline(f, line))
  {
    stringstream ss(line);
    ss.ignore(2); // p=
    lli x, y;
    ss >> x;
    ss.ignore(1); //,
    ss >> y;
    ss.ignore(3); // v=
    lli vx1, vx2;
    ss >> vx1;
    ss.ignore(1);
    ss >> vx2;
    ip.emplace_back(x, y);
    v.emplace_back(vx1, vx2);
    mpp[to_string(x) + "," + to_string(y)]++;
  }
}
bool iboundary(int i)
{
  if (i >= 0 && i < iedge)
  {
    return true;
  }
  return false;
}
bool jboundary(int j)
{
  if (j >= 0 && j < jedge)
  {
    return true;
  }
  return false;
}

int quadrant(int i, int j, int midx, int midy)
{
  if (i >= 0 && i < midx && j >= 0 && j < midy)
  {
    return 1;
  }
  else if (i > midx && i < iedge && j > midy && j < jedge)
  {
    return 4;
  }
  else if (i > midx && i < iedge && j > 0 && j < midy)
  {
    return 2;
  }
  else if (i >= 0 && i < midx && j > midy && j < jedge)
  {
    return 3;
  }
  else
    return 5;
}
pair<int, int> calc(int i, int j, int vx1, int vy1)
{
  i += vx1;
  j += vy1;
  if (!iboundary(i))
  {
    i = abs(iedge - abs(i));
  }
  if (!jboundary(j))
  {
    j = abs(jedge - abs(j));
  }
  return {i, j};
}
int part1()
{
  vector<pair<int, int>> res;
  for (int i = 0; i < ip.size(); i++)
  {
    // move 100 times for each pair. betterment: we can use dp to check if we reach the same spot
    int j = 0;
    pair<int, int> p1 = {ip[i].first, ip[i].second};

    while (j < 100)
    {
      p1 = calc(p1.first, p1.second, v[i].first, v[i].second);
      j++;
    }

    res.emplace_back(p1);
  }

  int midi = (iedge - 1) / 2;
  int midj = (jedge - 1) / 2;
  int q1 = 0, q2 = 0, q3 = 0, q4 = 0;
  for (pair<int, int> p : res)
  {
    int q = quadrant(p.first, p.second, midi, midj);
    if (q == 5)
      continue;
    else if (q == 1)
    {
    }
  }
  return 0;
}
int main()
{
  parseInput();
  part1();
  return 0;
}
