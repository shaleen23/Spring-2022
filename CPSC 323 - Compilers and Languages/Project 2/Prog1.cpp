/*
Given the following CFG and the Predictive Parsing table. Write a program to trace an input string given by the user. 
Save it as Prog1. Test your program with the following input strings:  (1) (a +a )*a$, (2) a*(a/a)$, (3) a*(a+a)$. 
Show the content of the stack after each match
*/

#include <iostream>
#include <string>
#include <sstream>
#include <stack>
#include <array>

using namespace std;

void printStack(stack<string> temp) // function prints the stack
{
    while (!temp.empty())
    {
        cout << temp.top() << " ";
        temp.pop();
    }
    cout << endl;
}

void parser(string s, string table[6][9], stack<string> parse, string terminal[10]) //function parses through the stack while passing in the input string, grammar table, the stack, and the given terminals
{
    int counter = 0; //counter to keep track of where we are in the string

    parse.push("$"); //push dollars sign onto stack to start
    parse.push("S"); //push S onto stack since that is the first grammar in the table
    printStack(parse); //print the stack


    while (!parse.empty()) //while the stack isn't empty, do the following
    {
        char temp = s.at(counter); //temp will be the current character in the string
        stringstream ss; //stringstream to convert char to string
        string incoming; //will keep track of the next character in the string
        ss << temp; //store the char in the stringstream
        incoming = ss.str(); //convert the stringstream to a string
        bool found = false; //bool to determine if the terminal was found
        int row, col; //row and column to find the top of the stack and the incoming string in the table
        if (parse.size() == 1) //if the stack only has 1 thing in the stack, then we check for the following
        {
            if (parse.top() == "$") //if it only has a dollar sign, that means it is accepted, otherwise it's rejected regardless
            {
                cout << "Accepted" << endl;
                break;
            }
        }

        for (int i = 0; i < 8; i++) //iterate through the terminals to see if the terminal at the given index is the top of the stack
        {
            if (parse.top() == terminal[i])
            {
                found = true;
            }
        }
        if (found == true) //if we do find a terminal in the stack, then we check if it is the same as the next character in the string
        {
            if (parse.top() == incoming) //if so, we pop it off the terminal 
            {

                parse.pop();
                cout << "Current stack is: ";
                printStack(parse);
                cout << endl;
                counter++;
            }
        }
        else if(found == false)//if we don't find a terminal, then we check the entire parsing table
        {
            for (int i = 0; i < 6; i++) 
            {
                for (int j = 0; j < 9; j++)
                {
                    if (table[i][j] == parse.top()) //if the top of the stack is the same as the current location in the table, then set row to i so we know which state we are at
                    {
                        row = i;
                    }
                    if (table[i][j] == incoming) //if the next character in the string is the same as the current location in the table, then set col to j so we know which terminal we are at
                    {
                        col = j;
                    }
                    
                }
            }

            if (table[row][col] != "") //if the table at the state and terminal is not blank because that would be a rejection then
            {
                string tmp;
                parse.pop(); //pop the element from the top of the stack
                tmp = table[row][col]; //set tmp to the element at the state and terminal
                int j = tmp.size() - 1; //set j to the last index of the string so we can reverse the string to avoid any error
                for (int i = 0; i < tmp.length(); i++) //iterate through the current grammar 
                {
                    char c = tmp.at(j); //create a char to hold the current grammar
                    stringstream ss; //stringstream to convert char to string
                    string value; //will keep track of the next character in the string
                    ss << c; //store the char in the stringstream
                    value = ss.str(); //convert the stringstream to a string
                    parse.push(value); //push the string onto the stack
                    j--; //decrement j so we can go to the next grammar
                }
                if (table[row][col] == "e") //if tha table at the given state and terminal is epsilon, pop off from the stack and print it out
                {

                    parse.pop();
                }
                cout << "Current stack is: ";
                printStack(parse);
                cout << endl;
            }
            else if(table[row][col] == "") //if the table at the state and terminal has a blank, string is rejected
            {

                cout << "Rejected" << endl;
                break;
            }
        }
    }
}

int main()
{
    stack <string> trace;
    // Predictive parsing table
    string table[6][9] = {{""  ,"a"  , "+"  , "-"  , "*"  , "/"  , "("    , ")"  , "$"},
                        {"E" ,"TQ" , ""   , ""   , ""   , ""   , "TQ"   , ""   , "" }, 
                        {"Q" , ""  , "+TQ", "-TQ", ""   , ""   , ""     , "e"  , "e"}, 
                        {"T" , "FR", ""   , ""   , ""   , ""   , "FR"   , ""   , "" }, 
                        {"R" , ""  , "e"  , "e"  , "*FR", "/FR", ""     , "e"  , "e"}, 
                        {"F" , "a" , ""   , ""   , ""   , ""   , "(E)"  , ""   , "" }  
    };
    string terminals[8] = {"a", "+", "-", "*", "/", "(", ")", "$"};
    string input, input2; //inputs
    do //do while loop for user input
    {
        cout << "Enter input string: ";
        cin >> input;
        parser(input, table, trace, terminals); //call the parser function

        cout << "Would you like to enter another string? (y/n): ";
        cin >> input2;
    } while (input2 == "y"); //do while loop continues while user enters 'y' for input

    return 0;
}

