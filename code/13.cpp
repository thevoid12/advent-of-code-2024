#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <utility> // for std::pair
#include <cmath>
#define lli long long
using namespace std;

vector<pair<lli, lli>> A;
vector<pair<lli, lli>> B;
vector<pair<lli, lli>> prize;

void parseInput()
{
  ifstream f("../input/13.txt");
  string line;

  while (getline(f, line))
  {
    // Trim the line and ensure it is non-empty
    if (line.empty())
      continue;

    // Variables to hold extracted values
    lli xA, yA, xB, yB, xPrize, yPrize;

    // Use stringstream for parsing
    stringstream ss(line);

    string label, temp;
    while (ss >> label)
    {
      if (label == "Button")
      {
        char button;
        ss >> button; // Read 'A' or 'B'

        ss.ignore(2); // Ignore ": "
        ss.ignore(2); // Ignore "X+"

        lli x, y;
        ss >> x;      // Read X offset
        ss.ignore(3); // Ignore ", Y+"
        ss >> y;      // Read Y offset

        if (button == 'A')
        {
          xA = x, yA = y;

          A.emplace_back(xA, yA);
        }
        else if (button == 'B')
        {
          xB = x, yB = y;
          B.emplace_back(xB, yB);
        }
      }
      else if (label == "Prize:")
      {
        ss.ignore(3); // Ignore "X="
        ss >> xPrize; // Read prize X
        ss.ignore(4); // Ignore ", Y="
        ss >> yPrize; // Read prize Y
        xPrize += 10000000000000;
        yPrize += 10000000000000;
        prize.emplace_back(xPrize, yPrize);
      }
    }
  }
}

// solve the system of equation for each pair
lli part1()
{
  lli maxval = 0;

  // Using brute force 2 eqn solving
  //  for (int i = 0; i < A.size(); i++)
  //  {
  //    lli mx = (A[i].first * B[i].second) - (B[i].first * A[i].second);
  //    lli mt = (prize[i].first * B[i].second) - (prize[i].second * A[i].second);

  //   if (mt % mx != 0)
  //     continue;
  //   lli a = mt / mx;
  //   lli b = (prize[i].first - (A[i].first * a)) / B[i].first;
  //   lli res = 3 * a + b;
  //   maxval = max(maxval, res);
  // }
  // return maxval;

  // using cramer's rule
  for (int i = 0; i < A.size(); i++)
  {
    // Coefficients of the equations
    lli a1 = A[i].first, b1 = B[i].first, c1 = prize[i].first;
    lli a2 = A[i].second, b2 = B[i].second, c2 = prize[i].second;

    // Determinant of the coefficient matrix
    lli det = (a1 * b2 - a2 * b1);
    if (det == 0)
    {
      continue;
    }

    // Determinants for Cramer's Rule
    lli detA = (c1 * b2 - c2 * b1);
    lli detB = (a1 * c2 - a2 * c1);

    // Check if the solution is integer
    if (detA % det != 0 || detB % det != 0)
    {
      continue;
      // No integer solution exists
    }

    // Calculate integer solutions
    lli resA = detA / det;
    lli resB = detB / det;
    maxval += resA * 3 + resB;
  }
  return maxval;
}
int main()
{
  parseInput();
  cout << part1() << endl;
}
