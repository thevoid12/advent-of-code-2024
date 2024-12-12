// today's question is the perfect use case to use a linked list for most optimal approach
// but I am brute forcing it. TODO solve using a linked list on the weekends
#include <iostream>
#include <vector>
#include <fstream>
#define lli long long
using namespace std;

vector<string> ip;

struct hash_pair
{
  template <class T1, class T2>
  size_t operator()(const pair<T1, T2> &p) const
  {
    auto hash1 = hash<T1>{}(p.first);
    auto hash2 = hash<T2>{}(p.second);
    return hash1 ^ hash2; // Combine the hashes
  }
};

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

int recurse(unordered_map<pair<int, lli>, lli, hash_pair> &cache, int round, lli val)
{
  if (round == 0)
  {
    return 1; // Base case
  }

  auto key = make_pair(round, val);
  if (cache.find(key) != cache.end())
  {
    return cache[key]; // Memoized result
  }

  int total = 0; // Initialize total
  string val_str = to_string(val);

  if (val == 0)
  {
    total = recurse(cache, round - 1, 1);
  }
  else if (val_str.size() % 2 == 0)
  {
    int mid = val_str.size() / 2;
    long long left = stoll(val_str.substr(0, mid));
    long long right = stoll(val_str.substr(mid));
    total = recurse(cache, round - 1, left) + recurse(cache, round - 1, right);
  }
  else
  {
    total = recurse(cache, round - 1, val * 2024);
  }

  cache[key] = total; // Memoize the result
  return total;
}
int solve(unordered_map<pair<int, lli>, lli, hash_pair> &cache, int round)
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
  unordered_map<pair<int, lli>, lli, hash_pair> cache;
  parseInput();
  int ans;
  ans = solve(cache, 25);
  cout << ans << endl;
  cout << ans << endl;
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
