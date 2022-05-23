/*
Write a program to read from the user a single line (up to 255 characters) statement at a time and determine whether each token is a number, identifier, a reserved word, or special character.
A number is an unsigned integer or a signed integer. An identifier starts with a letter or _ followed by any number of letters, _, and digits
*/

#include <iostream>
using namespace std;

string reservedWords[] = {"cout<<", "for", "int", "while"};
string special[] = {"<", "=", "*", "-", ";", "(", ")", "<=", "+", ","};

string getTokenType(string token) //function checks for reserved words and special characters and returns the type
{

    //reserved words
    for (int i = 0; i < 4; i++) //iterate through reservedWords array
    {
        if (token == reservedWords[i]) //if the word is a reserved word
        
        {
            return "reserved word"; //return reserved
        }
    }

    //special symbols
    for (int i = 0; i < 10; i++) //iterate through special characters array
    {
        if (token == special[i]) //if there is a special character
        {
            return "special symbol"; //return special character
        }
    }
    //finding the numbers
    if (token[0] == '-' || (0 <= token[0] && token[0] <= 9)) //if the first character is a - or a number between 0-9
    {
        for (int i = 0; i < token.length(); i++) //then iterate through each index in the word
        {

            if (i == token.length()) //if the current index is equal to the length of the word
            {
                return "number"; //return that it is a number
            }
        }
    }

    //identifiers
    if (token[0] == '_' || ('a' <= token[0] && token[0] <= 'z')) //check if the word given is an identifier a-z
    {
        return "identifier"; //if there is, return identifier 
    }
    else
    {
        return "not an identifier"; //otherwise say it is not 
    }
}


int main()
{
    char ch;
    string input;
    
    do //do while loop iterates as long as the input length is less than 255 characters and the input is yes
    {
        cout << "Enter a statement: \n";
        cin >> input;
       
        cout << input << "is: " << getTokenType(input) << endl;
        cout << "CONTINUE(y/n)? ";
        cin >> ch;
       
    } while (input.length() < 255 && ch == 'y');
   
    return 0;
}
