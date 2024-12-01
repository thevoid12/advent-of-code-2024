#include <iostream>
#include <fstream> // Include this for file operations
#include <vector>
#include <algorithm> // For sort()
#include <cmath>     // For abs()

using namespace std;

int main()
{
  // Open the input file
  ifstream inputFile("1.txt"); // Replace with your file name and path

  if (!inputFile)
  {
    cerr << "Unable to open file." << endl;
    return 1; // Return with error code if file couldn't be opened
  }

  vector<int> A, B;
  int a, b;
  unordered_map<int, int> mpp;
  // Read each line from the file
  while (inputFile >> a >> b)
  {

    A.push_back(a); // Store the first number in vector A
    B.push_back(b); // Store the second number in vector B
    mpp[b]++;
  }

  // Close the file
  inputFile.close();

  // Check if both vectors have the same size
  if (A.size() != B.size())
  {
    cerr << "Mismatched vector sizes. Please check input data." << endl;
    return 1;
  }

  // Sort both vectors
  sort(A.begin(), A.end());
  sort(B.begin(), B.end());

  // Calculate the sum of absolute differences
  int sum = 0;
  int prod = 0;
  for (int i = 0; i < A.size(); i++)
  {
    sum += abs(A[i] - B[i]);
    prod += (A[i] * mpp[A[i]]);
  }

  // Print the result
  cout << "Part 1 Sum of absolute differences: " << sum << endl;
  cout << "Prod is" << prod << endl;
  return 0;
}
