#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

vector<long long> a;
vector<vector<long long>> ip;
void parseInput()
{
  ifstream f("../input/7.txt");

  if (!f)
  {
    cout << "coudn't open the text file";
    return;
  }

  string s;
  while (getline(f, s))
  {
    string temp = "";
    vector<long long> c;
    for (int i = 0; i < s.size(); i++)
    {
      if (s[i] == ':')
      {
        a.push_back(stoll(temp));
        temp = "";
        continue;
      }
      if (s[i] == ' ' && temp != "")
      {
        c.push_back(stoll(temp));
        temp = "";
        continue;
      }
      temp += s[i];
    }
    if (temp != "")
    {
      c.push_back(stoll(temp));
    }
    // sort(c.rbegin(), c.rend());
    // std::sort(c.begin(), c.end(), std::greater<int>());
    // vector<int> tempv;
    // for (int p = c.size() - 1; p >= 0; p--)
    // {
    //   tempv.push_back(c[p]);
    // }
    ip.push_back(c);
  }

  return;
}

bool recurse(int pos, vector<long long> input, int i, long long res)
{
  if (pos == input.size())
  {
    if (res == a[i])
    {
      return true;
    }
    else
    {
      return false;
    }
  }

  bool add = recurse(pos + 1, input, i, res + input[pos]);
  bool mult = recurse(pos + 1, input, i, res * input[pos]);

  return add or mult;
}

bool recurseB(int pos, vector<long long> input, int i, long long res)
{
  if (pos == input.size())
  {
    if (res == a[i])
    {
      return true;
    }
    else
    {
      return false;
    }
  }

  bool add = recurseB(pos + 1, input, i, res + input[pos]);
  bool mult = recurseB(pos + 1, input, i, res * input[pos]);
  // sprintf(buffer, "%lld", res) + sprintf("%lld", input[pos]);
  bool concat = recurseB(pos + 1, input, i, stoll(to_string(res) + to_string(input[pos])));
  return (add or mult) or (concat);
}

long long partA()
{
  long long ans = 0;
  for (int i = 0; i < ip.size(); i++)
  {
    bool isSatisfy = false;
    if (ip[i].size() == 1 && ip[i][0] == a[i])
    {
      isSatisfy = true;
    }
    else
    {
      isSatisfy = recurse(1, ip[i], i, ip[i][0]);
    }
    if (isSatisfy)
    {
      ans += a[i];
    }
  }
  return ans;
}

long long partB()
{
  long long ans = 0;
  for (int i = 0; i < ip.size(); i++)
  {
    bool isSatisfy = false;
    if (ip[i].size() == 1 && ip[i][0] == a[i])
    {
      isSatisfy = true;
    }
    else
    {
      isSatisfy = recurseB(1, ip[i], i, ip[i][0]);
    }
    if (isSatisfy)
    {
      ans += a[i];
    }
  }
  return ans;
}

int main()
{
  long long ans = 0;
  parseInput();
  ans = partA();
  cout << ans << endl;
  ans = partB();
  cout << ans;
  return 0;
}
