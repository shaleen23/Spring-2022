/*
Shaleen Mathur
Professor Hermans 
CPSC 323 Section 03 
2 May 2022
*/
#include <iostream>
#include <map>
#include <string>
#include <stack>
#include <cmath>
#include <algorithm>

using namespace std;

double scanNum(char c) //function to scan the number
  {
   int value;
   value = c;
   return double(value - '0'); // return float from character
}
int Operator(char ch) //function to determine if the character is an operator
{
   if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^') //if the character is an operator, do the following
   {
      return 1; // character is an operator
   }
   return -1; // not an operator
}
int isOperand(char ch)
{
   if (ch >= '0' && ch <= '9') //if character is between 0-9
   {
      return 1; // character is an operand
   }
   return -1; // not an operand
}
double operation(int a, int b, char op) // function to perform the operation
{ 
   if (op == '+')
   {                // addition
      return b + a; // return the sum
   }
   else if (op == '-')
   {                // subtraction
      return b - a; // return the difference
   }
   else if (op == '*')
   {                // multiplication
      return b * a; // return the product
   }
   else if (op == '/')
   {                // division
      return b / a; // return the quotient
   }
   else if (op == '^')
   {                    // exponent
      return pow(b, a); // return the exponent
   }
   else
   {
      return INT_MIN; // return minimum value
   }
}
double postfixEval(string expression) // evaluate postfix expression
{                       
   int a, b;            // operands
   stack<double> trace; // create stack
   string::iterator it; // iterator for string
   for (it = expression.begin(); it != expression.end(); it++)
   { // iterate through string
      // read elements and perform postfix evaluation
      if (Operator(*it) != -1)
      {                                    // if character is an operator
         a = trace.top();                  // set a to top of stack
         trace.pop();                      // pop top element
         b = trace.top();                  // set b to top of stack
         trace.pop();                      // pop top element
         trace.push(operation(a, b, *it)); // push result of operation to stack
      }
      else if (isOperand(*it) > 0)
      {                            // if character is an operand and greater than 0
         trace.push(scanNum(*it)); // push operand to stack
      }
   }
   return trace.top(); // return top of stack
}
int main()
{
   string s; // input string
   char choice;
   int x; // input number
   map<char, int> trace; // map to store variables
   do
   {
      cout << "Enter a postfix expression with a $ at the end: ";

      cin >> s;
      s.pop_back(); // remove $ from end of string

      for (int i = 0; i < s.length(); i++)
      { // iterate through string
         if (s[i] >= 'a' && s[i] <= 'z' && trace.find(s[i]) == trace.end())
         { // if character is a lowercase letter and in map between a-z
            cout << "Enter the value of " << s[i] << ": ";
            cin >> x;
            trace[s[i]] = x; // insert character and value into map
            s[i] = x + '0';  // the string at the current index is set to the value of the character and a zero
         }
         else if (trace.find(s[i]) != trace.end())
         {                            // if character is not in map
            s[i] = trace[s[i]] + '0'; // the string at the current index is set to the value of the character and a zero
         }
      }
      double res = postfixEval(s);
      cout << "Final value= " << res << endl;
      cout << "Continue(y/n)? ";
      cin >> choice;
   } while (choice != 'n'); // do while loop continues until user enters n
   return 0;
}