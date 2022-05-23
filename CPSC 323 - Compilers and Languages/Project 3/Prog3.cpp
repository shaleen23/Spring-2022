
/*
Given the following CFG and the LR parsing table, write a program to trace input strings over the alphabet { i, +, - , *, / ), ( } and ending with $.  
Test it on two input strings (1) (i+i)*i$   and    (2) (i*)$.  
*/

#include <iostream>
#include <string>
#include <sstream>
#include <stack>
#include <algorithm>

using namespace std;

/*
Given CFG:
  R1.  E→E + T
  R2.  E →E – T
  R3.  E → T
  R4.  T→T * F
  R5.  T→ T/F
  R6.  T→ F
  R7.  F→( E )
  R8.  F→ i
*/
void printStack(stack<string> temp) // function prints the stack
{
    while (!temp.empty())
    {
        cout << temp.top() << " ";
        temp.pop();
    }
    cout << endl;
}
void parser(string s, string table[17][12], stack<string> parse) // function parses the inputted string
{

    parse.push("0"); // push 0 onto stack since that is the rule for LR Parsing
    string state = "0"; // string to keep track of the current state 0-15
    int counter = 0;   // keep track of where we are in string
    cout<<"Current stack is: ";
    printStack(parse); // print stack
    int row, col;      // keep track of row and column of table

    do // while the string isn't accepted or rejected, do the following
    {
        stringstream s1; // create stringstream
        string next;  // incoming char from string

        char temporary = s.at(counter); // convert each char of string one by one to from char to string

        s1 << temporary; //add the temp char to the stringstream
        next = s1.str(); //copy string value to next

        for (int i = 0; i < 17; i++) //iterate through table
        {
            for (int j = 0; j < 12; j++)
            {
                if (table[i][j] == next) //if the incoming character is from the table
                {
                    col = j; //set column to j and continue to next iteration
                }
            }
        }

        row = stoi(state); // convert state to int
        row++; // increment row

        string check = table[row][col]; //set check to the value of the table at the row and column

        if (check == "acc") //if the value of check of table[row][col] is at acc, return accepted
        {
            cout << "Accepted"<<endl;
            break;
        }

        else if (check == "") //otherwise error
        {
            cout << "Rejected"<<endl;
            break;
        }

        char temp2 = check.at(0); //store the first char of check in temp2
        stringstream s2; //create stringstream

        string type; //type is either shift or reduce and determines which reduce it is
        s2 << temp2;
        type = s2.str();

        if (type == "S") //if it's shift, do the following
        {

            parse.push(next); //push the shift 

            string temporary;
            stringstream s3;
            temporary = table[row][col];  //set temporary to the value of the table at the row and column

            temp2 = check.at(1); //store the second char of check in temp2
            s3 << temp2; //add the temp2 char to the stringstream

            if (temporary.size() == 3) //if S15, then do the following
            {
                temp2 = check.at(2); //store the third char of check in temp2
                s3 << temp2; //add the temp2 char to the stringstream
            }
            type = s3.str(); //copy string value to type

            parse.push(type); //push the type to stack
            cout << "Current stack is: ";
            printStack(parse); //print stack

            state = type; //set the current state to the current type
            counter++; //increment counter
            
        }

        else if (type == "R") //if it's reduce do the following
        {
            stringstream s3; //create stringstream
            string temporary; //temporary is the value of the table at the row and column
            //since the rule is to pop off the top 2 elements everytime we pop off twice from the stack
            parse.pop();
            parse.pop();
            temporary = check.at(1); //set temporary to the value of the table at the STATE and TERMINAL
            s3 << temporary; //add the temporary char to the stringstream
            type = s3.str(); //copy string value to type
            if (type == "1") //if the reduce type is 1, then E→ E + T
            {
                //for when a grammar goes to E → E + T or something like that, we need to pop off 4 times from the stack
                parse.pop();
                parse.pop();
                parse.pop();
                parse.pop();
                
                //locate the value of the table at the state and terminal ex. state 0 at terminal e is 2, so we get 2 
                for (int i = 0; i < 17; i++)
                {
                    for (int j = 0; j < 12; j++)
                    {
                        if (table[i][j] == "E") //since the reduce 1 is E->E+T we need to find the state and terminal value of E
                        {
                            col = j; //set column to j and continue to next iteration
                        }
                    }
                }
                row = stoi(parse.top()); //convert the top of the stack to int
                row++; //increment row

                parse.push("E"); //push E onto stack
                parse.push(table[row][col]); //push the value of the table at the state and terminal to the stack
                cout << "Current stack is: ";
                printStack(parse); //print stack
                state = table[row][col]; //set state to the value of the table at the state and terminal
            }
            if (type == "2") //if the reduce is 2, then E->E-T
            {
                //as a result, since it's going to E-T, we need to pop off 4 times from the stack
                parse.pop();
                parse.pop();
                parse.pop();
                parse.pop();
                //locate the value of the table at the state and terminal ex. state 0 at terminal e is 2, so we get 2
                for (int i = 0; i < 17; i++)
                {
                    for (int j = 0; j < 12; j++)
                    {
                        if (table[i][j] == "E") //if the terminal and state is at E, then we know the value
                        {
                            col = j; //set col to that value    
                        }
                    }
                }
                row = stoi(parse.top()); //convert the top of the stack to int
                row++; //increment row

                parse.push("E"); //push E onto stack
                parse.push(table[row][col]); //push the value of the table at the state and terminal to the stack
                cout << "Current stack is: ";
                printStack(parse); //print stack
                state = table[row][col]; //set state to the value of the table at the state and terminal
            }
            if (type == "3") //if the reduce is 3, then E->T
            {
                //since it is only going to one grammar, we don't need to pop off multiple times and that already happened when we were checking if it was shift or reduce
                for (int i = 0; i < 17; i++)
                {
                    for (int j = 0; j < 12; j++)
                    {
                        if (table[i][j] == "E") //if the terminal and state is at E, get the value
                        {
                            col = j; //set the column to j to hold the value
                        }
                    }
                }
                row = stoi(parse.top()); //convert the top of the stack to int
                row++; //increment row

                parse.push("E"); //push E onto stack
                parse.push(table[row][col]); //push the value of the table at the state and terminal to the stack
                cout << "Current stack is: ";
                printStack(parse); //print stack
                state = table[row][col]; //set state to the value of the table at the state and terminal
            }
            if (type == "4") //if the reduce is 4, then T->T*F
            {
                //as a reult, we need to pop off 4 times from the stack
                parse.pop();
                parse.pop();
                parse.pop();
                parse.pop();
                //locate the value of the table at the state and terminal ex. state 0 at terminal T is 2, so we get 2
                for (int i = 0; i < 17; i++)
                {
                    for (int j = 0; j < 12; j++)
                    {
                        if (table[i][j] == "T") //if the terminal and state is at T, get the col value
                        {
                            col = j; //set hte col value to that 
                        }
                    }
                }
                row = stoi(parse.top()); //convert the top of the stack to int
                row++; //increment row

                parse.push("T"); //push T onto stack
                parse.push(table[row][col]); //push the value of the table at the state and terminal to the stack
                cout << "Current stack is: ";
                printStack(parse); //print stack
                state = table[row][col];    //set state to the value of the table at the state and terminal
            }
            if (type == "5") //if the reduce is 4, then T->T/F
            {
                //as a result, pop 4 times
                parse.pop();
                parse.pop();
                parse.pop();
                parse.pop();
                //locate the value of the table at the state and terminal ex. state 0 at terminal T is 2, so we get 2
                for (int i = 0; i < 17; i++)
                {
                    for (int j = 0; j < 12; j++)
                    {
                        if (table[i][j] == "T") //if the terminal and state is at T, get the corresponding value
                        {
                            col = j; //set the col value to that
                        }
                    }
                }
                row = stoi(parse.top()); //convert the top of the stack to int
                row++; //increment row

                parse.push("T"); //push T onto stack
                parse.push(table[row][col]); //push the value of the table at the state and terminal to the stack
                cout << "Current stack is: ";
                printStack(parse); //print stack
                state = table[row][col]; //set state to the value of the table at the state and terminal
            }
            if (type == "6") //if the reduce is 6, then T->F
            {
                //no additonal pops needed

                //locate the value of the table at the state and terminal ex. state 0 at terminal T is 2, so we get 2
                for (int i = 0; i < 17; i++)
                {
                    for (int j = 0; j < 12; j++)
                    {
                        if (table[i][j] == "T") //if the terminal and state is at T, get the corresponding value
                        {
                            col = j; //set the col value to that
                        }
                    }
                }
                row = stoi(parse.top()); //convert the top of the stack to int
                row++; //increment row

                parse.push("T"); //push T onto stack
                parse.push(table[row][col]); //push the value of the table at the state and terminal to the stack
                cout << "Current stack is: ";
                printStack(parse); //print stack
                state = table[row][col]; //set state to the value of the table at the state and terminal
            }
            if (type == "7") //if reduce is 7, then F->(E)
            {
                //as a result, we need to pop off 4 times because (, E, ), so we need to pop off 4 times
                parse.pop();
                parse.pop();
                parse.pop();
                parse.pop();

                //locate the value of the table at the state and terminal ex. state 0 at terminal F is 3, so we get 3
                for (int i = 0; i < 17; i++)
                {
                    for (int j = 0; j < 12; j++)
                    {
                        if (table[i][j] == "F") //if the terminal and state is at F, get the corresponding value
                        {
                            col = j; //set the col value to that
                        }
                    }
                }
                row = stoi(parse.top()); //convert the top of the stack to int
                row++; //increment row

                parse.push("F"); //push F onto stack
                parse.push(table[row][col]); //push the value of the table at the state and terminal to the stack
                cout << "Current stack is: ";
                printStack(parse); //print stack
                state = table[row][col]; //set state to the value of the table at the state and terminal
            }
            if (type == "8") //if reduce is 8, then F->i
            {
                //no additional pops needed

                //locate the value of the table at the state and terminal ex. state 0 at terminal F is 3, so we get 3
                for (int i = 0; i < 17; i++)
                {
                    for (int j = 0; j < 12; j++)
                    {
                        if (table[i][j] == "F") //if the terminal and state is at F, get the corresponding value
                        {
                            col = j; //set the col value to that
                        }
                    } 
                }
                row = stoi(parse.top()); //convert the top of the stack to int
                row++; //increment row

                parse.push("F"); //push F onto stack
                parse.push(table[row][col]); //push the value of the table at the state and terminal to the stack
                cout << "Current stack is: ";
                printStack(parse); //print stack
                state = table[row][col]; //set state to the value of the table at the state and terminal
            }
        }
    } while (table[row][col] != "acc" || table[row][col] != ""); //while the state is not accepting or the stack is not empty, do-while loop will continue
}

int main()
{
    //given LR parsing table
    string table[17][12] ={{"", "i", "+", "-", "*", "/", "(", ")", "$", "E", "T", "F"},
                          {"0", "S5", "", "", "", "", "S4", "", "", "1", "2", "3"},
                          {"1", "", "S6", "S7", "", "", "", "", "acc", "", "", ""},
                          {"2", "", "R3", "R3", "S8", "S9", "", "R3", "R3", "", "", ""},
                          {"3", "", "R6", "R6", "R6", "R6", "", "R6", "R6", "", "", ""},
                          {"4", "S5", "", "", "", "", "S4", "", "", "10", "2", "3"},
                          {"5", "", "R8", "R8", "R8", "R8", "", "R8", "R8", "", "", ""},
                          {"6", "S5", "", "", "", "", "S4", "", "", "", "11", "3"},
                          {"7", "S5", "", "", "", "", "S4", "", "", "", "12", "3"},
                          {"8", "S5", "", "", "", "", "S4", "", "", "", "", "13"},
                          {"9", "S5", "", "", "", "", "S4", "", "", "", "", "14"},
                          {"10", "", "S6", "S7", "", "", "", "S15", "", "", "", ""},
                          {"11", "", "R1", "R1", "S8", "S9", "", "R1", "R1", "", "", ""},
                          {"12", "", "R2", "R2", "S8", "S9", "", "R2", "R2", "", "", ""},
                          {"13", "", "R4", "R4", "R4", "R4", "", "R4", "R4", "", "", ""},
                          {"14", "", "R5", "R5", "R5", "R5", "", "R5", "R5", "", "", ""},
                          {"15", "", "R7", "R7", "R7", "R7", "", "R7", "R7", "", "", ""}};
    string input, input2; //input and input2 are the input strings
    stack<string> trace; //stack for tracing
 
   do //do-while loop iterates as long as user does not enter "n"
    {
    cout << "Enter input string: "; //prompt user to enter input string
    cin >> input; //get input string
    parser(input, table, trace); //call parser function
    cout<<"Would you like to input another string? (y/n)";
    cin>>input2;
    } while (input2 == "y"); //do-while loop will continue as long as user does not enter "n"
    return 0;
}
