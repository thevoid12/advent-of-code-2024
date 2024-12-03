#include <iostream>
#include <string>
#include <fstream>
#include <cctype>
using namespace std;

// Function to read input from the file
string parseInput(const string &filePath)
{
  ifstream f(filePath);
  if (!f)
  {
    cerr << "Unable to open file." << endl;
    return "";
  }

  string content, line;
  while (getline(f, line))
  {
    content += line;
  }
  return content;
}

// Helper function to extract numbers from valid mul(X,Y)
bool parseMul(const string &s, size_t &i, int &result)
{
  // Ensure "mul(" prefix
  if (s.substr(i, 4) != "mul(")
    return false;
  i += 4; // Skip past "mul("

  int num1 = 0, num2 = 0;
  bool num1Valid = false, num2Valid = false;
  bool negative = false;

  // Parse first number
  if (s[i] == '-')
  {
    negative = true;
    i++;
  }
  while (i < s.size() && isdigit(s[i]))
  {
    num1 = num1 * 10 + (s[i] - '0');
    num1Valid = true;
    i++;
  }
  if (negative)
    num1 = -num1;

  // Expect a comma
  if (i >= s.size() || s[i] != ',')
    return false;
  i++; // Skip ','

  // Parse second number
  negative = false;
  if (s[i] == '-')
  {
    negative = true;
    i++;
  }
  while (i < s.size() && isdigit(s[i]))
  {
    num2 = num2 * 10 + (s[i] - '0');
    num2Valid = true;
    i++;
  }
  if (negative)
    num2 = -num2;

  // Expect a closing parenthesis
  if (i >= s.size() || s[i] != ')')
    return false;
  i++; // Skip ')'

  // Both numbers must be valid
  if (num1Valid && num2Valid)
  {
    result = num1 * num2;
    return true;
  }
  return false;
}

// Function to compute the result
int partA(const string &s)
{
  size_t i = 0;
  int total = 0, result = 0;

  while (i < s.size())
  {
    if (s.substr(i, 4) == "mul(")
    {
      if (parseMul(s, i, result))
      {
        total += result;
      }
      else
      {
        // Skip invalid mul-like pattern
        while (i < s.size() && s[i] != 'm')
          i++;
      }
    }
    else
    {
      i++;
    }
  }
  return total;
}

int partB(const string &s)
{
  size_t i = 0;
  int total = 0, result = 0;
  bool doflag = true;

  while (i < s.size())
  {
    if (s.substr(i, 7) == "don't()")
    {
      doflag = false;
      i += 7;
    }
    else if (s.substr(i, 4) == "do()")
    {
      doflag = true;
      i += 4;
    }
    if (s.substr(i, 4) == "mul(" && doflag)
    {
      if (parseMul(s, i, result))
      {
        total += result;
      }
      else
      {
        // Skip invalid mul-like pattern
        while (i < s.size() && s[i] != 'm')
          i++;
      }
    }
    else
    {
      i++;
    }
  }
  return total;
}
int main()
{
  string filePath = "../input/3.txt";
  string s = parseInput(filePath);
  if (s.empty())
    return 1;

  cout << "Input: " << s << endl;
  cout << "Result: " << partA(s) << endl;
  cout << "Part B:" << partB(s) << endl;

  return 0;
}
