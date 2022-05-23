///////////////////////////////////////////////////////////////////////////////
// poly_exp.cpp
//
// Definitions for two algorithms:
//
// soccer_exhaustive
// soccer_dyn_prog
//
///////////////////////////////////////////////////////////////////////////////


#include <cmath>
#include <iostream>
#include <array>
#include <vector>
#include <algorithm>
#include "poly_exp.hpp"

using namespace std;

int algorithms::soccer_exhaustive(const vector<string> field)
{
  if (field.size() == 0)
  {
    throw invalid_argument("Invalid graph");
  }

  if (field[0].size() == 0)
  {
    throw invalid_argument("Invalid graph");
  }

  for (int i = 0; i < field.size(); i++)
  {
    for (int j = 0; j < field[0].size(); j++)
    {
      if (field[i][j] != '.' && field[i][j] != 'X')
      {
        throw invalid_argument("Invalid argument");
      }
    }

    if (field[i].size() != field[0].size())
    {
      throw invalid_argument("Invalid Shape");
    }
  }

  int R = field.size();
  int C = field[0].size();

  int length = R + C - 2;

  if (field[0].size() >= 0 && field[0].size() <= 30)
  {
  }

  else
  {
   throw invalid_argument("invalid_argument");
  }

  if (R == 1 && field[0][0] == '.')
  {
   return 1;
  }

  int counter = 0;

  for (int i = 0; i <= pow(2, length); i++)
  {
     vector<array<int, 2>> candidate = {{0,0}};
     for (int j = 0; j <= length - 1; j++)
     {
       int bit = (i >> j) & 1;
       if (bit == 1)
       {
         array<int, 2> t = candidate.back();
         candidate.push_back({{t[0] + 1, t[1]}});
       }
       else
       {
         array<int, 2> t = candidate.back();
         candidate.push_back({{t[0], t[1] + 1}});
       }
     }

       if (candidate.back()[0] == R - 1 && candidate.back()[1] == C - 1)
       {
         int truth = 1;

         for (int m = 0; m < candidate.size(); m++)
         {
           if (field.at(candidate.at(m)[0])[candidate.at(m)[1]] == 'X')
           {
             truth = 0;
           }
         }

         if (truth == 1)
         {
            counter++;
         }
       }
  }
  return counter;

}

int algorithms::soccer_dyn_prog(const vector<string> field)
{

   if (field.size() == 0)
   {
    throw invalid_argument("Invalid graph");
   }

   if (field[0].size() == 0)
   {
    throw invalid_argument("Invalid graph");
   }

   for (int k = 0; k < field.size(); k++)
   {
     for (int l = 0; l < field[0].size(); l++)
     {
       if (field[k][l] != '.' && field[k][l] != 'X')
       {
         throw invalid_argument("Invalid argument");
       }
     }

     if (field[k].size() != field[0].size())
     {
       throw invalid_argument("Invalid Shape");
     }
   }

   if(field[0][0] == 'X')
   {
     return 0;
   }

  vector <vector<int>> A(field.size(), vector<int>(field[0].size(), 0));
  // base case
  A[0][0] = 1;

  // general cases
  for(int i = 0; i < field.size(); i++)
  {
    for(int j = 0; j < field[0].size(); j++)
    {
       if (field[i][j] == 'X')
       {
          A[i][j] = 0;
          continue;
       }

      int above = 0;
      int left = 0;

      if (i > 0 && field[i-1][j]=='.')
      {
          above = A[i-1][j];
      }

      if (j > 0 && field[i][j-1]=='.')
      {
         left = A[i][j-1];
      }

       A[i][j] += above + left;
    }
  }

  int R = field.size();
  int C = field[0].size();
  int full = A[R-1][C-1];
  return full;
}
