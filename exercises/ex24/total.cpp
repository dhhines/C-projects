/**
 * @author David Hines
 * @file total.cpp
 *
 * Simple C++ program to read in values from a file, add those values together
 * and print the result to standard output.
 */

#include <iostream>
#include <fstream>

using namespace std;

int main()
{

  ifstream input("numbers.txt");

  int val;
  int total = 0;
  while (input >> val)
    total += val;

  cout << "Total: " << total << endl;

}
