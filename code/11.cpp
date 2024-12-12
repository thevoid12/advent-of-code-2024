// today's question is the perfect use case to use a linked list for most optimal approach
// but I am brute forcing it. TODO solve using a linked list on the weekends
#include <iostream>
#include <vector>
#include <fstream>
#define lli long long
using namespace std;

vector<string> ip;

void parseInput()
{
  ifstream f("../input/11.txt");
  string s;
  while (getline(f, s))
  {
    string temp = "";
    for (char c : s)
    {
      if (c == ' ')
      {
        ip.push_back(temp);
        temp = "";
      }
      else
      {
        temp += c;
      }
    }
    if (temp != " ")
    {
      ip.push_back(temp);
    }
  }
}
void part1()
{
  // for (string &val : ip) // using & to fetch values in a vector by reference this change in val will reflect in original vector
  // {
  //   long long a = stoll(val);
  //   if (a == 0)
  //   {
  //     val = to_string(1);
  //   }
  //   else if (val.size() % 2 == 0)
  //   {
  //     int mid = val.size() / 2;
  //     long long left = stoll(val.substr(0, mid));
  //     long long right = stoll(val.substr(mid + 1));
  //     val=left;

  //   }
  // }
  int sz = ip.size();
  for (size_t i = 0; i < sz; i++) // Use a standard loop for safe modification
  {
    string &val = ip[i]; // using & to fetch values in a vector by reference this change in val will reflect in original vector
    long long a = stoll(val);
    if (a == 0)
    {
      val = to_string(1);
    }
    else if (val.size() % 2 == 0)
    {
      int mid = val.size() / 2;
      long long left = stoll(val.substr(0, mid));
      long long right = stoll(val.substr(mid));

      val = to_string(left); // Update current element

      // Insert the right part as a new element
      ip.insert(ip.begin() + i + 1, to_string(right));

      // Increment index to skip over the newly inserted element
    }
    else
    {
      long long mul = stoll(val) * 2024;
      val = to_string(mul);
    }
  }
}

int recurse(unordered_map<lli, lli> cache, int round, lli val)
{
  if (round == 0)
  {
    return 1; // atleast 1 element is there
  }
  if (cache[val] != 0) // dp
  {
    return cache[val];
  }

  int total;
  if (val == 0)
  {
    total = recurse(cache, round - 1, 1);
  }
  if (to_string(val).size() % 2 == 0)
  {
    int mid = to_string(val).size() / 2;
    long long left = stoll(to_string(val).substr(0, mid));
    long long right = stoll(to_string(val).substr(mid));
    lli leftrecurse = recurse(cache, round - 1, left);
    lli rightrecurse = recurse(cache, round - 1, right);
    total = leftrecurse + rightrecurse;
  }
  else
  {
    total = recurse(cache, round - 1, val * 2024);
  }

  cache[val] = total;
  return total;
}
int solve(unordered_map<lli, lli> cache, int round)
{
  int total = 0;
  for (string val : ip)
  {
    total += recurse(cache, round, stoll(val));
  }
  return total;
}
int main()
{
  unordered_map<lli, lli> cache;
  parseInput();
  int ans;
  ans = solve(cache, 5);
  cout << ans;
  // for (int j = 0; j < 25; j++)
  // {
  //   part1();
  // }

  // cout << ip.size() << endl;
  // for (int j = 0; j < 50; j++)
  // {
  //   part1();
  // }
  // cout << ip.size() << endl;
  return 0;
}
