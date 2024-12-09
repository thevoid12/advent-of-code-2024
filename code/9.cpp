#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

vector<int> a;
string parseInput()
{
  ifstream f("../input/9.txt");
  string s;
  string temp;
  while (getline(f, temp))
  {
    s += temp;
  }

  return s;
}

void processIp(string s)
{
  int idx = 0;
  for (long long i = 0; i < s.size(); i++)
  {
    int num;
    num = s[i] - '0'; // char to int
    if (i % 2 == 0)
    {

      for (int j = 0; j < num; j++)
      {
        a.push_back(idx);
      }
      idx++;
    }
    else
    {
      for (int j = 0; j < num; j++)
      {
        a.push_back(-1);
      }
    }
  }
}

void rearrangeIp()
{
  int i = 0, j = a.size() - 1;
  while (i < j)
  {
    // Find the leftmost free space
    while (i < j && a[i] != -1)
      i++;
    // Find the rightmost file block
    while (i < j && a[j] == -1)
      j--;

    // Swap if valid indices are found
    if (i < j)
    {
      swap(a[i], a[j]);
      i++;
      j--;
    }
  }
}

// using 2 pointer approach to solve A
long long partA()
{
  long long res = 0;
  for (int i = 0; i < a.size(); i++)
  {
    if (a[i] == -1)
    {
      break;
    }
    res += ((a[i]) * i);
  }

  return res;
}

int main()
{
  string s;
  s = parseInput();
  // cout << s << endl;
  string s1;
  processIp(s);
  for (int i = 0; i < a.size(); i++)
  {
    cout << a[i] << " ";
  }
  cout << endl;
  cout << "***************************************************************" << endl;
  // cout << s1 << endl;
  string sp;
  rearrangeIp();
  for (int i = 0; i < a.size(); i++)
  {
    cout << a[i] << " ";
  }
  cout << "***************************************************************" << endl;

  long long res;
  res = partA();
  cout << res << endl;
}
