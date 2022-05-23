/*
Write a program to read from the user a string of characters, ending with $, for the FA of the language L to determine 
whether the following words are accepted or rejected by L. 
For example, for the input aaabba$ the output should be YES while for the input babb$ the output should be NO.
*/

#include <iostream>
using namespace std;

int main()
{
    string str; //string to hold the input
    char ch; //character to see if user wants to continue or not
    do //do while loop executes as long as the user does not input 'n' in the machine
    {
        cout<<"Enter a regular expression"<<endl;
        cin >> str;
        int length = str.length(); //get the length of the input string
        if (length < 3) //if the length of the string is less than 3 
        {
            cout << "No" << endl; //print no
        }
        else if (str[length-3] == 'b' && str[length-2] == 'a') //else if the string is ba 
        {
            cout << "Yes" << endl; //return yes
        }
        else
        {
            cout << "No" << endl; //otherwise return no
        }
        cout << "Would you like to try again? (y/n)" << endl; //ask user if they want to input something else
        cin >> ch; //user input 
    } while (ch != 'n'); //while the user does not input 'n', do-while loop executes

    return 0;
}
