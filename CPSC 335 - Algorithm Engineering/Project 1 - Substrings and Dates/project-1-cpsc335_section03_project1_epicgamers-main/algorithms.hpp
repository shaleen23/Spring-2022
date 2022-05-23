///////////////////////////////////////////////////////////////////////////////
// algorithms.hpp
//
// Definitions for four algorithms:
//
// append_run
// run_length_encode
// longest_frequent_substring
// reformat_date
//
///////////////////////////////////////////////////////////////////////////////

#pragma once

#include <algorithm>
#include <iostream>
#include <map>
#include <string.h>
#include <string>

using namespace std;
namespace algorithms
{

// Run-length-encode the given string.
//
// uncompressed must be a string containing only lower-case letters or spaces.
//
// A run is defined as a sequence of K>2 contiguous copies of the same
// character c.
// For example, "aaa" is a run with K=3 and c='a'.
// This function returns a string based on uncompressed, where every run is
// replaced with the string
//   COUNTc
// where COUNT is the base-10 representation of K. Non-run characters are
// left as-is.
//
// Example inputs and outputs:
//   "aaa" -> "3a"
//   "heloooooooo there" -> "hel8o there"
//   "footloose and fancy free" -> "f2otl2ose and fancy fr2e"
//
// Throws std::invalid_argument if the string contains invalid characters.

string append_run(string C, char run_char, int run_length)
{
  if (run_length > 1)
  {
    C += to_string(run_length);
  }
  C += run_char;

  return C;
}

string run_length_encode(const string &uncompressed)
{
  string C = "";

  if (uncompressed.empty())
  {
    return C;
  }

  char run_char = uncompressed[0];
  int run_length = 1;

  for (int i = 1; i < uncompressed.length(); i++)
  {
    if (isspace(uncompressed[i]) && isspace(uncompressed[i + 1]))
    {
      throw invalid_argument("Invalid character.");
    }
    else if (uncompressed[i] == run_char)
    {
      run_length++;
    }
    else
    {
      C = append_run(C, run_char, run_length);
      run_char = uncompressed[i];
      run_length = 1;
    }
  }

  C = append_run(C, run_char, run_length);
  return C;
}

// Returns the longest substring of text, such that every character in the
// substring appears at least k times in text.
// If there are ties, the substring that appears first is returned.

string longest_frequent_substring(const string &text, unsigned k)
{
  map<char, int> Dictionary;
  char current;

  for (int i = 0; i < text.size(); i++)
  {
    current = text[i];
    if (Dictionary.find(current) == Dictionary.end())
    {
      Dictionary[current] = 1;
    }
    else
    {
      Dictionary[current]++;
    }
  }

  string best = "";
  string cand = "";
  int iterator = 1;
  bool abovek = 1;

  for (int m = 0; m < text.size(); m++)
  {
    iterator = 1;
    for (int n = m + 1; n <= text.size(); n++)
    {
      cand = text.substr(m, iterator);
      iterator++;
      for (int x = 0; x < cand.size(); x++)
      {
        current = cand[x];
        if ((Dictionary[current]) < k)
        {
          abovek = 0;
          break;
        }
      }
      if (abovek == 1)
      {
        if (cand.size() > best.size())
        {
          best = cand;
        }
      }
      abovek = 1;
    }
  }
  return best;
}

// Reformats a string containing a date into YYYY-MM-DD format.
//
// input may be formatted in one of four patterns:
// 1. Y-M-D
//    where Y, M, and D are positive integers
// 2. M/D/Y
//    where Y, M, and D are positive integers
// 3. MONTH DAY, YEAR
//    where
//    - MONTH is a case-insensitive name of a month, ex.
//      "january", "FEBRUARY", "March", etc.
//    - DAY is a positive integer representing a day, e.x. "15"
//    - YEAR is a positive integer representing a year, e.x. "2022"
// 4. MON DAY, YEAR
//    where
//    - MON is a case-insensitive three-letter abbreviation of a month, ex.
//      "jan", "FEB", "Mar", etc.
//    - DAY is the same as above
//    - YEAR is the same as above
//
// Any leading spaces or trailing spaces are ignored.
//
// Returns a string in strict YYYY-MM-DD format.
//
// Throws std::invalid argument if:
// - input does not fit any of the four patterns
// - MONTH is not a valid month name
// - MON is not a valid month abbreviation
// - DAY is not in the range [1, 31]
// - YEAR is not in the range [1900, 2099]

string reformat_date(const string &input)
{

  string output;
  // want YYYY-MM-DD

  string mon[] = {"jan", "feb", "mar", "apr", "may", "jun", "jul", "aug", "sep", "oct", "nov", "dec"};
  string months[] = {"january", "february", "march", "april", "may", "june", "july", "august", "september", "october", "november", "december"};

  // 1 means - format, 2 means / format, 3 mean MON format, 4 means MONTH format
  int stage = 4;

  string day, month, year;
  int currentDay, currentMonth = 0, currentYear;

  for (int s = 0; s < input.size(); s++)
  {
    if (isdigit(input[s]))
    {
      break;
    }
    if (s == input.size() - 1)
    {
      throw invalid_argument("Invalid character.");
    }
  }

  string validInput = "";
  char c;
  int i = 0;

  while (input[i])
  {
    c = input[i];
    validInput += tolower(c);
    i++;
  }

  // this for loop helps find the format
  for (int i = 0; i < validInput.size(); i++)
  {
    if (validInput[i] == '-')
    {
      stage = 1;
    }
    if (validInput[i] == '/')
    {
      stage = 2;
    }
    if (validInput[3] == ' ' && isalpha(validInput[0]))
    {
      stage = 3;
    }
  }

  if (stage == 1)
  {
    int i = 0;
    while (validInput[i] != '-')
    {
      year += validInput[i++];
    }
    i++;

    while (validInput[i] != '-')
    {
      month += validInput[i++];
    }
    i++;

    if (month.size() == 1)
    {
      month = '0' + month;
    }

    while (input[i])
    {
      day += validInput[i++];
      if (isalpha(validInput[i]) || validInput[i] == '-')
      {
        throw invalid_argument("Invalid character.");
      }
    }

    if (day.size() == 1)
    {
      day = '0' + day;
    }
    day.erase(remove(day.begin(), day.end(), ' '), day.end());
    year.erase(remove(year.begin(), year.end(), ' '), year.end());

    currentDay = stoi(day);
    currentMonth = stoi(month);
    currentYear = stoi(year);

    if ((currentDay >= 1 && currentDay <= 31) && (currentMonth >= 1 && currentMonth <= 12) && (currentYear >= 1900 && currentYear <= 2099))
    {
      output = year + '-' + month + '-' + day;
    }
    else
    {
      throw invalid_argument("Invalid character.");
    }
  }

  if (stage == 2)
  {
    int j = 0;
    while (validInput[j] != '/')
    {
      month += validInput[j++];
    }
    j++;

    if (month.size() == 1)
    {
      month = '0' + month;
    }

    while (validInput[j] != '/')
    {
      day += validInput[j++];
    }
    j++;

    if (day.size() == 1)
    {
      day = '0' + day;
    }

    while (validInput[j])
    {
      year += validInput[j++];
      if (isalpha(validInput[j]))
      {
        throw invalid_argument("Invalid character.");
      }
    }

    currentDay = stoi(day);
    currentMonth = stoi(month);
    currentYear = stoi(year);

    if ((currentDay >= 1 && currentDay <= 31) && (currentMonth >= 1 && currentMonth <= 12) && (currentYear >= 1900 && currentYear <= 2099))
    {
      output = year + '-' + month + '-' + day;
    }
    else
    {
      throw invalid_argument("Invalid character.");
    }
  }

  if (stage == 3)
  {
    int a = 0;
    while (validInput[a] != ' ')
    {
      month += validInput[a++];
    }
    a++;

    while (validInput[a] != ',')
    {
      day += validInput[a++];
    }
    a++;
    a++;

    if (day.size() == 1)
    {
      day = '0' + day;
    }

    while (validInput[a])
    {
      year += validInput[a++];
      if (isalpha(validInput[a]))
      {
        throw invalid_argument("Invalid character.");
      }
    }

    currentDay = stoi(day);
    currentYear = stoi(year);

    for (int k = 0; k < month.length(); k++)
    {
      if (month[k] >= 'A' && month[k] <= 'Z')
      {
        month[k] = ((char)(month[k] - 'A' + 'a'));
      }
    }

    for (int b = 0; b < 12; b++)
    {
      if (month == mon[b])
      {
        currentMonth = b + 1;
      }
    }

    month = to_string(currentMonth);
    if (month.size() == 1)
    {
      month = '0' + month;
    }

    if ((currentDay >= 1 && currentDay <= 31) && (currentMonth >= 1 && currentMonth <= 12) && (currentYear >= 1900 && currentYear <= 2099))
    {
      output = year + '-' + month + '-' + day;
    }

    else
    {
      throw invalid_argument("Invalid character.");
    }
  }

  if (stage == 4)
  {
    int g = 0;

    while (validInput[g] != ' ')
    {
      month += validInput[g++];
    }
    g++;

     while (validInput[g] != ',')
    {
      day += validInput[g++];
    }
    g++;
    g++;

    if (day.size() == 1)
    {
      day = '0' + day;
    }

     while (validInput[g])
    {
      year += validInput[g++];
    }

    if (year.size() > 4)
    {
      throw invalid_argument("Invalid character.");
    }

    currentDay = stoi(day);
    currentYear = stoi(year);

    for (int i = 0; i < month.length(); i++)
    {
      if (month[i] >= 'A' && month[i] <= 'Z')
      {
        month[i] = ((char)(month[i] - 'A' + 'a'));
      }
    }

    for (int b = 0; b <= 12; b++)
    {
      if (month == months[b])
      {
        currentMonth = b + 1;
      }
    }

    if (currentMonth == 0)
    {
      throw invalid_argument("Invalid character.");
    }

    month = to_string(currentMonth);
    if (month.size() == 1)
    {
      month = '0' + month;
    }

    if ((currentDay >= 1 && currentDay <= 31) && (currentMonth >= 1 && currentMonth <= 12) && (currentYear >= 1900 && currentYear <= 2099))
    {
      output = year + '-' + month + '-' + day;
    }
    else
    {
      throw invalid_argument("Invalid character.");
    }
  }

  return output;
}

} // namespace algorithms
