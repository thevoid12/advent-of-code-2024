#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;

vector<vector<int>> parseInput()
{
  vector<vector<int>> input;
  ifstream f("../input/2.txt");
  if (!f)
  {
    cerr << "Unable to open file." << endl;
    return input;
  }

  string ip;

  while (getline(f, ip))
  {
    string s = "";
    vector<int> temp;
    for (int i = 0; i < ip.size(); i++)
    {
      if (ip[i] != ' ')
      {
        s += ip[i];
      }
      else
      {
        temp.push_back(stoi(s));
        s = "";
      }
    }
    if (s != "")
    {
      temp.push_back(stoi(s));
    }
    input.push_back(temp);
  }

  return input;
}

int part1(vector<vector<int>> input)
{
  int safe = 0;

  for (int i = 0; i < input.size(); i++)
  {
    bool dec = false;
    bool ok = true;

    for (int j = 1; j < input[i].size(); j++)
    {
      int diff = 0;
      diff = (input[i][j - 1] - input[i][j]);
      if (diff < 0 && (dec == false || j == 1) && (abs(diff) >= 1 && 3 >= abs(diff)))
      {
        dec = false;
      }
      else if (diff > 0 && (dec == true || j == 1) && (abs(diff) >= 1 && 3 >= abs(diff)))
      {
        dec = true;
      }
      else
      {
        ok = false;
        break;
      }
    }
    if (ok == true)
    {
      safe = safe + 1;
    }
  }

  return safe;
}

// not the most optimal solution
int part2(vector<vector<int>> input)
{
  int safe = 0;

  for (int i = 0; i < input.size(); i++)
  {
    bool dec = false;
    bool ok = true;

    for (int j = 1; j < input[i].size(); j++)
    {
      int diff = 0;
      diff = (input[i][j - 1] - input[i][j]);
      if (diff < 0 && (dec == false || j == 1) && (abs(diff) >= 1 && 3 >= abs(diff)))
      {
        dec = false;
      }
      else if (diff > 0 && (dec == true || j == 1) && (abs(diff) >= 1 && 3 >= abs(diff)))
      {
        dec = true;
      }
      else
      {
        ok = false;
        break;
      }
    }
    if (ok == true)
    {
      safe = safe + 1;
    }
  }
}

int main()
{
  vector<vector<int>> input;
  int safe, safe2;
  input = parseInput();
  safe = part1(input);
  cout << safe << endl;
  safe2 = part2(input);
  cout << safe2;
}
